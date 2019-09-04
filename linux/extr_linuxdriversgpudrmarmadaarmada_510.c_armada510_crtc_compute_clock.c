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
typedef  int uint32_t ;
struct drm_display_mode {int clock; } ;
struct clk {int dummy; } ;
struct armada_crtc {int num; struct clk* clk; struct clk** extclk; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int SCLK_510_EXTCLK1 ; 
 int clk_prepare_enable (struct clk*) ; 
 int clk_round_rate (struct clk*,int) ; 
 int /*<<< orphan*/  clk_set_rate (struct clk*,int) ; 

__attribute__((used)) static int armada510_crtc_compute_clock(struct armada_crtc *dcrtc,
	const struct drm_display_mode *mode, uint32_t *sclk)
{
	struct clk *clk = dcrtc->extclk[0];
	int ret;

	if (dcrtc->num == 1)
		return -EINVAL;

	if (IS_ERR(clk))
		return PTR_ERR(clk);

	if (dcrtc->clk != clk) {
		ret = clk_prepare_enable(clk);
		if (ret)
			return ret;
		dcrtc->clk = clk;
	}

	if (sclk) {
		uint32_t rate, ref, div;

		rate = mode->clock * 1000;
		ref = clk_round_rate(clk, rate);
		div = DIV_ROUND_UP(ref, rate);
		if (div < 1)
			div = 1;

		clk_set_rate(clk, ref);
		*sclk = div | SCLK_510_EXTCLK1;
	}

	return 0;
}