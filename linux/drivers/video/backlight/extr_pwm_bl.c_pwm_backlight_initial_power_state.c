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
struct pwm_bl_data {int /*<<< orphan*/  pwm; int /*<<< orphan*/  power_supply; scalar_t__ enable_gpio; TYPE_1__* dev; } ;
struct device_node {int /*<<< orphan*/  phandle; } ;
struct TYPE_2__ {struct device_node* of_node; } ;

/* Variables and functions */
 int FB_BLANK_POWERDOWN ; 
 int FB_BLANK_UNBLANK ; 
 scalar_t__ gpiod_get_value_cansleep (scalar_t__) ; 
 int /*<<< orphan*/  pwm_is_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_is_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pwm_backlight_initial_power_state(const struct pwm_bl_data *pb)
{
	struct device_node *node = pb->dev->of_node;

	/* Not booted with device tree or no phandle link to the node */
	if (!node || !node->phandle)
		return FB_BLANK_UNBLANK;

	/*
	 * If the driver is probed from the device tree and there is a
	 * phandle link pointing to the backlight node, it is safe to
	 * assume that another driver will enable the backlight at the
	 * appropriate time. Therefore, if it is disabled, keep it so.
	 */

	/* if the enable GPIO is disabled, do not enable the backlight */
	if (pb->enable_gpio && gpiod_get_value_cansleep(pb->enable_gpio) == 0)
		return FB_BLANK_POWERDOWN;

	/* The regulator is disabled, do not enable the backlight */
	if (!regulator_is_enabled(pb->power_supply))
		return FB_BLANK_POWERDOWN;

	/* The PWM is disabled, keep it like this */
	if (!pwm_is_enabled(pb->pwm))
		return FB_BLANK_POWERDOWN;

	return FB_BLANK_UNBLANK;
}