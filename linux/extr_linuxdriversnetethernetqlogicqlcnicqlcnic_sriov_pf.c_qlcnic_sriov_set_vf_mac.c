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
typedef  int /*<<< orphan*/  u8 ;
struct qlcnic_vf_info {int /*<<< orphan*/  state; TYPE_2__* vp; } ;
struct qlcnic_sriov {int num_vfs; struct qlcnic_vf_info* vf_info; } ;
struct qlcnic_adapter {int /*<<< orphan*/ * mac_addr; TYPE_1__* ahw; } ;
struct net_device {int /*<<< orphan*/  addr_len; } ;
struct TYPE_4__ {int /*<<< orphan*/ * mac; } ;
struct TYPE_3__ {struct qlcnic_sriov* sriov; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  QLC_BC_VF_STATE ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ *,int) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  qlcnic_sriov_pf_check (struct qlcnic_adapter*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qlcnic_sriov_set_vf_mac(struct net_device *netdev, int vf, u8 *mac)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	struct qlcnic_sriov *sriov = adapter->ahw->sriov;
	int i, num_vfs;
	struct qlcnic_vf_info *vf_info;
	u8 *curr_mac;

	if (!qlcnic_sriov_pf_check(adapter))
		return -EOPNOTSUPP;

	num_vfs = sriov->num_vfs;

	if (!is_valid_ether_addr(mac) || vf >= num_vfs)
		return -EINVAL;

	if (ether_addr_equal(adapter->mac_addr, mac)) {
		netdev_err(netdev, "MAC address is already in use by the PF\n");
		return -EINVAL;
	}

	for (i = 0; i < num_vfs; i++) {
		vf_info = &sriov->vf_info[i];
		if (ether_addr_equal(vf_info->vp->mac, mac)) {
			netdev_err(netdev,
				   "MAC address is already in use by VF %d\n",
				   i);
			return -EINVAL;
		}
	}

	vf_info = &sriov->vf_info[vf];
	curr_mac = vf_info->vp->mac;

	if (test_bit(QLC_BC_VF_STATE, &vf_info->state)) {
		netdev_err(netdev,
			   "MAC address change failed for VF %d, as VF driver is loaded. Please unload VF driver and retry the operation\n",
			   vf);
		return -EOPNOTSUPP;
	}

	memcpy(curr_mac, mac, netdev->addr_len);
	netdev_info(netdev, "MAC Address %pM  is configured for VF %d\n",
		    mac, vf);
	return 0;
}