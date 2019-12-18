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
struct TYPE_3__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {int /*<<< orphan*/  gamma_mode; scalar_t__ csc_enable; scalar_t__ gamma_enable; TYPE_1__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int pipe; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  GAMMA_MODE (int) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  SKL_BOTTOM_COLOR (int) ; 
 int /*<<< orphan*/  SKL_BOTTOM_COLOR_CSC_ENABLE ; 
 int /*<<< orphan*/  SKL_BOTTOM_COLOR_GAMMA_ENABLE ; 
 int /*<<< orphan*/  icl_load_csc_matrix (struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  ilk_load_csc_matrix (struct intel_crtc_state const*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skl_color_commit(const struct intel_crtc_state *crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	enum pipe pipe = crtc->pipe;
	u32 val = 0;

	/*
	 * We don't (yet) allow userspace to control the pipe background color,
	 * so force it to black, but apply pipe gamma and CSC appropriately
	 * so that its handling will match how we program our planes.
	 */
	if (crtc_state->gamma_enable)
		val |= SKL_BOTTOM_COLOR_GAMMA_ENABLE;
	if (crtc_state->csc_enable)
		val |= SKL_BOTTOM_COLOR_CSC_ENABLE;
	I915_WRITE(SKL_BOTTOM_COLOR(pipe), val);

	I915_WRITE(GAMMA_MODE(crtc->pipe), crtc_state->gamma_mode);

	if (INTEL_GEN(dev_priv) >= 11)
		icl_load_csc_matrix(crtc_state);
	else
		ilk_load_csc_matrix(crtc_state);
}