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
struct drm_plane_state {int src_x; int src_y; int src_w; int src_h; int /*<<< orphan*/  crtc_h; int /*<<< orphan*/  crtc_w; int /*<<< orphan*/  crtc_y; int /*<<< orphan*/  crtc_x; int /*<<< orphan*/  fb; } ;
struct drm_plane {struct drm_plane_state* state; } ;
struct ade_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ade_update_channel (struct ade_plane*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 struct ade_plane* to_ade_plane (struct drm_plane*) ; 

__attribute__((used)) static void ade_plane_atomic_update(struct drm_plane *plane,
				    struct drm_plane_state *old_state)
{
	struct drm_plane_state	*state	= plane->state;
	struct ade_plane *aplane = to_ade_plane(plane);

	ade_update_channel(aplane, state->fb, state->crtc_x, state->crtc_y,
			   state->crtc_w, state->crtc_h,
			   state->src_x >> 16, state->src_y >> 16,
			   state->src_w >> 16, state->src_h >> 16);
}