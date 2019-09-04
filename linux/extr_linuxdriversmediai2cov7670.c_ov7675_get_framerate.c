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
struct ov7670_info {int clkrc; int clock_speed; TYPE_1__* fmt; scalar_t__ pll_bypass; } ;
struct TYPE_2__ {scalar_t__ mbus_code; } ;

/* Variables and functions */
 scalar_t__ MEDIA_BUS_FMT_SBGGR8_1X8 ; 
 int PLL_FACTOR ; 
 struct ov7670_info* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static void ov7675_get_framerate(struct v4l2_subdev *sd,
				 struct v4l2_fract *tpf)
{
	struct ov7670_info *info = to_state(sd);
	u32 clkrc = info->clkrc;
	int pll_factor;

	if (info->pll_bypass)
		pll_factor = 1;
	else
		pll_factor = PLL_FACTOR;

	clkrc++;
	if (info->fmt->mbus_code == MEDIA_BUS_FMT_SBGGR8_1X8)
		clkrc = (clkrc >> 1);

	tpf->numerator = 1;
	tpf->denominator = (5 * pll_factor * info->clock_speed) /
			(4 * clkrc);
}