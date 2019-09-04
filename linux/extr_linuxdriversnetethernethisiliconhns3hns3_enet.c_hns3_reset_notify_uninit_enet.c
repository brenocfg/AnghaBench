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
struct hns3_nic_priv {int dummy; } ;
struct TYPE_2__ {struct net_device* netdev; } ;
struct hnae3_handle {TYPE_1__ kinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns3_force_clear_all_rx_ring (struct hnae3_handle*) ; 
 int hns3_nic_uninit_vector_data (struct hns3_nic_priv*) ; 
 int hns3_uninit_all_ring (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_uninit_mac_addr (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int hns3_reset_notify_uninit_enet(struct hnae3_handle *handle)
{
	struct net_device *netdev = handle->kinfo.netdev;
	struct hns3_nic_priv *priv = netdev_priv(netdev);
	int ret;

	hns3_force_clear_all_rx_ring(handle);

	ret = hns3_nic_uninit_vector_data(priv);
	if (ret) {
		netdev_err(netdev, "uninit vector error\n");
		return ret;
	}

	ret = hns3_uninit_all_ring(priv);
	if (ret)
		netdev_err(netdev, "uninit ring error\n");

	hns3_uninit_mac_addr(netdev);

	return ret;
}