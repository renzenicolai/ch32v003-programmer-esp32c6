#include <inttypes.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "ch32.h"


bool test() {
    bool ch32res;

    ch32_sdi_reset();
    ch32_enable_slave_output();

    ch32res = ch32_check_link();
    if (!ch32res) {
        return false;
    }
    printf("Halt CH32...\n");
    ch32res = ch32_halt_microprocessor();
    if (!ch32res) {
        printf("CH32 halt failed\n");
        return false;
    }
    printf("CH32 halted\n");
    vTaskDelay(pdMS_TO_TICKS(1000));

    printf("Resume CH32...\n");
    ch32res = ch32_resume_microprocessor();
    if (!ch32res) {
        printf("CH32 resume failed\n");
        return false;
    }
    printf("CH32 resumed\n");
    vTaskDelay(pdMS_TO_TICKS(1000));

    printf("Reset CH32 and halt...\n");
    ch32res = ch32_reset_microprocessor_and_halt();
    if (!ch32res) {
        printf("CH32 reset and halt failed\n");
        return false;
    }
    printf("CH32 reset and halt ok\n");
    vTaskDelay(pdMS_TO_TICKS(1000));

    printf("Reset CH32 and run...\n");
    ch32res = ch32_reset_microprocessor_and_run();
    if (!ch32res) {
        printf("CH32 reset and run failed\n");
        return false;
    }
    printf("CH32 reset and run ok\n");
    vTaskDelay(pdMS_TO_TICKS(1000));

    /*printf("CH32 reset debug module\n");
    ch32res = ch32_reset_debug_module();
    if (!ch32res) {
        printf("CH32 debug module reset failed\n");
        return false;
    }
    printf("CH32 debug module reset ok\n");
    vTaskDelay(pdMS_TO_TICKS(1000));*/


    ch32_sdi_write(CH32_REG_DEBUG_COMMAND, 0x00271008);

    uint32_t value;
    ch32_sdi_read(CH32_REG_DEBUG_COMMAND, &value);
    printf("Value: %" PRIx32"\n", value);

    return true;
}

void app_main(void) {
    ch32_init(15);
    test();

    //ch32_programmer();

    //while (!test()) {
    //    vTaskDelay(pdMS_TO_TICKS(1000));
    //}
}
