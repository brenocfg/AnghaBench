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
typedef  int u32 ;
struct intel_plane {int i9xx_plane; } ;
struct TYPE_3__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {int gamma_enable; int csc_enable; TYPE_1__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  primary; } ;
struct intel_crtc {TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum i9xx_plane_id { ____Placeholder_i9xx_plane_id } i9xx_plane_id ;

/* Variables and functions */
 int DISPPLANE_GAMMA_ENABLE ; 
 int DISPPLANE_PIPE_CSC_ENABLE ; 
 int /*<<< orphan*/  DSPCNTR (int) ; 
 int /*<<< orphan*/  HAS_GMCH (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 
 struct intel_plane* to_intel_plane (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i9xx_get_pipe_color_config(struct intel_crtc_state *crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);
	struct intel_plane *plane = to_intel_plane(crtc->base.primary);
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	enum i9xx_plane_id i9xx_plane = plane->i9xx_plane;
	u32 tmp;

	tmp = I915_READ(DSPCNTR(i9xx_plane));

	if (tmp & DISPPLANE_GAMMA_ENABLE)
		crtc_state->gamma_enable = true;

	if (!HAS_GMCH(dev_priv) &&
	    tmp & DISPPLANE_PIPE_CSC_ENABLE)
		crtc_state->csc_enable = true;
}