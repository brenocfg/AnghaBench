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
struct drm_plane_state {int src_x; int src_y; int /*<<< orphan*/  fb; struct drm_crtc* crtc; } ;
struct drm_plane {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vbox_crtc_set_base_and_mode (struct drm_crtc*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void vbox_primary_atomic_disable(struct drm_plane *plane,
					struct drm_plane_state *old_state)
{
	struct drm_crtc *crtc = old_state->crtc;

	/* vbox_do_modeset checks plane->state->fb and will disable if NULL */
	vbox_crtc_set_base_and_mode(crtc, old_state->fb,
				    old_state->src_x >> 16,
				    old_state->src_y >> 16);
}