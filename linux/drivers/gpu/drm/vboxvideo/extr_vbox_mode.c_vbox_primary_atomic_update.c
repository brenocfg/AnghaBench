#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_plane_state {int dummy; } ;
struct drm_plane {TYPE_1__* state; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_2__ {int src_x; int src_y; struct drm_framebuffer* fb; struct drm_crtc* crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  vbox_crtc_set_base_and_mode (struct drm_crtc*,struct drm_framebuffer*,int,int) ; 

__attribute__((used)) static void vbox_primary_atomic_update(struct drm_plane *plane,
				       struct drm_plane_state *old_state)
{
	struct drm_crtc *crtc = plane->state->crtc;
	struct drm_framebuffer *fb = plane->state->fb;

	vbox_crtc_set_base_and_mode(crtc, fb,
				    plane->state->src_x >> 16,
				    plane->state->src_y >> 16);
}