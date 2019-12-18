#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_7__ {unsigned int rotation; int /*<<< orphan*/  visible; struct drm_framebuffer* fb; int /*<<< orphan*/  plane; } ;
struct intel_plane_state {TYPE_2__* color_plane; TYPE_1__ base; } ;
struct TYPE_11__ {int /*<<< orphan*/  id; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; TYPE_5__ base; } ;
struct intel_plane {scalar_t__ (* max_stride ) (struct intel_plane*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ;TYPE_6__ base; } ;
struct TYPE_10__ {int /*<<< orphan*/  id; } ;
struct drm_framebuffer {TYPE_4__ base; int /*<<< orphan*/  modifier; TYPE_3__* format; } ;
struct TYPE_9__ {int /*<<< orphan*/  format; } ;
struct TYPE_8__ {scalar_t__ stride; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int EINVAL ; 
 scalar_t__ intel_plane_can_remap (struct intel_plane_state const*) ; 
 scalar_t__ stub1 (struct intel_plane*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct intel_plane* to_intel_plane (int /*<<< orphan*/ ) ; 

int intel_plane_check_stride(const struct intel_plane_state *plane_state)
{
	struct intel_plane *plane = to_intel_plane(plane_state->base.plane);
	const struct drm_framebuffer *fb = plane_state->base.fb;
	unsigned int rotation = plane_state->base.rotation;
	u32 stride, max_stride;

	/*
	 * We ignore stride for all invisible planes that
	 * can be remapped. Otherwise we could end up
	 * with a false positive when the remapping didn't
	 * kick in due the plane being invisible.
	 */
	if (intel_plane_can_remap(plane_state) &&
	    !plane_state->base.visible)
		return 0;

	/* FIXME other color planes? */
	stride = plane_state->color_plane[0].stride;
	max_stride = plane->max_stride(plane, fb->format->format,
				       fb->modifier, rotation);

	if (stride > max_stride) {
		DRM_DEBUG_KMS("[FB:%d] stride (%d) exceeds [PLANE:%d:%s] max stride (%d)\n",
			      fb->base.id, stride,
			      plane->base.base.id, plane->base.name, max_stride);
		return -EINVAL;
	}

	return 0;
}