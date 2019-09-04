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
struct TYPE_4__ {int visible; int /*<<< orphan*/ * fb; int /*<<< orphan*/  plane; } ;
struct intel_plane_state {TYPE_2__ base; } ;
struct intel_plane {scalar_t__ id; } ;
struct TYPE_3__ {int /*<<< orphan*/  active; } ;
struct intel_crtc_state {TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ PLANE_CURSOR ; 
 struct intel_plane* to_intel_plane (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool intel_wm_plane_visible(const struct intel_crtc_state *crtc_state,
				   const struct intel_plane_state *plane_state)
{
	struct intel_plane *plane = to_intel_plane(plane_state->base.plane);

	/* FIXME check the 'enable' instead */
	if (!crtc_state->base.active)
		return false;

	/*
	 * Treat cursor with fb as always visible since cursor updates
	 * can happen faster than the vrefresh rate, and the current
	 * watermark code doesn't handle that correctly. Cursor updates
	 * which set/clear the fb or change the cursor size are going
	 * to get throttled by intel_legacy_cursor_update() to work
	 * around this problem with the watermark code.
	 */
	if (plane->id == PLANE_CURSOR)
		return plane_state->base.fb != NULL;
	else
		return plane_state->base.visible;
}