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
struct drm_display_mode {int /*<<< orphan*/  clock; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clamp (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static bool rcar_lvds_mode_fixup(struct drm_bridge *bridge,
				 const struct drm_display_mode *mode,
				 struct drm_display_mode *adjusted_mode)
{
	/*
	 * The internal LVDS encoder has a restricted clock frequency operating
	 * range (31MHz to 148.5MHz). Clamp the clock accordingly.
	 */
	adjusted_mode->clock = clamp(adjusted_mode->clock, 31000, 148500);

	return true;
}