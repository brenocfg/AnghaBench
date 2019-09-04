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
struct TYPE_3__ {int capabilities; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct tc_data {TYPE_2__ link; int /*<<< orphan*/  dev; } ;

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
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ tc_test_pattern ; 
 int /*<<< orphan*/  tc_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tc_main_link_stream(struct tc_data *tc, int state)
{
	int ret;
	u32 value;

	dev_dbg(tc->dev, "stream: %d\n", state);

	if (state) {
		value = VID_MN_GEN | DP_EN;
		if (tc->link.base.capabilities & DP_LINK_CAP_ENHANCED_FRAMING)
			value |= EF_EN;
		tc_write(DP0CTL, value);
		/*
		 * VID_EN assertion should be delayed by at least N * LSCLK
		 * cycles from the time VID_MN_GEN is enabled in order to
		 * generate stable values for VID_M. LSCLK is 270 MHz or
		 * 162 MHz, VID_N is set to 32768 in  tc_stream_clock_calc(),
		 * so a delay of at least 203 us should suffice.
		 */
		usleep_range(500, 1000);
		value |= VID_EN;
		tc_write(DP0CTL, value);
		/* Set input interface */
		value = DP0_AUDSRC_NO_INPUT;
		if (tc_test_pattern)
			value |= DP0_VIDSRC_COLOR_BAR;
		else
			value |= DP0_VIDSRC_DPI_RX;
		tc_write(SYSCTRL, value);
	} else {
		tc_write(DP0CTL, 0);
	}

	return 0;
err:
	return ret;
}