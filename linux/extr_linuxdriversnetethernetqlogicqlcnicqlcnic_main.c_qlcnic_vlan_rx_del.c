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
typedef  int /*<<< orphan*/  u16 ;
struct qlcnic_adapter {int /*<<< orphan*/  vlans; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_DOWN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ,int) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  qlcnic_restore_indev_addr (struct net_device*,int /*<<< orphan*/ ) ; 
 int qlcnic_sriov_cfg_vf_guest_vlan (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qlcnic_sriov_vf_check (struct qlcnic_adapter*) ; 

__attribute__((used)) static int
qlcnic_vlan_rx_del(struct net_device *netdev, __be16 proto, u16 vid)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	int err;

	if (qlcnic_sriov_vf_check(adapter)) {
		err = qlcnic_sriov_cfg_vf_guest_vlan(adapter, vid, 0);
		if (err) {
			netdev_err(netdev,
				   "Cannot delete VLAN filter for VLAN id %d, err=%d",
				   vid, err);
			return err;
		}
	}

	qlcnic_restore_indev_addr(netdev, NETDEV_DOWN);
	clear_bit(vid, adapter->vlans);
	return 0;
}