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
struct TYPE_2__ {int /*<<< orphan*/  rotation; struct drm_plane* plane; } ;
struct intel_plane_state {TYPE_1__ base; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ROTATE_0 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct intel_plane_state* kzalloc (int,int /*<<< orphan*/ ) ; 

struct intel_plane_state *
intel_create_plane_state(struct drm_plane *plane)
{
	struct intel_plane_state *state;

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (!state)
		return NULL;

	state->base.plane = plane;
	state->base.rotation = DRM_MODE_ROTATE_0;

	return state;
}