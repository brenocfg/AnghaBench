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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {scalar_t__ max_mtu; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  watchdog_timeo; } ;
struct hns3_nic_priv {struct hnae3_handle* ae_handle; int /*<<< orphan*/ * ring_data; int /*<<< orphan*/ * dev; scalar_t__ tx_timeout_count; struct net_device* netdev; } ;
struct TYPE_2__ {struct net_device* netdev; } ;
struct hnae3_handle {int flags; int /*<<< orphan*/  reset_level; void* priv; TYPE_1__ kinfo; int /*<<< orphan*/  last_reset_time; struct pci_dev* pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ ETH_FCS_LEN ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  HNAE3_FUNC_RESET ; 
 int HNAE3_SUPPORT_VF ; 
 int /*<<< orphan*/  HNAE3_VF_RESET ; 
 scalar_t__ HNS3_MAX_MTU ; 
 int /*<<< orphan*/  HNS3_TX_TIMEOUT ; 
 int /*<<< orphan*/  IFF_UNICAST_FLT ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ VLAN_HLEN ; 
 struct net_device* alloc_etherdev_mq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  hns3_dcbnl_setup (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hns3_ethtool_set_ops (struct net_device*) ; 
 int /*<<< orphan*/  hns3_get_max_available_channels (struct hnae3_handle*) ; 
 int hns3_get_ring_config (struct hns3_nic_priv*) ; 
 int hns3_init_all_ring (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_init_mac_addr (struct net_device*,int) ; 
 int hns3_nic_alloc_vector_data (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_nic_dealloc_vector_data (struct hns3_nic_priv*) ; 
 int hns3_nic_init_vector_data (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_nic_netdev_ops ; 
 int /*<<< orphan*/  hns3_nic_set_priv_ops (struct net_device*) ; 
 int /*<<< orphan*/  hns3_nic_uninit_vector_data (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_set_default_feature (struct net_device*) ; 
 int /*<<< orphan*/  jiffies ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int register_netdev (struct net_device*) ; 

__attribute__((used)) static int hns3_client_init(struct hnae3_handle *handle)
{
	struct pci_dev *pdev = handle->pdev;
	struct hns3_nic_priv *priv;
	struct net_device *netdev;
	int ret;

	netdev = alloc_etherdev_mq(sizeof(struct hns3_nic_priv),
				   hns3_get_max_available_channels(handle));
	if (!netdev)
		return -ENOMEM;

	priv = netdev_priv(netdev);
	priv->dev = &pdev->dev;
	priv->netdev = netdev;
	priv->ae_handle = handle;
	priv->ae_handle->last_reset_time = jiffies;
	priv->tx_timeout_count = 0;

	handle->kinfo.netdev = netdev;
	handle->priv = (void *)priv;

	hns3_init_mac_addr(netdev, true);

	hns3_set_default_feature(netdev);

	netdev->watchdog_timeo = HNS3_TX_TIMEOUT;
	netdev->priv_flags |= IFF_UNICAST_FLT;
	netdev->netdev_ops = &hns3_nic_netdev_ops;
	SET_NETDEV_DEV(netdev, &pdev->dev);
	hns3_ethtool_set_ops(netdev);
	hns3_nic_set_priv_ops(netdev);

	/* Carrier off reporting is important to ethtool even BEFORE open */
	netif_carrier_off(netdev);

	if (handle->flags & HNAE3_SUPPORT_VF)
		handle->reset_level = HNAE3_VF_RESET;
	else
		handle->reset_level = HNAE3_FUNC_RESET;

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

	ret = register_netdev(netdev);
	if (ret) {
		dev_err(priv->dev, "probe register netdev fail!\n");
		goto out_reg_netdev_fail;
	}

	hns3_dcbnl_setup(handle);

	/* MTU range: (ETH_MIN_MTU(kernel default) - 9706) */
	netdev->max_mtu = HNS3_MAX_MTU - (ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN);

	return ret;

out_reg_netdev_fail:
out_init_ring_data:
	(void)hns3_nic_uninit_vector_data(priv);
out_init_vector_data:
	hns3_nic_dealloc_vector_data(priv);
out_alloc_vector_data:
	priv->ring_data = NULL;
out_get_ring_cfg:
	priv->ae_handle = NULL;
	free_netdev(netdev);
	return ret;
}