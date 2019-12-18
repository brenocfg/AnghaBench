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
struct nt39016 {int /*<<< orphan*/  supply; int /*<<< orphan*/  reset_gpio; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 struct nt39016* to_nt39016 (struct drm_panel*) ; 

__attribute__((used)) static int nt39016_unprepare(struct drm_panel *drm_panel)
{
	struct nt39016 *panel = to_nt39016(drm_panel);

	gpiod_set_value_cansleep(panel->reset_gpio, 1);

	regulator_disable(panel->supply);

	return 0;
}