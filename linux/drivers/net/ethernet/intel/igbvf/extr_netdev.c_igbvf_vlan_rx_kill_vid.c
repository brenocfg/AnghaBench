#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct TYPE_5__ {scalar_t__ (* set_vfta ) (struct e1000_hw*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct e1000_hw {int /*<<< orphan*/  mbx_lock; TYPE_3__ mac; } ;
struct igbvf_adapter {int /*<<< orphan*/  active_vlans; TYPE_1__* pdev; struct e1000_hw hw; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct igbvf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int igbvf_vlan_rx_kill_vid(struct net_device *netdev,
				  __be16 proto, u16 vid)
{
	struct igbvf_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;

	spin_lock_bh(&hw->mbx_lock);

	if (hw->mac.ops.set_vfta(hw, vid, false)) {
		dev_err(&adapter->pdev->dev,
			"Failed to remove vlan id %d\n", vid);
		spin_unlock_bh(&hw->mbx_lock);
		return -EINVAL;
	}

	spin_unlock_bh(&hw->mbx_lock);

	clear_bit(vid, adapter->active_vlans);
	return 0;
}