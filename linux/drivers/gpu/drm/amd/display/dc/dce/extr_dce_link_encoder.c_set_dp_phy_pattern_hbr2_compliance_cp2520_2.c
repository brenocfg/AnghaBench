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
struct TYPE_4__ {TYPE_1__* funcs; } ;
struct dce110_link_encoder {TYPE_2__ base; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* setup ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DPHY_SCRAMBLER_BS_COUNT ; 
 int /*<<< orphan*/  DP_DPHY_HBR2_PATTERN_CONTROL ; 
 int /*<<< orphan*/  DP_DPHY_SCRAM_CNTL ; 
 int /*<<< orphan*/  DP_IDLE_BS_INTERVAL ; 
 int /*<<< orphan*/  DP_LINK_FRAMING_CNTL ; 
 int /*<<< orphan*/  DP_PANEL_MODE_DEFAULT ; 
 int /*<<< orphan*/  DP_VBID_DISABLE ; 
 int /*<<< orphan*/  DP_VID_ENHANCED_FRAME_MODE ; 
 int /*<<< orphan*/  DP_VID_STREAM_CNTL ; 
 int /*<<< orphan*/  DP_VID_STREAM_ENABLE ; 
 scalar_t__ REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  REG_UPDATE_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SIGNAL_TYPE_DISPLAY_PORT ; 
 int /*<<< orphan*/  enable_phy_bypass_mode (struct dce110_link_encoder*,int) ; 
 int /*<<< orphan*/  set_link_training_complete (struct dce110_link_encoder*,int) ; 
 int /*<<< orphan*/  setup_panel_mode (struct dce110_link_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_dp_phy_pattern_hbr2_compliance_cp2520_2(
	struct dce110_link_encoder *enc110,
	unsigned int cp2520_pattern)
{

	/* previously there is a register DP_HBR2_EYE_PATTERN
	 * that is enabled to get the pattern.
	 * But it does not work with the latest spec change,
	 * so we are programming the following registers manually.
	 *
	 * The following settings have been confirmed
	 * by Nick Chorney and Sandra Liu */

	/* Disable PHY Bypass mode to setup the test pattern */

	enable_phy_bypass_mode(enc110, false);

	/* Setup DIG encoder in DP SST mode */
	enc110->base.funcs->setup(&enc110->base, SIGNAL_TYPE_DISPLAY_PORT);

	/* ensure normal panel mode. */
	setup_panel_mode(enc110, DP_PANEL_MODE_DEFAULT);

	/* no vbid after BS (SR)
	 * DP_LINK_FRAMING_CNTL changed history Sandra Liu
	 * 11000260 / 11000104 / 110000FC */
	REG_UPDATE_3(DP_LINK_FRAMING_CNTL,
			DP_IDLE_BS_INTERVAL, 0xFC,
			DP_VBID_DISABLE, 1,
			DP_VID_ENHANCED_FRAME_MODE, 1);

	/* swap every BS with SR */
	REG_UPDATE(DP_DPHY_SCRAM_CNTL, DPHY_SCRAMBLER_BS_COUNT, 0);

	/* select cp2520 patterns */
	if (REG(DP_DPHY_HBR2_PATTERN_CONTROL))
		REG_UPDATE(DP_DPHY_HBR2_PATTERN_CONTROL,
				DP_DPHY_HBR2_PATTERN_CONTROL, cp2520_pattern);
	else
		/* pre-DCE11 can only generate CP2520 pattern 2 */
		ASSERT(cp2520_pattern == 2);

	/* set link training complete */
	set_link_training_complete(enc110, true);

	/* disable video stream */
	REG_UPDATE(DP_VID_STREAM_CNTL, DP_VID_STREAM_ENABLE, 0);

	/* Disable PHY Bypass mode to setup the test pattern */
	enable_phy_bypass_mode(enc110, false);
}