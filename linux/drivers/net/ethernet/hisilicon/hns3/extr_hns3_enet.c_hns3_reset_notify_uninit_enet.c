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
struct hns3_nic_priv {int /*<<< orphan*/  ae_handle; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {struct net_device* netdev; } ;
struct hnae3_handle {TYPE_1__ kinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS3_NIC_STATE_INITED ; 
 int /*<<< orphan*/  hns3_clear_all_ring (struct hnae3_handle*,int) ; 
 int hns3_nic_dealloc_vector_data (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_nic_uninit_vector_data (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_put_ring_config (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_reset_tx_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns3_store_coal (struct hns3_nic_priv*) ; 
 int hns3_uninit_all_ring (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hns3_reset_notify_uninit_enet(struct hnae3_handle *handle)
{
	struct net_device *netdev = handle->kinfo.netdev;
	struct hns3_nic_priv *priv = netdev_priv(netdev);
	int ret;

	if (!test_and_clear_bit(HNS3_NIC_STATE_INITED, &priv->state)) {
		netdev_warn(netdev, "already uninitialized\n");
		return 0;
	}

	hns3_clear_all_ring(handle, true);
	hns3_reset_tx_queue(priv->ae_handle);

	hns3_nic_uninit_vector_data(priv);

	hns3_store_coal(priv);

	ret = hns3_nic_dealloc_vector_data(priv);
	if (ret)
		netdev_err(netdev, "dealloc vector error\n");

	ret = hns3_uninit_all_ring(priv);
	if (ret)
		netdev_err(netdev, "uninit ring error\n");

	hns3_put_ring_config(priv);

	return ret;
}