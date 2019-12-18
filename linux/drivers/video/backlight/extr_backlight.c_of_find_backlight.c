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
struct device_node {int dummy; } ;
struct device {scalar_t__ of_node; } ;
struct TYPE_2__ {scalar_t__ max_brightness; scalar_t__ brightness; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct backlight_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 struct backlight_device* of_find_backlight_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (scalar_t__,char*,int /*<<< orphan*/ ) ; 

struct backlight_device *of_find_backlight(struct device *dev)
{
	struct backlight_device *bd = NULL;
	struct device_node *np;

	if (!dev)
		return NULL;

	if (IS_ENABLED(CONFIG_OF) && dev->of_node) {
		np = of_parse_phandle(dev->of_node, "backlight", 0);
		if (np) {
			bd = of_find_backlight_by_node(np);
			of_node_put(np);
			if (!bd)
				return ERR_PTR(-EPROBE_DEFER);
			/*
			 * Note: gpio_backlight uses brightness as
			 * power state during probe
			 */
			if (!bd->props.brightness)
				bd->props.brightness = bd->props.max_brightness;
		}
	}

	return bd;
}