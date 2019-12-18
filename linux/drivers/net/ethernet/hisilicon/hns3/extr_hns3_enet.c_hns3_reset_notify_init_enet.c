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
struct hns3_nic_priv {int /*<<< orphan*/  state; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct net_device* netdev; } ;
struct hnae3_handle {TYPE_1__ kinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS3_NIC_STATE_INITED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int hns3_client_start (struct hnae3_handle*) ; 
 int hns3_get_ring_config (struct hns3_nic_priv*) ; 
 int hns3_init_all_ring (struct hns3_nic_priv*) ; 
 int hns3_nic_alloc_vector_data (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_nic_dealloc_vector_data (struct hns3_nic_priv*) ; 
 int hns3_nic_init_vector_data (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_nic_uninit_vector_data (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_put_ring_config (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_restore_coal (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_uninit_all_ring (struct hns3_nic_priv*) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hns3_reset_notify_init_enet(struct hnae3_handle *handle)
{
	struct net_device *netdev = handle->kinfo.netdev;
	struct hns3_nic_priv *priv = netdev_priv(netdev);
	int ret;

	/* Carrier off reporting is important to ethtool even BEFORE open */
	netif_carrier_off(netdev);

	ret = hns3_get_ring_config(priv);
	if (ret)
		return ret;

	ret = hns3_nic_alloc_vector_data(priv);
	if (ret)
		goto err_put_ring;

	hns3_restore_coal(priv);

	ret = hns3_nic_init_vector_data(priv);
	if (ret)
		goto err_dealloc_vector;

	ret = hns3_init_all_ring(priv);
	if (ret)
		goto err_uninit_vector;

	ret = hns3_client_start(handle);
	if (ret) {
		dev_err(priv->dev, "hns3_client_start fail! ret=%d\n", ret);
		goto err_uninit_ring;
	}

	set_bit(HNS3_NIC_STATE_INITED, &priv->state);

	return ret;

err_uninit_ring:
	hns3_uninit_all_ring(priv);
err_uninit_vector:
	hns3_nic_uninit_vector_data(priv);
err_dealloc_vector:
	hns3_nic_dealloc_vector_data(priv);
err_put_ring:
	hns3_put_ring_config(priv);

	return ret;
}