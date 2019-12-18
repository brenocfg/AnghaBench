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
struct gpio_backlight {int /*<<< orphan*/  gpiod; scalar_t__ def_value; TYPE_1__* dev; } ;
struct device_node {int /*<<< orphan*/  phandle; } ;
struct TYPE_2__ {struct device_node* of_node; } ;

/* Variables and functions */
 int FB_BLANK_POWERDOWN ; 
 int FB_BLANK_UNBLANK ; 
 scalar_t__ gpiod_get_value_cansleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gpio_backlight_initial_power_state(struct gpio_backlight *gbl)
{
	struct device_node *node = gbl->dev->of_node;

	/* Not booted with device tree or no phandle link to the node */
	if (!node || !node->phandle)
		return gbl->def_value ? FB_BLANK_UNBLANK : FB_BLANK_POWERDOWN;

	/* if the enable GPIO is disabled, do not enable the backlight */
	if (gpiod_get_value_cansleep(gbl->gpiod) == 0)
		return FB_BLANK_POWERDOWN;

	return FB_BLANK_UNBLANK;
}