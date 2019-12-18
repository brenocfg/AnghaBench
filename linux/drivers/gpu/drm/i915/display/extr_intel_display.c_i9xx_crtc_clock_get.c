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
struct TYPE_4__ {int dpll; int fp0; int fp1; } ;
struct intel_crtc_state {int cpu_transcoder; int port_clock; TYPE_2__ dpll_hw_state; } ;
struct TYPE_3__ {struct drm_device* dev; } ;
struct intel_crtc {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
struct dpll {int m1; int n; int m2; int p1; int p2; } ;

/* Variables and functions */
 int DISPLAY_RATE_SELECT_FPA1 ; 
 int DPLLB_LVDS_P2_CLOCK_DIV_7 ; 
#define  DPLLB_MODE_DAC_SERIAL 129 
#define  DPLLB_MODE_LVDS 128 
 int DPLL_DAC_SERIAL_P2_CLOCK_DIV_5 ; 
 int DPLL_FPA01_P1_POST_DIV_MASK ; 
 int DPLL_FPA01_P1_POST_DIV_MASK_I830 ; 
 int DPLL_FPA01_P1_POST_DIV_MASK_I830_LVDS ; 
 int DPLL_FPA01_P1_POST_DIV_MASK_PINEVIEW ; 
 int DPLL_FPA01_P1_POST_DIV_SHIFT ; 
 int DPLL_FPA01_P1_POST_DIV_SHIFT_PINEVIEW ; 
 int DPLL_MODE_MASK ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int FP_M1_DIV_MASK ; 
 int FP_M1_DIV_SHIFT ; 
 int FP_M2_DIV_MASK ; 
 int FP_M2_DIV_SHIFT ; 
 int FP_M2_PINEVIEW_DIV_MASK ; 
 int FP_N_DIV_MASK ; 
 int FP_N_DIV_SHIFT ; 
 int FP_N_PINEVIEW_DIV_MASK ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_I830 (struct drm_i915_private*) ; 
 scalar_t__ IS_PINEVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  LVDS ; 
 int LVDS_CLKB_POWER_UP ; 
 int LVDS_PORT_EN ; 
 int PLL_P1_DIVIDE_BY_TWO ; 
 int PLL_P2_DIVIDE_BY_4 ; 
 void* ffs (int) ; 
 int i9xx_calc_dpll_params (int,struct dpll*) ; 
 int i9xx_pll_refclk (struct drm_device*,struct intel_crtc_state*) ; 
 int pnv_calc_dpll_params (int,struct dpll*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void i9xx_crtc_clock_get(struct intel_crtc *crtc,
				struct intel_crtc_state *pipe_config)
{
	struct drm_device *dev = crtc->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	int pipe = pipe_config->cpu_transcoder;
	u32 dpll = pipe_config->dpll_hw_state.dpll;
	u32 fp;
	struct dpll clock;
	int port_clock;
	int refclk = i9xx_pll_refclk(dev, pipe_config);

	if ((dpll & DISPLAY_RATE_SELECT_FPA1) == 0)
		fp = pipe_config->dpll_hw_state.fp0;
	else
		fp = pipe_config->dpll_hw_state.fp1;

	clock.m1 = (fp & FP_M1_DIV_MASK) >> FP_M1_DIV_SHIFT;
	if (IS_PINEVIEW(dev_priv)) {
		clock.n = ffs((fp & FP_N_PINEVIEW_DIV_MASK) >> FP_N_DIV_SHIFT) - 1;
		clock.m2 = (fp & FP_M2_PINEVIEW_DIV_MASK) >> FP_M2_DIV_SHIFT;
	} else {
		clock.n = (fp & FP_N_DIV_MASK) >> FP_N_DIV_SHIFT;
		clock.m2 = (fp & FP_M2_DIV_MASK) >> FP_M2_DIV_SHIFT;
	}

	if (!IS_GEN(dev_priv, 2)) {
		if (IS_PINEVIEW(dev_priv))
			clock.p1 = ffs((dpll & DPLL_FPA01_P1_POST_DIV_MASK_PINEVIEW) >>
				DPLL_FPA01_P1_POST_DIV_SHIFT_PINEVIEW);
		else
			clock.p1 = ffs((dpll & DPLL_FPA01_P1_POST_DIV_MASK) >>
			       DPLL_FPA01_P1_POST_DIV_SHIFT);

		switch (dpll & DPLL_MODE_MASK) {
		case DPLLB_MODE_DAC_SERIAL:
			clock.p2 = dpll & DPLL_DAC_SERIAL_P2_CLOCK_DIV_5 ?
				5 : 10;
			break;
		case DPLLB_MODE_LVDS:
			clock.p2 = dpll & DPLLB_LVDS_P2_CLOCK_DIV_7 ?
				7 : 14;
			break;
		default:
			DRM_DEBUG_KMS("Unknown DPLL mode %08x in programmed "
				  "mode\n", (int)(dpll & DPLL_MODE_MASK));
			return;
		}

		if (IS_PINEVIEW(dev_priv))
			port_clock = pnv_calc_dpll_params(refclk, &clock);
		else
			port_clock = i9xx_calc_dpll_params(refclk, &clock);
	} else {
		u32 lvds = IS_I830(dev_priv) ? 0 : I915_READ(LVDS);
		bool is_lvds = (pipe == 1) && (lvds & LVDS_PORT_EN);

		if (is_lvds) {
			clock.p1 = ffs((dpll & DPLL_FPA01_P1_POST_DIV_MASK_I830_LVDS) >>
				       DPLL_FPA01_P1_POST_DIV_SHIFT);

			if (lvds & LVDS_CLKB_POWER_UP)
				clock.p2 = 7;
			else
				clock.p2 = 14;
		} else {
			if (dpll & PLL_P1_DIVIDE_BY_TWO)
				clock.p1 = 2;
			else {
				clock.p1 = ((dpll & DPLL_FPA01_P1_POST_DIV_MASK_I830) >>
					    DPLL_FPA01_P1_POST_DIV_SHIFT) + 2;
			}
			if (dpll & PLL_P2_DIVIDE_BY_4)
				clock.p2 = 4;
			else
				clock.p2 = 2;
		}

		port_clock = i9xx_calc_dpll_params(refclk, &clock);
	}

	/*
	 * This value includes pixel_multiplier. We will use
	 * port_clock to compute adjusted_mode.crtc_clock in the
	 * encoder's get_config() function.
	 */
	pipe_config->port_clock = port_clock;
}