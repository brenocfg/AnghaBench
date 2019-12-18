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
struct sharp_nt_panel {TYPE_2__ base; TYPE_1__* dsi; int /*<<< orphan*/ * backlight; int /*<<< orphan*/ * reset_gpio; int /*<<< orphan*/ * supply; int /*<<< orphan*/ * mode; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  default_mode ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/ * devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_of_find_backlight (struct device*) ; 
 int /*<<< orphan*/ * devm_regulator_get (struct device*,char*) ; 
 int drm_panel_add (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_2__*) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sharp_nt_panel_funcs ; 

__attribute__((used)) static int sharp_nt_panel_add(struct sharp_nt_panel *sharp_nt)
{
	struct device *dev = &sharp_nt->dsi->dev;

	sharp_nt->mode = &default_mode;

	sharp_nt->supply = devm_regulator_get(dev, "avdd");
	if (IS_ERR(sharp_nt->supply))
		return PTR_ERR(sharp_nt->supply);

	sharp_nt->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(sharp_nt->reset_gpio)) {
		dev_err(dev, "cannot get reset-gpios %ld\n",
			PTR_ERR(sharp_nt->reset_gpio));
		sharp_nt->reset_gpio = NULL;
	} else {
		gpiod_set_value(sharp_nt->reset_gpio, 0);
	}

	sharp_nt->backlight = devm_of_find_backlight(dev);

	if (IS_ERR(sharp_nt->backlight))
		return PTR_ERR(sharp_nt->backlight);

	drm_panel_init(&sharp_nt->base);
	sharp_nt->base.funcs = &sharp_nt_panel_funcs;
	sharp_nt->base.dev = &sharp_nt->dsi->dev;

	return drm_panel_add(&sharp_nt->base);
}