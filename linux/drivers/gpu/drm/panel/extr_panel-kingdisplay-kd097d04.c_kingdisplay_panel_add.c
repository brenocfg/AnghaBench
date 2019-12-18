#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct device* dev; int /*<<< orphan*/ * funcs; } ;
struct kingdisplay_panel {TYPE_2__ base; TYPE_1__* link; int /*<<< orphan*/ * backlight; int /*<<< orphan*/ * enable_gpio; int /*<<< orphan*/ * supply; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/ * devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_of_find_backlight (struct device*) ; 
 int /*<<< orphan*/ * devm_regulator_get (struct device*,char*) ; 
 int drm_panel_add (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_2__*) ; 
 int /*<<< orphan*/  kingdisplay_panel_funcs ; 

__attribute__((used)) static int kingdisplay_panel_add(struct kingdisplay_panel *kingdisplay)
{
	struct device *dev = &kingdisplay->link->dev;
	int err;

	kingdisplay->supply = devm_regulator_get(dev, "power");
	if (IS_ERR(kingdisplay->supply))
		return PTR_ERR(kingdisplay->supply);

	kingdisplay->enable_gpio = devm_gpiod_get_optional(dev, "enable",
							   GPIOD_OUT_HIGH);
	if (IS_ERR(kingdisplay->enable_gpio)) {
		err = PTR_ERR(kingdisplay->enable_gpio);
		dev_dbg(dev, "failed to get enable gpio: %d\n", err);
		kingdisplay->enable_gpio = NULL;
	}

	kingdisplay->backlight = devm_of_find_backlight(dev);
	if (IS_ERR(kingdisplay->backlight))
		return PTR_ERR(kingdisplay->backlight);

	drm_panel_init(&kingdisplay->base);
	kingdisplay->base.funcs = &kingdisplay_panel_funcs;
	kingdisplay->base.dev = &kingdisplay->link->dev;

	return drm_panel_add(&kingdisplay->base);
}