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
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  perm_addr; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* init_hw ) (struct e1000_hw*) ;scalar_t__ (* reset_hw ) (struct e1000_hw*) ;} ;
struct e1000_mac_info {int /*<<< orphan*/  addr; TYPE_2__ ops; } ;
struct e1000_hw {struct e1000_mac_info mac; int /*<<< orphan*/  mbx_lock; } ;
struct igbvf_adapter {int /*<<< orphan*/  last_reset; struct e1000_hw hw; TYPE_1__* pdev; struct net_device* netdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 

__attribute__((used)) static void igbvf_reset(struct igbvf_adapter *adapter)
{
	struct e1000_mac_info *mac = &adapter->hw.mac;
	struct net_device *netdev = adapter->netdev;
	struct e1000_hw *hw = &adapter->hw;

	spin_lock_bh(&hw->mbx_lock);

	/* Allow time for pending master requests to run */
	if (mac->ops.reset_hw(hw))
		dev_err(&adapter->pdev->dev, "PF still resetting\n");

	mac->ops.init_hw(hw);

	spin_unlock_bh(&hw->mbx_lock);

	if (is_valid_ether_addr(adapter->hw.mac.addr)) {
		memcpy(netdev->dev_addr, adapter->hw.mac.addr,
		       netdev->addr_len);
		memcpy(netdev->perm_addr, adapter->hw.mac.addr,
		       netdev->addr_len);
	}

	adapter->last_reset = jiffies;
}