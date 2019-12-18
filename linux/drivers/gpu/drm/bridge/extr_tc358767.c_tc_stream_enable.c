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
struct TYPE_4__ {int capabilities; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct TYPE_6__ {int clock; } ;
struct tc_data {int /*<<< orphan*/  regmap; TYPE_2__ link; TYPE_3__ mode; int /*<<< orphan*/  refclk; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP0CTL ; 
 int DP0_AUDSRC_NO_INPUT ; 
 int DP0_VIDSRC_COLOR_BAR ; 
 int DP0_VIDSRC_DPI_RX ; 
 int DP_EN ; 
 int DP_LINK_CAP_ENHANCED_FRAMING ; 
 int EF_EN ; 
 int /*<<< orphan*/  SYSCTRL ; 
 int VID_EN ; 
 int VID_MN_GEN ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int tc_pxl_pll_en (struct tc_data*,int /*<<< orphan*/ ,int) ; 
 int tc_set_video_mode (struct tc_data*,TYPE_3__*) ; 
 int tc_stream_clock_calc (struct tc_data*) ; 
 scalar_t__ tc_test_pattern ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tc_stream_enable(struct tc_data *tc)
{
	int ret;
	u32 value;

	dev_dbg(tc->dev, "enable video stream\n");

	/* PXL PLL setup */
	if (tc_test_pattern) {
		ret = tc_pxl_pll_en(tc, clk_get_rate(tc->refclk),
				    1000 * tc->mode.clock);
		if (ret)
			return ret;
	}

	ret = tc_set_video_mode(tc, &tc->mode);
	if (ret)
		return ret;

	/* Set M/N */
	ret = tc_stream_clock_calc(tc);
	if (ret)
		return ret;

	value = VID_MN_GEN | DP_EN;
	if (tc->link.base.capabilities & DP_LINK_CAP_ENHANCED_FRAMING)
		value |= EF_EN;
	ret = regmap_write(tc->regmap, DP0CTL, value);
	if (ret)
		return ret;
	/*
	 * VID_EN assertion should be delayed by at least N * LSCLK
	 * cycles from the time VID_MN_GEN is enabled in order to
	 * generate stable values for VID_M. LSCLK is 270 MHz or
	 * 162 MHz, VID_N is set to 32768 in  tc_stream_clock_calc(),
	 * so a delay of at least 203 us should suffice.
	 */
	usleep_range(500, 1000);
	value |= VID_EN;
	ret = regmap_write(tc->regmap, DP0CTL, value);
	if (ret)
		return ret;
	/* Set input interface */
	value = DP0_AUDSRC_NO_INPUT;
	if (tc_test_pattern)
		value |= DP0_VIDSRC_COLOR_BAR;
	else
		value |= DP0_VIDSRC_DPI_RX;
	ret = regmap_write(tc->regmap, SYSCTRL, value);
	if (ret)
		return ret;

	return 0;
}