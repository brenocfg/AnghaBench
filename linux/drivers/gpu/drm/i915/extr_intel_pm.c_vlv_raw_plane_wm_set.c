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
typedef  scalar_t__ u16 ;
struct TYPE_5__ {struct g4x_pipe_wm* raw; } ;
struct TYPE_6__ {TYPE_1__ vlv; } ;
struct TYPE_8__ {TYPE_3__* crtc; } ;
struct intel_crtc_state {TYPE_2__ wm; TYPE_4__ base; } ;
struct g4x_pipe_wm {scalar_t__* plane; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum plane_id { ____Placeholder_plane_id } plane_id ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int intel_wm_num_levels (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool vlv_raw_plane_wm_set(struct intel_crtc_state *crtc_state,
				 int level, enum plane_id plane_id, u16 value)
{
	struct drm_i915_private *dev_priv = to_i915(crtc_state->base.crtc->dev);
	int num_levels = intel_wm_num_levels(dev_priv);
	bool dirty = false;

	for (; level < num_levels; level++) {
		struct g4x_pipe_wm *raw = &crtc_state->wm.vlv.raw[level];

		dirty |= raw->plane[plane_id] != value;
		raw->plane[plane_id] = value;
	}

	return dirty;
}