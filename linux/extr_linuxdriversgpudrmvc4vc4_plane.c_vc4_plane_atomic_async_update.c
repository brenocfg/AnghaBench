#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vc4_plane_state {size_t pos0_offset; size_t pos2_offset; size_t ptr0_offset; int /*<<< orphan*/ * hw_dlist; int /*<<< orphan*/ * dlist; } ;
struct drm_plane_state {scalar_t__ fb; int /*<<< orphan*/  src_y; int /*<<< orphan*/  src_x; int /*<<< orphan*/  crtc_y; int /*<<< orphan*/  crtc_x; } ;
struct drm_plane {TYPE_1__* state; } ;
struct TYPE_4__ {scalar_t__ fb; int /*<<< orphan*/  src_y; int /*<<< orphan*/  src_x; int /*<<< orphan*/  crtc_y; int /*<<< orphan*/  crtc_x; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_atomic_set_fb_for_plane (TYPE_1__*,scalar_t__) ; 
 struct vc4_plane_state* to_vc4_plane_state (TYPE_1__*) ; 
 int /*<<< orphan*/  vc4_plane_async_set_fb (struct drm_plane*,scalar_t__) ; 
 int /*<<< orphan*/  vc4_plane_atomic_check (struct drm_plane*,TYPE_1__*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vc4_plane_atomic_async_update(struct drm_plane *plane,
					  struct drm_plane_state *state)
{
	struct vc4_plane_state *vc4_state = to_vc4_plane_state(plane->state);

	if (plane->state->fb != state->fb) {
		vc4_plane_async_set_fb(plane, state->fb);
		drm_atomic_set_fb_for_plane(plane->state, state->fb);
	}

	/* Set the cursor's position on the screen.  This is the
	 * expected change from the drm_mode_cursor_universal()
	 * helper.
	 */
	plane->state->crtc_x = state->crtc_x;
	plane->state->crtc_y = state->crtc_y;

	/* Allow changing the start position within the cursor BO, if
	 * that matters.
	 */
	plane->state->src_x = state->src_x;
	plane->state->src_y = state->src_y;

	/* Update the display list based on the new crtc_x/y. */
	vc4_plane_atomic_check(plane, plane->state);

	/* Note that we can't just call vc4_plane_write_dlist()
	 * because that would smash the context data that the HVS is
	 * currently using.
	 */
	writel(vc4_state->dlist[vc4_state->pos0_offset],
	       &vc4_state->hw_dlist[vc4_state->pos0_offset]);
	writel(vc4_state->dlist[vc4_state->pos2_offset],
	       &vc4_state->hw_dlist[vc4_state->pos2_offset]);
	writel(vc4_state->dlist[vc4_state->ptr0_offset],
	       &vc4_state->hw_dlist[vc4_state->ptr0_offset]);
}