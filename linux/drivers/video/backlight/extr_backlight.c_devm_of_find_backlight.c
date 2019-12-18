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
struct device {int dummy; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
 struct backlight_device* ERR_PTR (int) ; 
 scalar_t__ IS_ERR_OR_NULL (struct backlight_device*) ; 
 int /*<<< orphan*/  backlight_put (struct backlight_device*) ; 
 int devm_add_action (struct device*,int /*<<< orphan*/ ,struct backlight_device*) ; 
 int /*<<< orphan*/  devm_backlight_release ; 
 struct backlight_device* of_find_backlight (struct device*) ; 

struct backlight_device *devm_of_find_backlight(struct device *dev)
{
	struct backlight_device *bd;
	int ret;

	bd = of_find_backlight(dev);
	if (IS_ERR_OR_NULL(bd))
		return bd;
	ret = devm_add_action(dev, devm_backlight_release, bd);
	if (ret) {
		backlight_put(bd);
		return ERR_PTR(ret);
	}
	return bd;
}