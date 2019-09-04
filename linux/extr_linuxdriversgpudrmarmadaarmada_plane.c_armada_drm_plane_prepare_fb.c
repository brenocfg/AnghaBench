#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_plane_state {TYPE_3__* fb; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct drm_plane {int /*<<< orphan*/  name; TYPE_1__ base; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_framebuffer_get (TYPE_3__*) ; 

int armada_drm_plane_prepare_fb(struct drm_plane *plane,
	struct drm_plane_state *state)
{
	DRM_DEBUG_KMS("[PLANE:%d:%s] [FB:%d]\n",
		plane->base.id, plane->name,
		state->fb ? state->fb->base.id : 0);

	/*
	 * Take a reference on the new framebuffer - we want to
	 * hold on to it while the hardware is displaying it.
	 */
	if (state->fb)
		drm_framebuffer_get(state->fb);
	return 0;
}