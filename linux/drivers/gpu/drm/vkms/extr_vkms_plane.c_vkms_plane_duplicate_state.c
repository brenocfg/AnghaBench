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
struct drm_plane_state {int dummy; } ;
struct vkms_plane_state {struct drm_plane_state base; struct vkms_composer* composer; } ;
struct vkms_composer {int dummy; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_plane_duplicate_state (struct drm_plane*,struct drm_plane_state*) ; 
 int /*<<< orphan*/  kfree (struct vkms_plane_state*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_plane_state *
vkms_plane_duplicate_state(struct drm_plane *plane)
{
	struct vkms_plane_state *vkms_state;
	struct vkms_composer *composer;

	vkms_state = kzalloc(sizeof(*vkms_state), GFP_KERNEL);
	if (!vkms_state)
		return NULL;

	composer = kzalloc(sizeof(*composer), GFP_KERNEL);
	if (!composer) {
		DRM_DEBUG_KMS("Couldn't allocate composer\n");
		kfree(vkms_state);
		return NULL;
	}

	vkms_state->composer = composer;

	__drm_atomic_helper_plane_duplicate_state(plane,
						  &vkms_state->base);

	return &vkms_state->base;
}