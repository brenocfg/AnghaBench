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

/* Variables and functions */
 int /*<<< orphan*/  GPIO_LED_BLINK ; 
 int /*<<< orphan*/  GPIO_LED_NO_BLINK_LOW ; 
 int /*<<< orphan*/  H1940_LATCH_BLUETOOTH_POWER ; 
 int /*<<< orphan*/  S3C2410_GPH (int) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  h1940_led_blink_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void h1940bt_enable(int on)
{
	if (on) {
		/* Power on the chip */
		gpio_set_value(H1940_LATCH_BLUETOOTH_POWER, 1);
		/* Reset the chip */
		mdelay(10);

		gpio_set_value(S3C2410_GPH(1), 1);
		mdelay(10);
		gpio_set_value(S3C2410_GPH(1), 0);

		h1940_led_blink_set(NULL, GPIO_LED_BLINK, NULL, NULL);
	}
	else {
		gpio_set_value(S3C2410_GPH(1), 1);
		mdelay(10);
		gpio_set_value(S3C2410_GPH(1), 0);
		mdelay(10);
		gpio_set_value(H1940_LATCH_BLUETOOTH_POWER, 0);

		h1940_led_blink_set(NULL, GPIO_LED_NO_BLINK_LOW, NULL, NULL);
	}
}