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
struct timer_list {int dummy; } ;
struct atl1_hw {int mii_autoneg_adv_reg; int mii_1000t_ctrl_reg; } ;
struct atl1_adapter {int phy_timer_pending; int /*<<< orphan*/  lock; struct atl1_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_ATLX_CR ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int MII_CR_AUTO_NEG_EN ; 
 int MII_CR_RESET ; 
 struct atl1_adapter* adapter ; 
 int /*<<< orphan*/  atl1_write_phy_reg (struct atl1_hw*,int /*<<< orphan*/ ,int) ; 
 struct atl1_adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_config_timer ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void atl1_phy_config(struct timer_list *t)
{
	struct atl1_adapter *adapter = from_timer(adapter, t,
						  phy_config_timer);
	struct atl1_hw *hw = &adapter->hw;
	unsigned long flags;

	spin_lock_irqsave(&adapter->lock, flags);
	adapter->phy_timer_pending = false;
	atl1_write_phy_reg(hw, MII_ADVERTISE, hw->mii_autoneg_adv_reg);
	atl1_write_phy_reg(hw, MII_ATLX_CR, hw->mii_1000t_ctrl_reg);
	atl1_write_phy_reg(hw, MII_BMCR, MII_CR_RESET | MII_CR_AUTO_NEG_EN);
	spin_unlock_irqrestore(&adapter->lock, flags);
}