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
struct TYPE_2__ {struct drm_crtc* crtc; } ;
struct vkms_plane_state {struct vkms_plane_state* composer; int /*<<< orphan*/  fb; TYPE_1__ base; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __drm_atomic_helper_plane_destroy_state (struct drm_plane_state*) ; 
 int /*<<< orphan*/  drm_framebuffer_put (int /*<<< orphan*/ *) ; 
 scalar_t__ drm_framebuffer_read_refcount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vkms_plane_state*) ; 
 struct vkms_plane_state* to_vkms_plane_state (struct drm_plane_state*) ; 

__attribute__((used)) static void vkms_plane_destroy_state(struct drm_plane *plane,
				     struct drm_plane_state *old_state)
{
	struct vkms_plane_state *vkms_state = to_vkms_plane_state(old_state);
	struct drm_crtc *crtc = vkms_state->base.crtc;

	if (crtc) {
		/* dropping the reference we acquired in
		 * vkms_primary_plane_update()
		 */
		if (drm_framebuffer_read_refcount(&vkms_state->composer->fb))
			drm_framebuffer_put(&vkms_state->composer->fb);
	}

	kfree(vkms_state->composer);
	vkms_state->composer = NULL;

	__drm_atomic_helper_plane_destroy_state(old_state);
	kfree(vkms_state);
}