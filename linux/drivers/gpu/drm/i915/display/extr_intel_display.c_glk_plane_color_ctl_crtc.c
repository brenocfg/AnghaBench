#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {TYPE_1__* crtc; } ;
struct intel_crtc_state {scalar_t__ csc_enable; scalar_t__ gamma_enable; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PLANE_COLOR_PIPE_CSC_ENABLE ; 
 int /*<<< orphan*/  PLANE_COLOR_PIPE_GAMMA_ENABLE ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

u32 glk_plane_color_ctl_crtc(const struct intel_crtc_state *crtc_state)
{
	struct drm_i915_private *dev_priv = to_i915(crtc_state->base.crtc->dev);
	u32 plane_color_ctl = 0;

	if (INTEL_GEN(dev_priv) >= 11)
		return plane_color_ctl;

	if (crtc_state->gamma_enable)
		plane_color_ctl |= PLANE_COLOR_PIPE_GAMMA_ENABLE;

	if (crtc_state->csc_enable)
		plane_color_ctl |= PLANE_COLOR_PIPE_CSC_ENABLE;

	return plane_color_ctl;
}