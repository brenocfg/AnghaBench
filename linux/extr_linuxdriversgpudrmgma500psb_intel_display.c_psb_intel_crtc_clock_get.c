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
struct psb_pipe {int dpll; int fp0; int fp1; } ;
struct psb_offset {int /*<<< orphan*/  fp1; int /*<<< orphan*/  fp0; int /*<<< orphan*/  dpll; } ;
struct gma_crtc {int pipe; } ;
struct gma_clock_t {int m1; int m2; int n; int p1; int p2; int dot; } ;
struct TYPE_3__ {int saveLVDS; } ;
struct TYPE_4__ {TYPE_1__ psb; struct psb_pipe* pipe; } ;
struct drm_psb_private {TYPE_2__ regs; struct psb_offset* regmap; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int DISPLAY_RATE_SELECT_FPA1 ; 
 int DPLL_FPA01_P1_POST_DIV_MASK_I830 ; 
 int DPLL_FPA01_P1_POST_DIV_MASK_I830_LVDS ; 
 int DPLL_FPA01_P1_POST_DIV_SHIFT ; 
 int FP_M1_DIV_MASK ; 
 int FP_M1_DIV_SHIFT ; 
 int FP_M2_DIV_MASK ; 
 int FP_M2_DIV_SHIFT ; 
 int FP_N_DIV_MASK ; 
 int FP_N_DIV_SHIFT ; 
 int /*<<< orphan*/  LVDS ; 
 int LVDS_PORT_EN ; 
 int PLLB_REF_INPUT_SPREADSPECTRUMIN ; 
 int PLL_P1_DIVIDE_BY_TWO ; 
 int PLL_P2_DIVIDE_BY_4 ; 
 int PLL_REF_INPUT_MASK ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int ffs (int) ; 
 scalar_t__ gma_power_begin (struct drm_device*,int) ; 
 int /*<<< orphan*/  gma_power_end (struct drm_device*) ; 
 int /*<<< orphan*/  psb_intel_clock (int,struct gma_clock_t*) ; 
 struct gma_crtc* to_gma_crtc (struct drm_crtc*) ; 

__attribute__((used)) static int psb_intel_crtc_clock_get(struct drm_device *dev,
				struct drm_crtc *crtc)
{
	struct gma_crtc *gma_crtc = to_gma_crtc(crtc);
	struct drm_psb_private *dev_priv = dev->dev_private;
	int pipe = gma_crtc->pipe;
	const struct psb_offset *map = &dev_priv->regmap[pipe];
	u32 dpll;
	u32 fp;
	struct gma_clock_t clock;
	bool is_lvds;
	struct psb_pipe *p = &dev_priv->regs.pipe[pipe];

	if (gma_power_begin(dev, false)) {
		dpll = REG_READ(map->dpll);
		if ((dpll & DISPLAY_RATE_SELECT_FPA1) == 0)
			fp = REG_READ(map->fp0);
		else
			fp = REG_READ(map->fp1);
		is_lvds = (pipe == 1) && (REG_READ(LVDS) & LVDS_PORT_EN);
		gma_power_end(dev);
	} else {
		dpll = p->dpll;

		if ((dpll & DISPLAY_RATE_SELECT_FPA1) == 0)
			fp = p->fp0;
		else
		        fp = p->fp1;

		is_lvds = (pipe == 1) && (dev_priv->regs.psb.saveLVDS &
								LVDS_PORT_EN);
	}

	clock.m1 = (fp & FP_M1_DIV_MASK) >> FP_M1_DIV_SHIFT;
	clock.m2 = (fp & FP_M2_DIV_MASK) >> FP_M2_DIV_SHIFT;
	clock.n = (fp & FP_N_DIV_MASK) >> FP_N_DIV_SHIFT;

	if (is_lvds) {
		clock.p1 =
		    ffs((dpll &
			 DPLL_FPA01_P1_POST_DIV_MASK_I830_LVDS) >>
			DPLL_FPA01_P1_POST_DIV_SHIFT);
		clock.p2 = 14;

		if ((dpll & PLL_REF_INPUT_MASK) ==
		    PLLB_REF_INPUT_SPREADSPECTRUMIN) {
			/* XXX: might not be 66MHz */
			psb_intel_clock(66000, &clock);
		} else
			psb_intel_clock(48000, &clock);
	} else {
		if (dpll & PLL_P1_DIVIDE_BY_TWO)
			clock.p1 = 2;
		else {
			clock.p1 =
			    ((dpll &
			      DPLL_FPA01_P1_POST_DIV_MASK_I830) >>
			     DPLL_FPA01_P1_POST_DIV_SHIFT) + 2;
		}
		if (dpll & PLL_P2_DIVIDE_BY_4)
			clock.p2 = 4;
		else
			clock.p2 = 2;

		psb_intel_clock(48000, &clock);
	}

	/* XXX: It would be nice to validate the clocks, but we can't reuse
	 * i830PllIsValid() because it relies on the xf86_config connector
	 * configuration being accurate, which it isn't necessarily.
	 */

	return clock.dot;
}