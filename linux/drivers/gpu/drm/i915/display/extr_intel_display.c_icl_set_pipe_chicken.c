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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int pipe; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PER_PIXEL_ALPHA_BYPASS_EN ; 
 int /*<<< orphan*/  PIPE_CHICKEN (int) ; 
 int /*<<< orphan*/  PIXEL_ROUNDING_TRUNC_FB_PASSTHRU ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void icl_set_pipe_chicken(struct intel_crtc *crtc)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	enum pipe pipe = crtc->pipe;
	u32 tmp;

	tmp = I915_READ(PIPE_CHICKEN(pipe));

	/*
	 * Display WA #1153: icl
	 * enable hardware to bypass the alpha math
	 * and rounding for per-pixel values 00 and 0xff
	 */
	tmp |= PER_PIXEL_ALPHA_BYPASS_EN;
	/*
	 * Display WA # 1605353570: icl
	 * Set the pixel rounding bit to 1 for allowing
	 * passthrough of Frame buffer pixels unmodified
	 * across pipe
	 */
	tmp |= PIXEL_ROUNDING_TRUNC_FB_PASSTHRU;
	I915_WRITE(PIPE_CHICKEN(pipe), tmp);
}