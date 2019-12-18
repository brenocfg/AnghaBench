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
struct net_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_ethertype_anti_spoofing ) (struct ixgbe_hw*,int,int) ;int /*<<< orphan*/  (* set_vlan_anti_spoofing ) (struct ixgbe_hw*,int,int) ;int /*<<< orphan*/  (* set_mac_anti_spoofing ) (struct ixgbe_hw*,int,int) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct ixgbe_hw {TYPE_3__ mac; } ;
struct ixgbe_adapter {int num_vfs; TYPE_1__* vfinfo; struct ixgbe_hw hw; } ;
struct TYPE_4__ {int spoofchk_enabled; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_P_LLDP ; 
 int ETH_P_PAUSE ; 
 int /*<<< orphan*/  IXGBE_ETQF (int /*<<< orphan*/ ) ; 
 int IXGBE_ETQF_FILTER_EN ; 
 int /*<<< orphan*/  IXGBE_ETQF_FILTER_FC ; 
 int /*<<< orphan*/  IXGBE_ETQF_FILTER_LLDP ; 
 int IXGBE_ETQF_TX_ANTISPOOF ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*,int,int) ; 

int ixgbe_ndo_set_vf_spoofchk(struct net_device *netdev, int vf, bool setting)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	struct ixgbe_hw *hw = &adapter->hw;

	if (vf >= adapter->num_vfs)
		return -EINVAL;

	adapter->vfinfo[vf].spoofchk_enabled = setting;

	/* configure MAC spoofing */
	hw->mac.ops.set_mac_anti_spoofing(hw, setting, vf);

	/* configure VLAN spoofing */
	hw->mac.ops.set_vlan_anti_spoofing(hw, setting, vf);

	/* Ensure LLDP and FC is set for Ethertype Antispoofing if we will be
	 * calling set_ethertype_anti_spoofing for each VF in loop below
	 */
	if (hw->mac.ops.set_ethertype_anti_spoofing) {
		IXGBE_WRITE_REG(hw, IXGBE_ETQF(IXGBE_ETQF_FILTER_LLDP),
				(IXGBE_ETQF_FILTER_EN    |
				 IXGBE_ETQF_TX_ANTISPOOF |
				 ETH_P_LLDP));

		IXGBE_WRITE_REG(hw, IXGBE_ETQF(IXGBE_ETQF_FILTER_FC),
				(IXGBE_ETQF_FILTER_EN |
				 IXGBE_ETQF_TX_ANTISPOOF |
				 ETH_P_PAUSE));

		hw->mac.ops.set_ethertype_anti_spoofing(hw, setting, vf);
	}

	return 0;
}