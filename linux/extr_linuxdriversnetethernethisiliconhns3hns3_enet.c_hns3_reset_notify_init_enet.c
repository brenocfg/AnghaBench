#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct hns3_nic_priv {int /*<<< orphan*/ * ring_data; } ;
struct TYPE_2__ {struct net_device* netdev; } ;
struct hnae3_handle {int flags; TYPE_1__ kinfo; } ;

/* Variables and functions */
 int HNAE3_SUPPORT_VF ; 
 int hns3_init_all_ring (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_init_mac_addr (struct net_device*,int) ; 
 int hns3_nic_init_vector_data (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_nic_set_rx_mode (struct net_device*) ; 
 int /*<<< orphan*/  hns3_nic_uninit_vector_data (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_recover_hw_addr (struct net_device*) ; 
 int /*<<< orphan*/  hns3_restore_vlan (struct net_device*) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 

__attribute__((used)) static int hns3_reset_notify_init_enet(struct hnae3_handle *handle)
{
	struct net_device *netdev = handle->kinfo.netdev;
	struct hns3_nic_priv *priv = netdev_priv(netdev);
	int ret;

	hns3_init_mac_addr(netdev, false);
	hns3_nic_set_rx_mode(netdev);
	hns3_recover_hw_addr(netdev);

	/* Hardware table is only clear when pf resets */
	if (!(handle->flags & HNAE3_SUPPORT_VF))
		hns3_restore_vlan(netdev);

	/* Carrier off reporting is important to ethtool even BEFORE open */
	netif_carrier_off(netdev);

	ret = hns3_nic_init_vector_data(priv);
	if (ret)
		return ret;

	ret = hns3_init_all_ring(priv);
	if (ret) {
		hns3_nic_uninit_vector_data(priv);
		priv->ring_data = NULL;
	}

	return ret;
}