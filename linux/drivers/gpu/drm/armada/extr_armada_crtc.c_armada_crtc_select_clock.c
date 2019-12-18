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
typedef  unsigned long u32 ;
struct clk {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; TYPE_1__ base; } ;
struct armada_crtc {TYPE_2__ crtc; } ;
struct armada_clocking_params {int settable; unsigned long div_max; unsigned long permillage_min; unsigned long permillage_max; } ;
struct armada_clk_result {unsigned long desired_clk_hz; unsigned long div; struct clk* clk; } ;

/* Variables and functions */
 int BIT (int) ; 
 unsigned long DIV_ROUND_CLOSEST (unsigned long,unsigned long) ; 
 unsigned long DIV_ROUND_UP (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int ERANGE ; 
 unsigned long clk_get_rate (struct clk*) ; 
 unsigned long clk_round_rate (struct clk*,unsigned long) ; 

int armada_crtc_select_clock(struct armada_crtc *dcrtc,
			     struct armada_clk_result *res,
			     const struct armada_clocking_params *params,
			     struct clk *clks[], size_t num_clks,
			     unsigned long desired_khz)
{
	unsigned long desired_hz = desired_khz * 1000;
	unsigned long desired_clk_hz;	// requested clk input
	unsigned long real_clk_hz;	// actual clk input
	unsigned long real_hz;		// actual pixel clk
	unsigned long permillage;
	struct clk *clk;
	u32 div;
	int i;

	DRM_DEBUG_KMS("[CRTC:%u:%s] desired clock=%luHz\n",
		      dcrtc->crtc.base.id, dcrtc->crtc.name, desired_hz);

	for (i = 0; i < num_clks; i++) {
		clk = clks[i];
		if (!clk)
			continue;

		if (params->settable & BIT(i)) {
			real_clk_hz = clk_round_rate(clk, desired_hz);
			desired_clk_hz = desired_hz;
		} else {
			real_clk_hz = clk_get_rate(clk);
			desired_clk_hz = real_clk_hz;
		}

		/* If the clock can do exactly the desired rate, we're done */
		if (real_clk_hz == desired_hz) {
			real_hz = real_clk_hz;
			div = 1;
			goto found;
		}

		/* Calculate the divider - if invalid, we can't do this rate */
		div = DIV_ROUND_CLOSEST(real_clk_hz, desired_hz);
		if (div == 0 || div > params->div_max)
			continue;

		/* Calculate the actual rate - HDMI requires -0.6%..+0.5% */
		real_hz = DIV_ROUND_CLOSEST(real_clk_hz, div);

		DRM_DEBUG_KMS("[CRTC:%u:%s] clk=%u %luHz div=%u real=%luHz\n",
			dcrtc->crtc.base.id, dcrtc->crtc.name,
			i, real_clk_hz, div, real_hz);

		/* Avoid repeated division */
		if (real_hz < desired_hz) {
			permillage = real_hz / desired_khz;
			if (permillage < params->permillage_min)
				continue;
		} else {
			permillage = DIV_ROUND_UP(real_hz, desired_khz);
			if (permillage > params->permillage_max)
				continue;
		}
		goto found;
	}

	return -ERANGE;

found:
	DRM_DEBUG_KMS("[CRTC:%u:%s] selected clk=%u %luHz div=%u real=%luHz\n",
		dcrtc->crtc.base.id, dcrtc->crtc.name,
		i, real_clk_hz, div, real_hz);

	res->desired_clk_hz = desired_clk_hz;
	res->clk = clk;
	res->div = div;

	return i;
}