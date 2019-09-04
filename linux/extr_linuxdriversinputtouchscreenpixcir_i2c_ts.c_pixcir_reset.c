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
struct pixcir_i2c_ts_data {int /*<<< orphan*/  gpio_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  ndelay (int) ; 

__attribute__((used)) static void pixcir_reset(struct pixcir_i2c_ts_data *tsdata)
{
	if (!IS_ERR_OR_NULL(tsdata->gpio_reset)) {
		gpiod_set_value_cansleep(tsdata->gpio_reset, 1);
		ndelay(100);	/* datasheet section 1.2.3 says 80ns min. */
		gpiod_set_value_cansleep(tsdata->gpio_reset, 0);
		/* wait for controller ready. 100ms guess. */
		msleep(100);
	}
}