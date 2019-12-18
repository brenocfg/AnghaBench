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
struct dce110_link_encoder {int dummy; } ;
typedef  enum dp_panel_mode { ____Placeholder_dp_panel_mode } dp_panel_mode ;

/* Variables and functions */
 int /*<<< orphan*/  DPHY_SCRAMBLER_BS_COUNT ; 
 int /*<<< orphan*/  DP_DPHY_SCRAM_CNTL ; 
 int /*<<< orphan*/  DP_IDLE_BS_INTERVAL ; 
 int /*<<< orphan*/  DP_LINK_FRAMING_CNTL ; 
 int /*<<< orphan*/  DP_VBID_DISABLE ; 
 int /*<<< orphan*/  DP_VID_ENHANCED_FRAME_MODE ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  disable_prbs_mode (struct dce110_link_encoder*) ; 
 int /*<<< orphan*/  enable_phy_bypass_mode (struct dce110_link_encoder*,int) ; 
 int /*<<< orphan*/  set_link_training_complete (struct dce110_link_encoder*,int) ; 
 int /*<<< orphan*/  setup_panel_mode (struct dce110_link_encoder*,int) ; 

__attribute__((used)) static void set_dp_phy_pattern_passthrough_mode(
	struct dce110_link_encoder *enc110,
	enum dp_panel_mode panel_mode)
{
	/* program correct panel mode */
	setup_panel_mode(enc110, panel_mode);

	/* restore LINK_FRAMING_CNTL and DPHY_SCRAMBLER_BS_COUNT
	 * in case we were doing HBR2 compliance pattern before
	 */
	REG_UPDATE_3(DP_LINK_FRAMING_CNTL,
			DP_IDLE_BS_INTERVAL, 0x2000,
			DP_VBID_DISABLE, 0,
			DP_VID_ENHANCED_FRAME_MODE, 1);

	REG_UPDATE(DP_DPHY_SCRAM_CNTL, DPHY_SCRAMBLER_BS_COUNT, 0x1FF);

	/* set link training complete */
	set_link_training_complete(enc110, true);

	/* Disable PHY Bypass mode to setup the test pattern */
	enable_phy_bypass_mode(enc110, false);

	/* Disable PRBS mode */
	disable_prbs_mode(enc110);
}