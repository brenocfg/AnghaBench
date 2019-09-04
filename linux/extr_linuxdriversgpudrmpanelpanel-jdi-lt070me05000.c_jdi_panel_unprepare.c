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
struct jdi_panel {int prepared; int /*<<< orphan*/  dcdc_en_gpio; int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  enable_gpio; int /*<<< orphan*/  supplies; TYPE_1__* dsi; } ;
struct drm_panel {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jdi_panel_off (struct jdi_panel*) ; 
 int regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct jdi_panel* to_jdi_panel (struct drm_panel*) ; 

__attribute__((used)) static int jdi_panel_unprepare(struct drm_panel *panel)
{
	struct jdi_panel *jdi = to_jdi_panel(panel);
	struct device *dev = &jdi->dsi->dev;
	int ret;

	if (!jdi->prepared)
		return 0;

	jdi_panel_off(jdi);

	ret = regulator_bulk_disable(ARRAY_SIZE(jdi->supplies), jdi->supplies);
	if (ret < 0)
		dev_err(dev, "regulator disable failed, %d\n", ret);

	gpiod_set_value(jdi->enable_gpio, 0);

	gpiod_set_value(jdi->reset_gpio, 1);

	gpiod_set_value(jdi->dcdc_en_gpio, 0);

	jdi->prepared = false;

	return 0;
}