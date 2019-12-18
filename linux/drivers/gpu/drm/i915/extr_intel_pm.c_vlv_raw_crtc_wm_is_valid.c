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
struct intel_crtc_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLANE_CURSOR ; 
 int /*<<< orphan*/  PLANE_PRIMARY ; 
 int /*<<< orphan*/  PLANE_SPRITE0 ; 
 int /*<<< orphan*/  PLANE_SPRITE1 ; 
 scalar_t__ vlv_raw_plane_wm_is_valid (struct intel_crtc_state const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool vlv_raw_crtc_wm_is_valid(const struct intel_crtc_state *crtc_state, int level)
{
	return vlv_raw_plane_wm_is_valid(crtc_state, PLANE_PRIMARY, level) &&
		vlv_raw_plane_wm_is_valid(crtc_state, PLANE_SPRITE0, level) &&
		vlv_raw_plane_wm_is_valid(crtc_state, PLANE_SPRITE1, level) &&
		vlv_raw_plane_wm_is_valid(crtc_state, PLANE_CURSOR, level);
}