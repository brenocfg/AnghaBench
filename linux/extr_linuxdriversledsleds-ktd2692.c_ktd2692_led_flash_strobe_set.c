#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct led_flash_setting {int /*<<< orphan*/  step; int /*<<< orphan*/  val; } ;
struct TYPE_2__ {int /*<<< orphan*/  brightness; } ;
struct led_classdev_flash {TYPE_1__ led_cdev; struct led_flash_setting timeout; } ;
struct ktd2692_context {int mode; int /*<<< orphan*/  lock; int /*<<< orphan*/  aux_gpio; } ;

/* Variables and functions */
 int GET_TIMEOUT_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTD2692_HIGH ; 
 int /*<<< orphan*/  KTD2692_LOW ; 
 void* KTD2692_MODE_DISABLE ; 
 int KTD2692_MODE_FLASH ; 
 int KTD2692_REG_FLASH_TIMEOUT_BASE ; 
 int KTD2692_REG_MODE_BASE ; 
 int /*<<< orphan*/  LED_OFF ; 
 struct ktd2692_context* fled_cdev_to_led (struct led_classdev_flash*) ; 
 int /*<<< orphan*/  gpiod_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktd2692_expresswire_write (struct ktd2692_context*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ktd2692_led_flash_strobe_set(struct led_classdev_flash *fled_cdev,
					bool state)
{
	struct ktd2692_context *led = fled_cdev_to_led(fled_cdev);
	struct led_flash_setting *timeout = &fled_cdev->timeout;
	u32 flash_tm_reg;

	mutex_lock(&led->lock);

	if (state) {
		flash_tm_reg = GET_TIMEOUT_OFFSET(timeout->val, timeout->step);
		ktd2692_expresswire_write(led, flash_tm_reg
				| KTD2692_REG_FLASH_TIMEOUT_BASE);

		led->mode = KTD2692_MODE_FLASH;
		gpiod_direction_output(led->aux_gpio, KTD2692_HIGH);
	} else {
		led->mode = KTD2692_MODE_DISABLE;
		gpiod_direction_output(led->aux_gpio, KTD2692_LOW);
	}

	ktd2692_expresswire_write(led, led->mode | KTD2692_REG_MODE_BASE);

	fled_cdev->led_cdev.brightness = LED_OFF;
	led->mode = KTD2692_MODE_DISABLE;

	mutex_unlock(&led->lock);

	return 0;
}