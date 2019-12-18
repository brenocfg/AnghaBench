#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct intel_crtc {int dummy; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  CURCNTR (int /*<<< orphan*/ ) ; 
 int DISPLAY_PLANE_ENABLE ; 
 int /*<<< orphan*/  DPLL (int) ; 
 int /*<<< orphan*/  DPLL_VGA_MODE_DIS ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSPCNTR (int /*<<< orphan*/ ) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MCURSOR_MODE ; 
 int /*<<< orphan*/  PIPECONF (int) ; 
 int /*<<< orphan*/  PIPE_A ; 
 int /*<<< orphan*/  PIPE_B ; 
 int /*<<< orphan*/  PLANE_A ; 
 int /*<<< orphan*/  PLANE_B ; 
 int /*<<< orphan*/  PLANE_C ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct intel_crtc* intel_get_crtc_for_pipe (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_wait_for_pipe_scanline_stopped (struct intel_crtc*) ; 
 int /*<<< orphan*/  pipe_name (int) ; 

void i830_disable_pipe(struct drm_i915_private *dev_priv, enum pipe pipe)
{
	struct intel_crtc *crtc = intel_get_crtc_for_pipe(dev_priv, pipe);

	DRM_DEBUG_KMS("disabling pipe %c due to force quirk\n",
		      pipe_name(pipe));

	WARN_ON(I915_READ(DSPCNTR(PLANE_A)) & DISPLAY_PLANE_ENABLE);
	WARN_ON(I915_READ(DSPCNTR(PLANE_B)) & DISPLAY_PLANE_ENABLE);
	WARN_ON(I915_READ(DSPCNTR(PLANE_C)) & DISPLAY_PLANE_ENABLE);
	WARN_ON(I915_READ(CURCNTR(PIPE_A)) & MCURSOR_MODE);
	WARN_ON(I915_READ(CURCNTR(PIPE_B)) & MCURSOR_MODE);

	I915_WRITE(PIPECONF(pipe), 0);
	POSTING_READ(PIPECONF(pipe));

	intel_wait_for_pipe_scanline_stopped(crtc);

	I915_WRITE(DPLL(pipe), DPLL_VGA_MODE_DIS);
	POSTING_READ(DPLL(pipe));
}