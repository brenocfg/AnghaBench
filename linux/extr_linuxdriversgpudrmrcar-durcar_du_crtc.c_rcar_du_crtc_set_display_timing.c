#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct rcar_du_device {int /*<<< orphan*/  dev; TYPE_3__* info; } ;
struct TYPE_6__ {TYPE_1__* state; } ;
struct rcar_du_crtc {int index; TYPE_4__* group; scalar_t__ extclock; scalar_t__ clock; TYPE_2__ crtc; } ;
struct drm_display_mode {int clock; int flags; int htotal; int hsync_start; int hdisplay; int hsync_end; int crtc_vtotal; int crtc_vsync_end; int crtc_vdisplay; int crtc_vsync_start; } ;
struct dpll_info {unsigned long output; int /*<<< orphan*/  m; int /*<<< orphan*/  n; int /*<<< orphan*/  fdpll; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {struct rcar_du_device* dev; } ;
struct TYPE_7__ {int dpll_ch; } ;
struct TYPE_5__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESR ; 
 int /*<<< orphan*/  DEWR ; 
 int DIV_ROUND_CLOSEST (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  DPLLCR ; 
 int DPLLCR_CLKE ; 
 int DPLLCR_CODE ; 
 int DPLLCR_FDPLL (int /*<<< orphan*/ ) ; 
 int DPLLCR_INCS_DOTCLKIN0 ; 
 int DPLLCR_INCS_DOTCLKIN1 ; 
 int DPLLCR_M (int /*<<< orphan*/ ) ; 
 int DPLLCR_N (int /*<<< orphan*/ ) ; 
 int DPLLCR_PLCS0 ; 
 int DPLLCR_PLCS1 ; 
 int DPLLCR_STBY ; 
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 int /*<<< orphan*/  DSMR ; 
 int DSMR_CSPM ; 
 int DSMR_DIPM_DISP ; 
 int DSMR_HSL ; 
 int DSMR_VSL ; 
 int /*<<< orphan*/  ESCR ; 
 int /*<<< orphan*/  ESCR2 ; 
 int ESCR_DCLKSEL_CLKS ; 
 int ESCR_DCLKSEL_DCLKIN ; 
 int /*<<< orphan*/  HCR ; 
 int /*<<< orphan*/  HDER ; 
 int /*<<< orphan*/  HDSR ; 
 int /*<<< orphan*/  HSWR ; 
 int /*<<< orphan*/  OTAR ; 
 int /*<<< orphan*/  OTAR2 ; 
 int /*<<< orphan*/  VCR ; 
 int /*<<< orphan*/  VDER ; 
 int /*<<< orphan*/  VDSR ; 
 int /*<<< orphan*/  VSPR ; 
 scalar_t__ abs (long) ; 
 int clamp (int,unsigned int,unsigned int) ; 
 unsigned long clk_get_rate (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long,unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  rcar_du_crtc_write (struct rcar_du_crtc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcar_du_dpll_divider (struct rcar_du_crtc*,struct dpll_info*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  rcar_du_group_write (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcar_du_r8a7795_es1 ; 
 scalar_t__ soc_device_match (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcar_du_crtc_set_display_timing(struct rcar_du_crtc *rcrtc)
{
	const struct drm_display_mode *mode = &rcrtc->crtc.state->adjusted_mode;
	struct rcar_du_device *rcdu = rcrtc->group->dev;
	unsigned long mode_clock = mode->clock * 1000;
	unsigned long clk;
	u32 value;
	u32 escr;
	u32 div;

	/*
	 * Compute the clock divisor and select the internal or external dot
	 * clock based on the requested frequency.
	 */
	clk = clk_get_rate(rcrtc->clock);
	div = DIV_ROUND_CLOSEST(clk, mode_clock);
	div = clamp(div, 1U, 64U) - 1;
	escr = div | ESCR_DCLKSEL_CLKS;

	if (rcrtc->extclock) {
		struct dpll_info dpll = { 0 };
		unsigned long extclk;
		unsigned long extrate;
		unsigned long rate;
		u32 extdiv;

		extclk = clk_get_rate(rcrtc->extclock);
		if (rcdu->info->dpll_ch & (1 << rcrtc->index)) {
			unsigned long target = mode_clock;

			/*
			 * The H3 ES1.x exhibits dot clock duty cycle stability
			 * issues. We can work around them by configuring the
			 * DPLL to twice the desired frequency, coupled with a
			 * /2 post-divider. This isn't needed on other SoCs and
			 * breaks HDMI output on M3-W for a currently unknown
			 * reason, so restrict the workaround to H3 ES1.x.
			 */
			if (soc_device_match(rcar_du_r8a7795_es1))
				target *= 2;

			rcar_du_dpll_divider(rcrtc, &dpll, extclk, target);
			extclk = dpll.output;
		}

		extdiv = DIV_ROUND_CLOSEST(extclk, mode_clock);
		extdiv = clamp(extdiv, 1U, 64U) - 1;

		rate = clk / (div + 1);
		extrate = extclk / (extdiv + 1);

		if (abs((long)extrate - (long)mode_clock) <
		    abs((long)rate - (long)mode_clock)) {

			if (rcdu->info->dpll_ch & (1 << rcrtc->index)) {
				u32 dpllcr = DPLLCR_CODE | DPLLCR_CLKE
					   | DPLLCR_FDPLL(dpll.fdpll)
					   | DPLLCR_N(dpll.n) | DPLLCR_M(dpll.m)
					   | DPLLCR_STBY;

				if (rcrtc->index == 1)
					dpllcr |= DPLLCR_PLCS1
					       |  DPLLCR_INCS_DOTCLKIN1;
				else
					dpllcr |= DPLLCR_PLCS0
					       |  DPLLCR_INCS_DOTCLKIN0;

				rcar_du_group_write(rcrtc->group, DPLLCR,
						    dpllcr);
			}

			escr = ESCR_DCLKSEL_DCLKIN | extdiv;
		}

		dev_dbg(rcrtc->group->dev->dev,
			"mode clock %lu extrate %lu rate %lu ESCR 0x%08x\n",
			mode_clock, extrate, rate, escr);
	}

	rcar_du_group_write(rcrtc->group, rcrtc->index % 2 ? ESCR2 : ESCR,
			    escr);
	rcar_du_group_write(rcrtc->group, rcrtc->index % 2 ? OTAR2 : OTAR, 0);

	/* Signal polarities */
	value = ((mode->flags & DRM_MODE_FLAG_PVSYNC) ? DSMR_VSL : 0)
	      | ((mode->flags & DRM_MODE_FLAG_PHSYNC) ? DSMR_HSL : 0)
	      | DSMR_DIPM_DISP | DSMR_CSPM;
	rcar_du_crtc_write(rcrtc, DSMR, value);

	/* Display timings */
	rcar_du_crtc_write(rcrtc, HDSR, mode->htotal - mode->hsync_start - 19);
	rcar_du_crtc_write(rcrtc, HDER, mode->htotal - mode->hsync_start +
					mode->hdisplay - 19);
	rcar_du_crtc_write(rcrtc, HSWR, mode->hsync_end -
					mode->hsync_start - 1);
	rcar_du_crtc_write(rcrtc, HCR,  mode->htotal - 1);

	rcar_du_crtc_write(rcrtc, VDSR, mode->crtc_vtotal -
					mode->crtc_vsync_end - 2);
	rcar_du_crtc_write(rcrtc, VDER, mode->crtc_vtotal -
					mode->crtc_vsync_end +
					mode->crtc_vdisplay - 2);
	rcar_du_crtc_write(rcrtc, VSPR, mode->crtc_vtotal -
					mode->crtc_vsync_end +
					mode->crtc_vsync_start - 1);
	rcar_du_crtc_write(rcrtc, VCR,  mode->crtc_vtotal - 1);

	rcar_du_crtc_write(rcrtc, DESR,  mode->htotal - mode->hsync_start - 1);
	rcar_du_crtc_write(rcrtc, DEWR,  mode->hdisplay);
}