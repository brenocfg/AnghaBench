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
struct tc_data {int /*<<< orphan*/  panel; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 struct tc_data* bridge_to_tc (struct drm_bridge*) ; 
 int /*<<< orphan*/  drm_panel_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tc_bridge_post_disable(struct drm_bridge *bridge)
{
	struct tc_data *tc = bridge_to_tc(bridge);

	drm_panel_unprepare(tc->panel);
}