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
struct net_device {int mtu; } ;
struct hinic_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drv ; 
 int hinic_port_set_mtu (struct hinic_dev*,int) ; 
 struct hinic_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct hinic_dev*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_info (struct hinic_dev*,int /*<<< orphan*/ ,struct net_device*,char*,int) ; 

__attribute__((used)) static int hinic_change_mtu(struct net_device *netdev, int new_mtu)
{
	struct hinic_dev *nic_dev = netdev_priv(netdev);
	int err;

	netif_info(nic_dev, drv, netdev, "set_mtu = %d\n", new_mtu);

	err = hinic_port_set_mtu(nic_dev, new_mtu);
	if (err)
		netif_err(nic_dev, drv, netdev, "Failed to set port mtu\n");
	else
		netdev->mtu = new_mtu;

	return err;
}