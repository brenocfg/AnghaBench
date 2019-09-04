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
struct dcn10_link_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPHY_PRBS_EN ; 
 int /*<<< orphan*/  DPHY_PRBS_SEL ; 
 int /*<<< orphan*/  DP_DPHY_PRBS_CNTL ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  disable_prbs_symbols (struct dcn10_link_encoder*,int) ; 
 int /*<<< orphan*/  enable_phy_bypass_mode (struct dcn10_link_encoder*,int) ; 

__attribute__((used)) static void set_dp_phy_pattern_prbs7(
	struct dcn10_link_encoder *enc10)
{
	/* Disable PHY Bypass mode to setup the test pattern */
	enable_phy_bypass_mode(enc10, false);

	/* A PRBS7 pattern is used for most DP electrical measurements. */

	/* Enable PRBS symbols on the lanes */
	disable_prbs_symbols(enc10, false);

	/* For PRBS7 Set bit DPHY_PRBS_SEL=0 and Set bit DPHY_PRBS_EN=1 */
	REG_UPDATE_2(DP_DPHY_PRBS_CNTL,
			DPHY_PRBS_SEL, 0,
			DPHY_PRBS_EN, 1);

	/* Enable phy bypass mode to enable the test pattern */
	enable_phy_bypass_mode(enc10, true);
}