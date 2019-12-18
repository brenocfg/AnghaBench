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
struct atl2_hw {int mii_autoneg_adv_reg; } ;
struct atl2_adapter {int /*<<< orphan*/  cfg_phy; int /*<<< orphan*/  stats_lock; struct atl2_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int MII_CR_AUTO_NEG_EN ; 
 int MII_CR_RESET ; 
 int MII_CR_RESTART_AUTO_NEG ; 
 struct atl2_adapter* adapter ; 
 int /*<<< orphan*/  atl2_write_phy_reg (struct atl2_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct atl2_adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_config_timer ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void atl2_phy_config(struct timer_list *t)
{
	struct atl2_adapter *adapter = from_timer(adapter, t,
						  phy_config_timer);
	struct atl2_hw *hw = &adapter->hw;
	unsigned long flags;

	spin_lock_irqsave(&adapter->stats_lock, flags);
	atl2_write_phy_reg(hw, MII_ADVERTISE, hw->mii_autoneg_adv_reg);
	atl2_write_phy_reg(hw, MII_BMCR, MII_CR_RESET | MII_CR_AUTO_NEG_EN |
		MII_CR_RESTART_AUTO_NEG);
	spin_unlock_irqrestore(&adapter->stats_lock, flags);
	clear_bit(0, &adapter->cfg_phy);
}