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
struct net_device {scalar_t__ reg_state; } ;
struct hns3_nic_priv {int /*<<< orphan*/ * ring_data; } ;
struct TYPE_2__ {struct net_device* netdev; } ;
struct hnae3_handle {TYPE_1__ kinfo; } ;

/* Variables and functions */
 scalar_t__ NETREG_UNINITIALIZED ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  hns3_force_clear_all_rx_ring (struct hnae3_handle*) ; 
 int hns3_nic_dealloc_vector_data (struct hns3_nic_priv*) ; 
 int hns3_nic_uninit_vector_data (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_put_ring_config (struct hns3_nic_priv*) ; 
 int hns3_uninit_all_ring (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_uninit_mac_addr (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void hns3_client_uninit(struct hnae3_handle *handle, bool reset)
{
	struct net_device *netdev = handle->kinfo.netdev;
	struct hns3_nic_priv *priv = netdev_priv(netdev);
	int ret;

	if (netdev->reg_state != NETREG_UNINITIALIZED)
		unregister_netdev(netdev);

	hns3_force_clear_all_rx_ring(handle);

	ret = hns3_nic_uninit_vector_data(priv);
	if (ret)
		netdev_err(netdev, "uninit vector error\n");

	ret = hns3_nic_dealloc_vector_data(priv);
	if (ret)
		netdev_err(netdev, "dealloc vector error\n");

	ret = hns3_uninit_all_ring(priv);
	if (ret)
		netdev_err(netdev, "uninit ring error\n");

	hns3_put_ring_config(priv);

	priv->ring_data = NULL;

	hns3_uninit_mac_addr(netdev);

	free_netdev(netdev);
}