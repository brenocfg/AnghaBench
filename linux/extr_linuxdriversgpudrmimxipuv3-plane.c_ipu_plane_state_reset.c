#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  rotation; struct drm_plane* plane; } ;
struct ipu_plane_state {TYPE_1__ base; } ;
struct drm_plane {TYPE_1__* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ROTATE_0 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_plane_destroy_state (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct ipu_plane_state*) ; 
 struct ipu_plane_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct ipu_plane_state* to_ipu_plane_state (TYPE_1__*) ; 

__attribute__((used)) static void ipu_plane_state_reset(struct drm_plane *plane)
{
	struct ipu_plane_state *ipu_state;

	if (plane->state) {
		ipu_state = to_ipu_plane_state(plane->state);
		__drm_atomic_helper_plane_destroy_state(plane->state);
		kfree(ipu_state);
	}

	ipu_state = kzalloc(sizeof(*ipu_state), GFP_KERNEL);

	if (ipu_state) {
		ipu_state->base.plane = plane;
		ipu_state->base.rotation = DRM_MODE_ROTATE_0;
	}

	plane->state = &ipu_state->base;
}