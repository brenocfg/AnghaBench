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
typedef  int u32 ;
struct intel_crtc {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct dpll {int m1; int m2; int p1; int p2; int n; int /*<<< orphan*/  dot; int /*<<< orphan*/  vco; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  DPLL (int) ; 
 int DPLL_DVO_2X_MODE ; 
 int DPLL_FPA01_P1_POST_DIV_SHIFT ; 
 int DPLL_VCO_ENABLE ; 
 int DPLL_VGA_MODE_DIS ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP0 (int) ; 
 int /*<<< orphan*/  FP1 (int) ; 
 int /*<<< orphan*/  HBLANK (int) ; 
 int /*<<< orphan*/  HSYNC (int) ; 
 int /*<<< orphan*/  HTOTAL (int) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PIPECONF (int) ; 
 int PIPECONF_ENABLE ; 
 int PIPECONF_PROGRESSIVE ; 
 int /*<<< orphan*/  PIPESRC (int) ; 
 int PLL_P2_DIVIDE_BY_4 ; 
 int PLL_REF_INPUT_DREFCLK ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VBLANK (int) ; 
 int /*<<< orphan*/  VSYNC (int) ; 
 int /*<<< orphan*/  VTOTAL (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int i9xx_calc_dpll_params (int,struct dpll*) ; 
 int i9xx_dpll_compute_fp (struct dpll*) ; 
 struct intel_crtc* intel_get_crtc_for_pipe (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_wait_for_pipe_scanline_moving (struct intel_crtc*) ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void i830_enable_pipe(struct drm_i915_private *dev_priv, enum pipe pipe)
{
	struct intel_crtc *crtc = intel_get_crtc_for_pipe(dev_priv, pipe);
	/* 640x480@60Hz, ~25175 kHz */
	struct dpll clock = {
		.m1 = 18,
		.m2 = 7,
		.p1 = 13,
		.p2 = 4,
		.n = 2,
	};
	u32 dpll, fp;
	int i;

	WARN_ON(i9xx_calc_dpll_params(48000, &clock) != 25154);

	DRM_DEBUG_KMS("enabling pipe %c due to force quirk (vco=%d dot=%d)\n",
		      pipe_name(pipe), clock.vco, clock.dot);

	fp = i9xx_dpll_compute_fp(&clock);
	dpll = DPLL_DVO_2X_MODE |
		DPLL_VGA_MODE_DIS |
		((clock.p1 - 2) << DPLL_FPA01_P1_POST_DIV_SHIFT) |
		PLL_P2_DIVIDE_BY_4 |
		PLL_REF_INPUT_DREFCLK |
		DPLL_VCO_ENABLE;

	I915_WRITE(FP0(pipe), fp);
	I915_WRITE(FP1(pipe), fp);

	I915_WRITE(HTOTAL(pipe), (640 - 1) | ((800 - 1) << 16));
	I915_WRITE(HBLANK(pipe), (640 - 1) | ((800 - 1) << 16));
	I915_WRITE(HSYNC(pipe), (656 - 1) | ((752 - 1) << 16));
	I915_WRITE(VTOTAL(pipe), (480 - 1) | ((525 - 1) << 16));
	I915_WRITE(VBLANK(pipe), (480 - 1) | ((525 - 1) << 16));
	I915_WRITE(VSYNC(pipe), (490 - 1) | ((492 - 1) << 16));
	I915_WRITE(PIPESRC(pipe), ((640 - 1) << 16) | (480 - 1));

	/*
	 * Apparently we need to have VGA mode enabled prior to changing
	 * the P1/P2 dividers. Otherwise the DPLL will keep using the old
	 * dividers, even though the register value does change.
	 */
	I915_WRITE(DPLL(pipe), dpll & ~DPLL_VGA_MODE_DIS);
	I915_WRITE(DPLL(pipe), dpll);

	/* Wait for the clocks to stabilize. */
	POSTING_READ(DPLL(pipe));
	udelay(150);

	/* The pixel multiplier can only be updated once the
	 * DPLL is enabled and the clocks are stable.
	 *
	 * So write it again.
	 */
	I915_WRITE(DPLL(pipe), dpll);

	/* We do this three times for luck */
	for (i = 0; i < 3 ; i++) {
		I915_WRITE(DPLL(pipe), dpll);
		POSTING_READ(DPLL(pipe));
		udelay(150); /* wait for warmup */
	}

	I915_WRITE(PIPECONF(pipe), PIPECONF_ENABLE | PIPECONF_PROGRESSIVE);
	POSTING_READ(PIPECONF(pipe));

	intel_wait_for_pipe_scanline_moving(crtc);
}