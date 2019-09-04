#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drm_plane {TYPE_1__* alpha_property; TYPE_2__* state; } ;
struct TYPE_6__ {int /*<<< orphan*/  alpha; int /*<<< orphan*/  rotation; struct drm_plane* plane; } ;
struct TYPE_5__ {int /*<<< orphan*/ * values; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ROTATE_0 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_plane_destroy_state (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 

void drm_atomic_helper_plane_reset(struct drm_plane *plane)
{
	if (plane->state)
		__drm_atomic_helper_plane_destroy_state(plane->state);

	kfree(plane->state);
	plane->state = kzalloc(sizeof(*plane->state), GFP_KERNEL);

	if (plane->state) {
		plane->state->plane = plane;
		plane->state->rotation = DRM_MODE_ROTATE_0;

		/* Reset the alpha value to fully opaque if it matters */
		if (plane->alpha_property)
			plane->state->alpha = plane->alpha_property->values[1];
	}
}