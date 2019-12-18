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
typedef  int u32 ;
struct TYPE_6__ {int n; int m2; int m1; int p1; int p2; int vco; } ;
struct TYPE_5__ {int dpll; } ;
struct intel_crtc_state {TYPE_3__ dpll; TYPE_2__ dpll_hw_state; } ;
struct TYPE_4__ {struct drm_device* dev; } ;
struct intel_crtc {int pipe; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
typedef  enum dpio_channel { ____Placeholder_dpio_channel } dpio_channel ;

/* Variables and functions */
 int /*<<< orphan*/  CHV_CMN_DW13 (int) ; 
 int /*<<< orphan*/  CHV_CMN_DW14 (int) ; 
 int /*<<< orphan*/  CHV_PLL_DW0 (int) ; 
 int /*<<< orphan*/  CHV_PLL_DW1 (int) ; 
 int /*<<< orphan*/  CHV_PLL_DW2 (int) ; 
 int /*<<< orphan*/  CHV_PLL_DW3 (int) ; 
 int /*<<< orphan*/  CHV_PLL_DW6 (int) ; 
 int /*<<< orphan*/  CHV_PLL_DW8 (int) ; 
 int /*<<< orphan*/  CHV_PLL_DW9 (int) ; 
 int DPIO_AFC_RECAL ; 
 int DPIO_CHV_FEEDFWD_GAIN_MASK ; 
 int DPIO_CHV_FEEDFWD_GAIN_SHIFT ; 
 int DPIO_CHV_FRAC_DIV_EN ; 
 int DPIO_CHV_GAIN_CTRL_SHIFT ; 
 int DPIO_CHV_INT_COEFF_SHIFT ; 
 int DPIO_CHV_INT_LOCK_THRESHOLD_MASK ; 
 int DPIO_CHV_INT_LOCK_THRESHOLD_SEL_COARSE ; 
 int DPIO_CHV_INT_LOCK_THRESHOLD_SHIFT ; 
 int DPIO_CHV_K_DIV_SHIFT ; 
 int DPIO_CHV_M1_DIV_BY_2 ; 
 int DPIO_CHV_N_DIV_SHIFT ; 
 int DPIO_CHV_P1_DIV_SHIFT ; 
 int DPIO_CHV_P2_DIV_SHIFT ; 
 int DPIO_CHV_PROP_COEFF_SHIFT ; 
 int DPIO_CHV_S1_DIV_SHIFT ; 
 int DPIO_CHV_TDC_TARGET_CNT_MASK ; 
 int DPIO_CHV_TDC_TARGET_CNT_SHIFT ; 
 int /*<<< orphan*/  DPLL (int) ; 
 int DPLL_VCO_ENABLE ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 int /*<<< orphan*/  vlv_dpio_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vlv_dpio_put (struct drm_i915_private*) ; 
 int vlv_dpio_read (struct drm_i915_private*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_dpio_write (struct drm_i915_private*,int,int /*<<< orphan*/ ,int) ; 
 int vlv_pipe_to_channel (int) ; 

__attribute__((used)) static void chv_prepare_pll(struct intel_crtc *crtc,
			    const struct intel_crtc_state *pipe_config)
{
	struct drm_device *dev = crtc->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	enum pipe pipe = crtc->pipe;
	enum dpio_channel port = vlv_pipe_to_channel(pipe);
	u32 loopfilter, tribuf_calcntr;
	u32 bestn, bestm1, bestm2, bestp1, bestp2, bestm2_frac;
	u32 dpio_val;
	int vco;

	/* Enable Refclk and SSC */
	I915_WRITE(DPLL(pipe),
		   pipe_config->dpll_hw_state.dpll & ~DPLL_VCO_ENABLE);

	/* No need to actually set up the DPLL with DSI */
	if ((pipe_config->dpll_hw_state.dpll & DPLL_VCO_ENABLE) == 0)
		return;

	bestn = pipe_config->dpll.n;
	bestm2_frac = pipe_config->dpll.m2 & 0x3fffff;
	bestm1 = pipe_config->dpll.m1;
	bestm2 = pipe_config->dpll.m2 >> 22;
	bestp1 = pipe_config->dpll.p1;
	bestp2 = pipe_config->dpll.p2;
	vco = pipe_config->dpll.vco;
	dpio_val = 0;
	loopfilter = 0;

	vlv_dpio_get(dev_priv);

	/* p1 and p2 divider */
	vlv_dpio_write(dev_priv, pipe, CHV_CMN_DW13(port),
			5 << DPIO_CHV_S1_DIV_SHIFT |
			bestp1 << DPIO_CHV_P1_DIV_SHIFT |
			bestp2 << DPIO_CHV_P2_DIV_SHIFT |
			1 << DPIO_CHV_K_DIV_SHIFT);

	/* Feedback post-divider - m2 */
	vlv_dpio_write(dev_priv, pipe, CHV_PLL_DW0(port), bestm2);

	/* Feedback refclk divider - n and m1 */
	vlv_dpio_write(dev_priv, pipe, CHV_PLL_DW1(port),
			DPIO_CHV_M1_DIV_BY_2 |
			1 << DPIO_CHV_N_DIV_SHIFT);

	/* M2 fraction division */
	vlv_dpio_write(dev_priv, pipe, CHV_PLL_DW2(port), bestm2_frac);

	/* M2 fraction division enable */
	dpio_val = vlv_dpio_read(dev_priv, pipe, CHV_PLL_DW3(port));
	dpio_val &= ~(DPIO_CHV_FEEDFWD_GAIN_MASK | DPIO_CHV_FRAC_DIV_EN);
	dpio_val |= (2 << DPIO_CHV_FEEDFWD_GAIN_SHIFT);
	if (bestm2_frac)
		dpio_val |= DPIO_CHV_FRAC_DIV_EN;
	vlv_dpio_write(dev_priv, pipe, CHV_PLL_DW3(port), dpio_val);

	/* Program digital lock detect threshold */
	dpio_val = vlv_dpio_read(dev_priv, pipe, CHV_PLL_DW9(port));
	dpio_val &= ~(DPIO_CHV_INT_LOCK_THRESHOLD_MASK |
					DPIO_CHV_INT_LOCK_THRESHOLD_SEL_COARSE);
	dpio_val |= (0x5 << DPIO_CHV_INT_LOCK_THRESHOLD_SHIFT);
	if (!bestm2_frac)
		dpio_val |= DPIO_CHV_INT_LOCK_THRESHOLD_SEL_COARSE;
	vlv_dpio_write(dev_priv, pipe, CHV_PLL_DW9(port), dpio_val);

	/* Loop filter */
	if (vco == 5400000) {
		loopfilter |= (0x3 << DPIO_CHV_PROP_COEFF_SHIFT);
		loopfilter |= (0x8 << DPIO_CHV_INT_COEFF_SHIFT);
		loopfilter |= (0x1 << DPIO_CHV_GAIN_CTRL_SHIFT);
		tribuf_calcntr = 0x9;
	} else if (vco <= 6200000) {
		loopfilter |= (0x5 << DPIO_CHV_PROP_COEFF_SHIFT);
		loopfilter |= (0xB << DPIO_CHV_INT_COEFF_SHIFT);
		loopfilter |= (0x3 << DPIO_CHV_GAIN_CTRL_SHIFT);
		tribuf_calcntr = 0x9;
	} else if (vco <= 6480000) {
		loopfilter |= (0x4 << DPIO_CHV_PROP_COEFF_SHIFT);
		loopfilter |= (0x9 << DPIO_CHV_INT_COEFF_SHIFT);
		loopfilter |= (0x3 << DPIO_CHV_GAIN_CTRL_SHIFT);
		tribuf_calcntr = 0x8;
	} else {
		/* Not supported. Apply the same limits as in the max case */
		loopfilter |= (0x4 << DPIO_CHV_PROP_COEFF_SHIFT);
		loopfilter |= (0x9 << DPIO_CHV_INT_COEFF_SHIFT);
		loopfilter |= (0x3 << DPIO_CHV_GAIN_CTRL_SHIFT);
		tribuf_calcntr = 0;
	}
	vlv_dpio_write(dev_priv, pipe, CHV_PLL_DW6(port), loopfilter);

	dpio_val = vlv_dpio_read(dev_priv, pipe, CHV_PLL_DW8(port));
	dpio_val &= ~DPIO_CHV_TDC_TARGET_CNT_MASK;
	dpio_val |= (tribuf_calcntr << DPIO_CHV_TDC_TARGET_CNT_SHIFT);
	vlv_dpio_write(dev_priv, pipe, CHV_PLL_DW8(port), dpio_val);

	/* AFC Recal */
	vlv_dpio_write(dev_priv, pipe, CHV_CMN_DW14(port),
			vlv_dpio_read(dev_priv, pipe, CHV_CMN_DW14(port)) |
			DPIO_AFC_RECAL);

	vlv_dpio_put(dev_priv);
}