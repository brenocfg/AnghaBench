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
struct raydium_data {int /*<<< orphan*/  avdd; int /*<<< orphan*/  vccio; scalar_t__ reset_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void raydium_i2c_power_off(void *_data)
{
	struct raydium_data *ts = _data;

	if (ts->reset_gpio) {
		gpiod_set_value_cansleep(ts->reset_gpio, 1);
		regulator_disable(ts->vccio);
		regulator_disable(ts->avdd);
	}
}