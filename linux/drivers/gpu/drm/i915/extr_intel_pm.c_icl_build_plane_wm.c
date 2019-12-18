#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct drm_framebuffer* fb; int /*<<< orphan*/  plane; } ;
struct intel_plane_state {TYPE_2__* linked_plane; TYPE_1__ base; scalar_t__ slave; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_framebuffer {TYPE_3__* format; } ;
typedef  enum plane_id { ____Placeholder_plane_id } plane_id ;
struct TYPE_8__ {int id; } ;
struct TYPE_7__ {int num_planes; int /*<<< orphan*/  is_yuv; } ;
struct TYPE_6__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ intel_wm_plane_visible (struct intel_crtc_state*,struct intel_plane_state const*) ; 
 int skl_build_plane_wm_single (struct intel_crtc_state*,struct intel_plane_state const*,int,int) ; 
 TYPE_4__* to_intel_plane (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int icl_build_plane_wm(struct intel_crtc_state *crtc_state,
			      const struct intel_plane_state *plane_state)
{
	enum plane_id plane_id = to_intel_plane(plane_state->base.plane)->id;
	int ret;

	/* Watermarks calculated in master */
	if (plane_state->slave)
		return 0;

	if (plane_state->linked_plane) {
		const struct drm_framebuffer *fb = plane_state->base.fb;
		enum plane_id y_plane_id = plane_state->linked_plane->id;

		WARN_ON(!intel_wm_plane_visible(crtc_state, plane_state));
		WARN_ON(!fb->format->is_yuv ||
			fb->format->num_planes == 1);

		ret = skl_build_plane_wm_single(crtc_state, plane_state,
						y_plane_id, 0);
		if (ret)
			return ret;

		ret = skl_build_plane_wm_single(crtc_state, plane_state,
						plane_id, 1);
		if (ret)
			return ret;
	} else if (intel_wm_plane_visible(crtc_state, plane_state)) {
		ret = skl_build_plane_wm_single(crtc_state, plane_state,
						plane_id, 0);
		if (ret)
			return ret;
	}

	return 0;
}