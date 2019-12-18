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
struct elants_data {int /*<<< orphan*/  vcc33; int /*<<< orphan*/  vccio; int /*<<< orphan*/  reset_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void elants_i2c_power_off(void *_data)
{
	struct elants_data *ts = _data;

	if (!IS_ERR_OR_NULL(ts->reset_gpio)) {
		/*
		 * Activate reset gpio to prevent leakage through the
		 * pin once we shut off power to the controller.
		 */
		gpiod_set_value_cansleep(ts->reset_gpio, 1);
		regulator_disable(ts->vccio);
		regulator_disable(ts->vcc33);
	}
}