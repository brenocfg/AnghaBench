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
struct drm_display_mode {int dummy; } ;
struct tc_data {struct drm_display_mode mode; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 struct tc_data* bridge_to_tc (struct drm_bridge*) ; 

__attribute__((used)) static void tc_bridge_mode_set(struct drm_bridge *bridge,
			       const struct drm_display_mode *mode,
			       const struct drm_display_mode *adj)
{
	struct tc_data *tc = bridge_to_tc(bridge);

	tc->mode = *mode;
}