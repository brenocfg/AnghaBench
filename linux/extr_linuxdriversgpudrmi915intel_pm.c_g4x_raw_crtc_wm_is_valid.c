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
struct TYPE_5__ {TYPE_1__* crtc; } ;
struct intel_crtc_state {TYPE_2__ base; } ;
struct TYPE_6__ {int max_level; } ;
struct drm_i915_private {TYPE_3__ wm; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLANE_CURSOR ; 
 int /*<<< orphan*/  PLANE_PRIMARY ; 
 int /*<<< orphan*/  PLANE_SPRITE0 ; 
 scalar_t__ g4x_raw_plane_wm_is_valid (struct intel_crtc_state const*,int /*<<< orphan*/ ,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool g4x_raw_crtc_wm_is_valid(const struct intel_crtc_state *crtc_state,
				     int level)
{
	struct drm_i915_private *dev_priv = to_i915(crtc_state->base.crtc->dev);

	if (level > dev_priv->wm.max_level)
		return false;

	return g4x_raw_plane_wm_is_valid(crtc_state, PLANE_PRIMARY, level) &&
		g4x_raw_plane_wm_is_valid(crtc_state, PLANE_SPRITE0, level) &&
		g4x_raw_plane_wm_is_valid(crtc_state, PLANE_CURSOR, level);
}