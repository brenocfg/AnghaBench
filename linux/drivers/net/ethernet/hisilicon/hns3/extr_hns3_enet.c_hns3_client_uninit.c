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
struct hns3_nic_priv {int /*<<< orphan*/  state; } ;
struct TYPE_2__ {struct net_device* netdev; } ;
struct hnae3_handle {TYPE_1__ kinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS3_NIC_STATE_INITED ; 
 scalar_t__ NETREG_UNINITIALIZED ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  hns3_clear_all_ring (struct hnae3_handle*,int) ; 
 int /*<<< orphan*/  hns3_client_stop (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hns3_dbg_uninit (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hns3_del_all_fd_rules (struct net_device*,int) ; 
 int hns3_nic_dealloc_vector_data (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_nic_uninit_vector_data (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_put_ring_config (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_remove_hw_addr (struct net_device*) ; 
 int hns3_uninit_all_ring (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_uninit_phy (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void hns3_client_uninit(struct hnae3_handle *handle, bool reset)
{
	struct net_device *netdev = handle->kinfo.netdev;
	struct hns3_nic_priv *priv = netdev_priv(netdev);
	int ret;

	hns3_remove_hw_addr(netdev);

	if (netdev->reg_state != NETREG_UNINITIALIZED)
		unregister_netdev(netdev);

	hns3_client_stop(handle);

	hns3_uninit_phy(netdev);

	if (!test_and_clear_bit(HNS3_NIC_STATE_INITED, &priv->state)) {
		netdev_warn(netdev, "already uninitialized\n");
		goto out_netdev_free;
	}

	hns3_del_all_fd_rules(netdev, true);

	hns3_clear_all_ring(handle, true);

	hns3_nic_uninit_vector_data(priv);

	ret = hns3_nic_dealloc_vector_data(priv);
	if (ret)
		netdev_err(netdev, "dealloc vector error\n");

	ret = hns3_uninit_all_ring(priv);
	if (ret)
		netdev_err(netdev, "uninit ring error\n");

	hns3_put_ring_config(priv);

	hns3_dbg_uninit(handle);

out_netdev_free:
	free_netdev(netdev);
}