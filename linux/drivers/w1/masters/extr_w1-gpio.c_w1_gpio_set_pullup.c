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
typedef  int /*<<< orphan*/  u8 ;
struct w1_gpio_platform_data {int pullup_duration; int /*<<< orphan*/  gpiod; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_raw_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static u8 w1_gpio_set_pullup(void *data, int delay)
{
	struct w1_gpio_platform_data *pdata = data;

	if (delay) {
		pdata->pullup_duration = delay;
	} else {
		if (pdata->pullup_duration) {
			/*
			 * This will OVERRIDE open drain emulation and force-pull
			 * the line high for some time.
			 */
			gpiod_set_raw_value(pdata->gpiod, 1);
			msleep(pdata->pullup_duration);
			/*
			 * This will simply set the line as input since we are doing
			 * open drain emulation in the GPIO library.
			 */
			gpiod_set_value(pdata->gpiod, 1);
		}
		pdata->pullup_duration = 0;
	}

	return 0;
}