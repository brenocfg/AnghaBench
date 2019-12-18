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
struct vkms_crtc_state {struct vkms_crtc_state* active_planes; int /*<<< orphan*/  composer_work; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __drm_atomic_helper_crtc_destroy_state (struct drm_crtc_state*) ; 
 int /*<<< orphan*/  kfree (struct vkms_crtc_state*) ; 
 struct vkms_crtc_state* to_vkms_crtc_state (struct drm_crtc_state*) ; 
 int /*<<< orphan*/  work_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vkms_atomic_crtc_destroy_state(struct drm_crtc *crtc,
					   struct drm_crtc_state *state)
{
	struct vkms_crtc_state *vkms_state = to_vkms_crtc_state(state);

	__drm_atomic_helper_crtc_destroy_state(state);

	WARN_ON(work_pending(&vkms_state->composer_work));
	kfree(vkms_state->active_planes);
	kfree(vkms_state);
}