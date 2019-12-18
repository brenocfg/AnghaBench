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
struct atl1e_hw {int dummy; } ;
struct atl1e_adapter {int /*<<< orphan*/  mdio_lock; struct atl1e_hw hw; } ;

/* Variables and functions */
 struct atl1e_adapter* adapter ; 
 int /*<<< orphan*/  atl1e_restart_autoneg (struct atl1e_hw*) ; 
 struct atl1e_adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_config_timer ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void atl1e_phy_config(struct timer_list *t)
{
	struct atl1e_adapter *adapter = from_timer(adapter, t,
						   phy_config_timer);
	struct atl1e_hw *hw = &adapter->hw;
	unsigned long flags;

	spin_lock_irqsave(&adapter->mdio_lock, flags);
	atl1e_restart_autoneg(hw);
	spin_unlock_irqrestore(&adapter->mdio_lock, flags);
}