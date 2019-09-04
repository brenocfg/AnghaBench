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
struct TYPE_2__ {struct drm_plane* plane; int /*<<< orphan*/  alpha; } ;
struct vc4_plane_state {TYPE_1__ base; } ;
struct drm_plane {TYPE_1__* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_BLEND_ALPHA_OPAQUE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (TYPE_1__*) ; 
 struct vc4_plane_state* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vc4_plane_reset(struct drm_plane *plane)
{
	struct vc4_plane_state *vc4_state;

	WARN_ON(plane->state);

	vc4_state = kzalloc(sizeof(*vc4_state), GFP_KERNEL);
	if (!vc4_state)
		return;

	plane->state = &vc4_state->base;
	plane->state->alpha = DRM_BLEND_ALPHA_OPAQUE;
	vc4_state->base.plane = plane;
}