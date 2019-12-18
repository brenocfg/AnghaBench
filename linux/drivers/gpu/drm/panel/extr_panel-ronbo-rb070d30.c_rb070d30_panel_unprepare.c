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
struct TYPE_2__ {int /*<<< orphan*/  power; int /*<<< orphan*/  reset; } ;
struct rb070d30_panel {int /*<<< orphan*/  supply; TYPE_1__ gpios; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rb070d30_panel* panel_to_rb070d30_panel (struct drm_panel*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rb070d30_panel_unprepare(struct drm_panel *panel)
{
	struct rb070d30_panel *ctx = panel_to_rb070d30_panel(panel);

	gpiod_set_value(ctx->gpios.reset, 0);
	gpiod_set_value(ctx->gpios.power, 0);
	regulator_disable(ctx->supply);

	return 0;
}