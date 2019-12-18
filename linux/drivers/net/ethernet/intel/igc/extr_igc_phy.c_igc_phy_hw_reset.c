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
struct TYPE_2__ {int /*<<< orphan*/  (* release ) (struct igc_hw*) ;scalar_t__ (* acquire ) (struct igc_hw*) ;} ;
struct igc_phy_info {TYPE_1__ ops; int /*<<< orphan*/  reset_delay_us; } ;
struct igc_hw {struct igc_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_CTRL ; 
 int IGC_CTRL_PHY_RST ; 
 scalar_t__ igc_check_reset_block (struct igc_hw*) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct igc_hw*) ; 
 int /*<<< orphan*/  stub2 (struct igc_hw*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrfl () ; 

s32 igc_phy_hw_reset(struct igc_hw *hw)
{
	struct igc_phy_info *phy = &hw->phy;
	s32  ret_val;
	u32 ctrl;

	ret_val = igc_check_reset_block(hw);
	if (ret_val) {
		ret_val = 0;
		goto out;
	}

	ret_val = phy->ops.acquire(hw);
	if (ret_val)
		goto out;

	ctrl = rd32(IGC_CTRL);
	wr32(IGC_CTRL, ctrl | IGC_CTRL_PHY_RST);
	wrfl();

	udelay(phy->reset_delay_us);

	wr32(IGC_CTRL, ctrl);
	wrfl();

	usleep_range(1500, 2000);

	phy->ops.release(hw);

out:
	return ret_val;
}