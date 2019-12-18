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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int pipe; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PREC_PAL_EXT2_GC_MAX (int,int) ; 
 int /*<<< orphan*/  PREC_PAL_EXT_GC_MAX (int,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ivb_load_lut_ext_max(struct intel_crtc *crtc)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	enum pipe pipe = crtc->pipe;

	/* Program the max register to clamp values > 1.0. */
	I915_WRITE(PREC_PAL_EXT_GC_MAX(pipe, 0), 1 << 16);
	I915_WRITE(PREC_PAL_EXT_GC_MAX(pipe, 1), 1 << 16);
	I915_WRITE(PREC_PAL_EXT_GC_MAX(pipe, 2), 1 << 16);

	/*
	 * Program the gc max 2 register to clamp values > 1.0.
	 * ToDo: Extend the ABI to be able to program values
	 * from 3.0 to 7.0
	 */
	if (INTEL_GEN(dev_priv) >= 10 || IS_GEMINILAKE(dev_priv)) {
		I915_WRITE(PREC_PAL_EXT2_GC_MAX(pipe, 0), 1 << 16);
		I915_WRITE(PREC_PAL_EXT2_GC_MAX(pipe, 1), 1 << 16);
		I915_WRITE(PREC_PAL_EXT2_GC_MAX(pipe, 2), 1 << 16);
	}
}