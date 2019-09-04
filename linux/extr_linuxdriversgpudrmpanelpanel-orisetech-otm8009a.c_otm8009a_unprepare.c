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
struct otm8009a {int prepared; int /*<<< orphan*/  supply; scalar_t__ reset_gpio; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct otm8009a* panel_to_otm8009a (struct drm_panel*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int otm8009a_unprepare(struct drm_panel *panel)
{
	struct otm8009a *ctx = panel_to_otm8009a(panel);

	if (!ctx->prepared)
		return 0;

	if (ctx->reset_gpio) {
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		msleep(20);
	}

	regulator_disable(ctx->supply);

	ctx->prepared = false;

	return 0;
}