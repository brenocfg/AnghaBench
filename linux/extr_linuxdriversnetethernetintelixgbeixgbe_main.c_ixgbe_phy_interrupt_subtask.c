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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ (* handle_lasi ) (struct ixgbe_hw*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ phy; } ;
struct ixgbe_adapter {int flags2; struct ixgbe_hw hw; } ;

/* Variables and functions */
 scalar_t__ IXGBE_ERR_OVERTEMP ; 
 int IXGBE_FLAG2_PHY_INTERRUPT ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  e_crit (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_overheat_msg ; 
 scalar_t__ stub1 (struct ixgbe_hw*) ; 

__attribute__((used)) static void ixgbe_phy_interrupt_subtask(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u32 status;

	if (!(adapter->flags2 & IXGBE_FLAG2_PHY_INTERRUPT))
		return;

	adapter->flags2 &= ~IXGBE_FLAG2_PHY_INTERRUPT;

	if (!hw->phy.ops.handle_lasi)
		return;

	status = hw->phy.ops.handle_lasi(&adapter->hw);
	if (status != IXGBE_ERR_OVERTEMP)
		return;

	e_crit(drv, "%s\n", ixgbe_overheat_msg);
}