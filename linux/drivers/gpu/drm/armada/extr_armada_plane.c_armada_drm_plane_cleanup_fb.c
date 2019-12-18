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
 int /*<<< orphan*/  drm_framebuffer_put (TYPE_3__*) ; 

void armada_drm_plane_cleanup_fb(struct drm_plane *plane,
	struct drm_plane_state *old_state)
{
	DRM_DEBUG_KMS("[PLANE:%d:%s] [FB:%d]\n",
		plane->base.id, plane->name,
		old_state->fb ? old_state->fb->base.id : 0);

	if (old_state->fb)
		drm_framebuffer_put(old_state->fb);
}