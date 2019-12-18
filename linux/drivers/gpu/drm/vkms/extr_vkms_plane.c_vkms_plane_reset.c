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
struct TYPE_2__ {struct drm_plane* plane; } ;
struct vkms_plane_state {TYPE_1__ base; } ;
struct drm_plane {TYPE_1__* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct vkms_plane_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkms_plane_destroy_state (struct drm_plane*,TYPE_1__*) ; 

__attribute__((used)) static void vkms_plane_reset(struct drm_plane *plane)
{
	struct vkms_plane_state *vkms_state;

	if (plane->state)
		vkms_plane_destroy_state(plane, plane->state);

	vkms_state = kzalloc(sizeof(*vkms_state), GFP_KERNEL);
	if (!vkms_state) {
		DRM_ERROR("Cannot allocate vkms_plane_state\n");
		return;
	}

	plane->state = &vkms_state->base;
	plane->state->plane = plane;
}