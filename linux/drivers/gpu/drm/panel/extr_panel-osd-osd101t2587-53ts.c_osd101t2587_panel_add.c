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
struct osd101t2587_panel {TYPE_2__ base; TYPE_1__* dsi; int /*<<< orphan*/  backlight; int /*<<< orphan*/  supply; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_of_find_backlight (struct device*) ; 
 int /*<<< orphan*/  devm_regulator_get (struct device*,char*) ; 
 int drm_panel_add (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_2__*) ; 
 int /*<<< orphan*/  osd101t2587_panel_funcs ; 

__attribute__((used)) static int osd101t2587_panel_add(struct osd101t2587_panel *osd101t2587)
{
	struct device *dev = &osd101t2587->dsi->dev;

	osd101t2587->supply = devm_regulator_get(dev, "power");
	if (IS_ERR(osd101t2587->supply))
		return PTR_ERR(osd101t2587->supply);

	osd101t2587->backlight = devm_of_find_backlight(dev);
	if (IS_ERR(osd101t2587->backlight))
		return PTR_ERR(osd101t2587->backlight);

	drm_panel_init(&osd101t2587->base);
	osd101t2587->base.funcs = &osd101t2587_panel_funcs;
	osd101t2587->base.dev = &osd101t2587->dsi->dev;

	return drm_panel_add(&osd101t2587->base);
}