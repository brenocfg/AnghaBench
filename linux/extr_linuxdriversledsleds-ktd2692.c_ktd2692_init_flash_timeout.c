#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct led_flash_setting {int max; int step; int val; int /*<<< orphan*/  min; } ;
struct led_classdev_flash {struct led_flash_setting timeout; } ;
struct ktd2692_led_config_data {int flash_max_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  KTD2692_FLASH_MODE_TIMEOUT_DISABLE ; 
 int KTD2692_FLASH_MODE_TIMEOUT_LEVELS ; 

__attribute__((used)) static void ktd2692_init_flash_timeout(struct led_classdev_flash *fled_cdev,
				       struct ktd2692_led_config_data *cfg)
{
	struct led_flash_setting *setting;

	setting = &fled_cdev->timeout;
	setting->min = KTD2692_FLASH_MODE_TIMEOUT_DISABLE;
	setting->max = cfg->flash_max_timeout;
	setting->step = cfg->flash_max_timeout
			/ (KTD2692_FLASH_MODE_TIMEOUT_LEVELS - 1);
	setting->val = cfg->flash_max_timeout;
}