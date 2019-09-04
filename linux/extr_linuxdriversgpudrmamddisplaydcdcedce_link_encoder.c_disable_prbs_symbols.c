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

/* Variables and functions */
 int /*<<< orphan*/  DPHY_ATEST_SEL_LANE0 ; 
 int /*<<< orphan*/  DPHY_ATEST_SEL_LANE1 ; 
 int /*<<< orphan*/  DPHY_ATEST_SEL_LANE2 ; 
 int /*<<< orphan*/  DPHY_ATEST_SEL_LANE3 ; 
 int /*<<< orphan*/  DP_DPHY_CNTL ; 
 int /*<<< orphan*/  REG_UPDATE_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void disable_prbs_symbols(
	struct dce110_link_encoder *enc110,
	bool disable)
{
	/* This register resides in DP back end block;
	 * transmitter is used for the offset */

	REG_UPDATE_4(DP_DPHY_CNTL,
			DPHY_ATEST_SEL_LANE0, disable,
			DPHY_ATEST_SEL_LANE1, disable,
			DPHY_ATEST_SEL_LANE2, disable,
			DPHY_ATEST_SEL_LANE3, disable);
}