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
struct qlcnic_adapter {int dummy; } ;
struct net_device {int mtu; } ;

/* Variables and functions */
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int qlcnic_fw_cmd_set_mtu (struct qlcnic_adapter*,int) ; 

int qlcnic_change_mtu(struct net_device *netdev, int mtu)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	int rc = 0;

	rc = qlcnic_fw_cmd_set_mtu(adapter, mtu);

	if (!rc)
		netdev->mtu = mtu;

	return rc;
}