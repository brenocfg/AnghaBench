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
struct sharp_nt_panel {int prepared; scalar_t__ reset_gpio; int /*<<< orphan*/  supply; } ;
struct drm_panel {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int sharp_nt_panel_init (struct sharp_nt_panel*) ; 
 int sharp_nt_panel_on (struct sharp_nt_panel*) ; 
 struct sharp_nt_panel* to_sharp_nt_panel (struct drm_panel*) ; 

__attribute__((used)) static int sharp_nt_panel_prepare(struct drm_panel *panel)
{
	struct sharp_nt_panel *sharp_nt = to_sharp_nt_panel(panel);
	int ret;

	if (sharp_nt->prepared)
		return 0;

	ret = regulator_enable(sharp_nt->supply);
	if (ret < 0)
		return ret;

	msleep(20);

	if (sharp_nt->reset_gpio) {
		gpiod_set_value(sharp_nt->reset_gpio, 1);
		msleep(1);
		gpiod_set_value(sharp_nt->reset_gpio, 0);
		msleep(1);
		gpiod_set_value(sharp_nt->reset_gpio, 1);
		msleep(10);
	}

	ret = sharp_nt_panel_init(sharp_nt);
	if (ret < 0) {
		dev_err(panel->dev, "failed to init panel: %d\n", ret);
		goto poweroff;
	}

	ret = sharp_nt_panel_on(sharp_nt);
	if (ret < 0) {
		dev_err(panel->dev, "failed to set panel on: %d\n", ret);
		goto poweroff;
	}

	sharp_nt->prepared = true;

	return 0;

poweroff:
	regulator_disable(sharp_nt->supply);
	if (sharp_nt->reset_gpio)
		gpiod_set_value(sharp_nt->reset_gpio, 0);
	return ret;
}