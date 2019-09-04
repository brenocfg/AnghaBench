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
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_fract {int numerator; int denominator; } ;
struct ov7670_info {int clock_speed; int clkrc; TYPE_1__* fmt; scalar_t__ pll_bypass; } ;
struct TYPE_2__ {scalar_t__ mbus_code; } ;

/* Variables and functions */
 int CLK_EXT ; 
 int CLK_SCALE ; 
 int DBLV_BYPASS ; 
 int DBLV_X4 ; 
 scalar_t__ MEDIA_BUS_FMT_SBGGR8_1X8 ; 
 int PLL_FACTOR ; 
 int /*<<< orphan*/  REG_CLKRC ; 
 int /*<<< orphan*/  REG_DBLV ; 
 int ov7670_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ov7675_get_framerate (struct v4l2_subdev*,struct v4l2_fract*) ; 
 struct ov7670_info* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov7675_set_framerate(struct v4l2_subdev *sd,
				 struct v4l2_fract *tpf)
{
	struct ov7670_info *info = to_state(sd);
	u32 clkrc;
	int pll_factor;
	int ret;

	/*
	 * The formula is fps = 5/4*pixclk for YUV/RGB and
	 * fps = 5/2*pixclk for RAW.
	 *
	 * pixclk = clock_speed / (clkrc + 1) * PLLfactor
	 *
	 */
	if (info->pll_bypass) {
		pll_factor = 1;
		ret = ov7670_write(sd, REG_DBLV, DBLV_BYPASS);
	} else {
		pll_factor = PLL_FACTOR;
		ret = ov7670_write(sd, REG_DBLV, DBLV_X4);
	}
	if (ret < 0)
		return ret;

	if (tpf->numerator == 0 || tpf->denominator == 0) {
		clkrc = 0;
	} else {
		clkrc = (5 * pll_factor * info->clock_speed * tpf->numerator) /
			(4 * tpf->denominator);
		if (info->fmt->mbus_code == MEDIA_BUS_FMT_SBGGR8_1X8)
			clkrc = (clkrc << 1);
		clkrc--;
	}

	/*
	 * The datasheet claims that clkrc = 0 will divide the input clock by 1
	 * but we've checked with an oscilloscope that it divides by 2 instead.
	 * So, if clkrc = 0 just bypass the divider.
	 */
	if (clkrc <= 0)
		clkrc = CLK_EXT;
	else if (clkrc > CLK_SCALE)
		clkrc = CLK_SCALE;
	info->clkrc = clkrc;

	/* Recalculate frame rate */
	ov7675_get_framerate(sd, tpf);

	ret = ov7670_write(sd, REG_CLKRC, info->clkrc);
	if (ret < 0)
		return ret;

	return ov7670_write(sd, REG_DBLV, DBLV_X4);
}