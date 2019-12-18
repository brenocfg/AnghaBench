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
struct seiko_panel {int prepared; int /*<<< orphan*/  dvdd; int /*<<< orphan*/  avdd; } ;
struct drm_panel {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 struct seiko_panel* to_seiko_panel (struct drm_panel*) ; 

__attribute__((used)) static int seiko_panel_prepare(struct drm_panel *panel)
{
	struct seiko_panel *p = to_seiko_panel(panel);
	int err;

	if (p->prepared)
		return 0;

	err = regulator_enable(p->dvdd);
	if (err < 0) {
		dev_err(panel->dev, "failed to enable dvdd: %d\n", err);
		return err;
	}

	/* Add a 100ms delay as per the panel datasheet */
	msleep(100);

	err = regulator_enable(p->avdd);
	if (err < 0) {
		dev_err(panel->dev, "failed to enable avdd: %d\n", err);
		goto disable_dvdd;
	}

	p->prepared = true;

	return 0;

disable_dvdd:
	regulator_disable(p->dvdd);
	return err;
}