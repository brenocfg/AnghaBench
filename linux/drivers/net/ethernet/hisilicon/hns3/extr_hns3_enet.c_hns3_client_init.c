#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  max_mtu; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  watchdog_timeo; } ;
struct hns3_nic_priv {struct hnae3_handle* ae_handle; int /*<<< orphan*/ * ring_data; int /*<<< orphan*/  state; int /*<<< orphan*/ * dev; scalar_t__ tx_timeout_count; struct net_device* netdev; } ;
struct TYPE_6__ {struct net_device* netdev; } ;
struct hnae3_handle {void* priv; TYPE_3__ kinfo; int /*<<< orphan*/  msg_enable; TYPE_2__* ae_algo; struct pci_dev* pdev; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_tqps_and_rss_info ) (struct hnae3_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_MSG_LEVEL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HNS3_MAX_MTU ; 
 int /*<<< orphan*/  HNS3_NIC_STATE_DOWN ; 
 int /*<<< orphan*/  HNS3_NIC_STATE_INITED ; 
 int /*<<< orphan*/  HNS3_TX_TIMEOUT ; 
 int /*<<< orphan*/  IFF_UNICAST_FLT ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_etherdev_mq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int hns3_client_start (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hns3_dbg_init (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hns3_dcbnl_setup (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hns3_ethtool_set_ops (struct net_device*) ; 
 int hns3_get_ring_config (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_info_show (struct hns3_nic_priv*) ; 
 int hns3_init_all_ring (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_init_mac_addr (struct net_device*,int) ; 
 int hns3_init_phy (struct net_device*) ; 
 int hns3_nic_alloc_vector_data (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_nic_dealloc_vector_data (struct hns3_nic_priv*) ; 
 int hns3_nic_init_vector_data (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_nic_netdev_ops ; 
 int /*<<< orphan*/  hns3_nic_uninit_vector_data (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_set_default_feature (struct net_device*) ; 
 int /*<<< orphan*/  hns3_uninit_all_ring (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_uninit_phy (struct net_device*) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_msg_drv (struct hnae3_handle*) ; 
 int /*<<< orphan*/  netif_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct hnae3_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int hns3_client_init(struct hnae3_handle *handle)
{
	struct pci_dev *pdev = handle->pdev;
	u16 alloc_tqps, max_rss_size;
	struct hns3_nic_priv *priv;
	struct net_device *netdev;
	int ret;

	handle->ae_algo->ops->get_tqps_and_rss_info(handle, &alloc_tqps,
						    &max_rss_size);
	netdev = alloc_etherdev_mq(sizeof(struct hns3_nic_priv), alloc_tqps);
	if (!netdev)
		return -ENOMEM;

	priv = netdev_priv(netdev);
	priv->dev = &pdev->dev;
	priv->netdev = netdev;
	priv->ae_handle = handle;
	priv->tx_timeout_count = 0;
	set_bit(HNS3_NIC_STATE_DOWN, &priv->state);

	handle->msg_enable = netif_msg_init(debug, DEFAULT_MSG_LEVEL);

	handle->kinfo.netdev = netdev;
	handle->priv = (void *)priv;

	hns3_init_mac_addr(netdev, true);

	hns3_set_default_feature(netdev);

	netdev->watchdog_timeo = HNS3_TX_TIMEOUT;
	netdev->priv_flags |= IFF_UNICAST_FLT;
	netdev->netdev_ops = &hns3_nic_netdev_ops;
	SET_NETDEV_DEV(netdev, &pdev->dev);
	hns3_ethtool_set_ops(netdev);

	/* Carrier off reporting is important to ethtool even BEFORE open */
	netif_carrier_off(netdev);

	ret = hns3_get_ring_config(priv);
	if (ret) {
		ret = -ENOMEM;
		goto out_get_ring_cfg;
	}

	ret = hns3_nic_alloc_vector_data(priv);
	if (ret) {
		ret = -ENOMEM;
		goto out_alloc_vector_data;
	}

	ret = hns3_nic_init_vector_data(priv);
	if (ret) {
		ret = -ENOMEM;
		goto out_init_vector_data;
	}

	ret = hns3_init_all_ring(priv);
	if (ret) {
		ret = -ENOMEM;
		goto out_init_ring_data;
	}

	ret = hns3_init_phy(netdev);
	if (ret)
		goto out_init_phy;

	ret = register_netdev(netdev);
	if (ret) {
		dev_err(priv->dev, "probe register netdev fail!\n");
		goto out_reg_netdev_fail;
	}

	ret = hns3_client_start(handle);
	if (ret) {
		dev_err(priv->dev, "hns3_client_start fail! ret=%d\n", ret);
		goto out_client_start;
	}

	hns3_dcbnl_setup(handle);

	hns3_dbg_init(handle);

	/* MTU range: (ETH_MIN_MTU(kernel default) - 9702) */
	netdev->max_mtu = HNS3_MAX_MTU;

	set_bit(HNS3_NIC_STATE_INITED, &priv->state);

	if (netif_msg_drv(handle))
		hns3_info_show(priv);

	return ret;

out_client_start:
	unregister_netdev(netdev);
out_reg_netdev_fail:
	hns3_uninit_phy(netdev);
out_init_phy:
	hns3_uninit_all_ring(priv);
out_init_ring_data:
	hns3_nic_uninit_vector_data(priv);
out_init_vector_data:
	hns3_nic_dealloc_vector_data(priv);
out_alloc_vector_data:
	priv->ring_data = NULL;
out_get_ring_cfg:
	priv->ae_handle = NULL;
	free_netdev(netdev);
	return ret;
}