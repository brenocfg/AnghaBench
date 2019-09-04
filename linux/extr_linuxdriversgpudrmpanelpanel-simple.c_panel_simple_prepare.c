#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct panel_simple {int prepared; TYPE_1__* desc; int /*<<< orphan*/  enable_gpio; int /*<<< orphan*/  supply; } ;
struct drm_panel {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ prepare; } ;
struct TYPE_3__ {TYPE_2__ delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 struct panel_simple* to_panel_simple (struct drm_panel*) ; 

__attribute__((used)) static int panel_simple_prepare(struct drm_panel *panel)
{
	struct panel_simple *p = to_panel_simple(panel);
	int err;

	if (p->prepared)
		return 0;

	err = regulator_enable(p->supply);
	if (err < 0) {
		dev_err(panel->dev, "failed to enable supply: %d\n", err);
		return err;
	}

	gpiod_set_value_cansleep(p->enable_gpio, 1);

	if (p->desc->delay.prepare)
		msleep(p->desc->delay.prepare);

	p->prepared = true;

	return 0;
}