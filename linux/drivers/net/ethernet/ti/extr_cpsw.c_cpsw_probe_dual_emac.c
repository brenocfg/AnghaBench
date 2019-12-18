#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct net_device {int features; TYPE_2__ dev; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  dev_addr; } ;
struct cpsw_priv {int emac_port; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  msg_enable; TYPE_2__* dev; struct net_device* ndev; struct cpsw_common* cpsw; } ;
struct cpsw_platform_data {TYPE_1__* slave_data; } ;
struct cpsw_common {int /*<<< orphan*/  dev; TYPE_4__* slaves; struct cpsw_platform_data data; } ;
struct TYPE_8__ {TYPE_3__* data; struct net_device* ndev; } ;
struct TYPE_7__ {int /*<<< orphan*/  slave_node; } ;
struct TYPE_5__ {int /*<<< orphan*/  mac_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPSW_DEBUG ; 
 int /*<<< orphan*/  CPSW_MAX_QUEUES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_ethtool_ops ; 
 int /*<<< orphan*/  cpsw_netdev_ops ; 
 int /*<<< orphan*/  debug_level ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct net_device* devm_alloc_etherdev_mqs (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_random_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cpsw_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int register_netdev (struct net_device*) ; 

__attribute__((used)) static int cpsw_probe_dual_emac(struct cpsw_priv *priv)
{
	struct cpsw_common		*cpsw = priv->cpsw;
	struct cpsw_platform_data	*data = &cpsw->data;
	struct net_device		*ndev;
	struct cpsw_priv		*priv_sl2;
	int ret = 0;

	ndev = devm_alloc_etherdev_mqs(cpsw->dev, sizeof(struct cpsw_priv),
				       CPSW_MAX_QUEUES, CPSW_MAX_QUEUES);
	if (!ndev) {
		dev_err(cpsw->dev, "cpsw: error allocating net_device\n");
		return -ENOMEM;
	}

	priv_sl2 = netdev_priv(ndev);
	priv_sl2->cpsw = cpsw;
	priv_sl2->ndev = ndev;
	priv_sl2->dev  = &ndev->dev;
	priv_sl2->msg_enable = netif_msg_init(debug_level, CPSW_DEBUG);

	if (is_valid_ether_addr(data->slave_data[1].mac_addr)) {
		memcpy(priv_sl2->mac_addr, data->slave_data[1].mac_addr,
			ETH_ALEN);
		dev_info(cpsw->dev, "cpsw: Detected MACID = %pM\n",
			 priv_sl2->mac_addr);
	} else {
		eth_random_addr(priv_sl2->mac_addr);
		dev_info(cpsw->dev, "cpsw: Random MACID = %pM\n",
			 priv_sl2->mac_addr);
	}
	memcpy(ndev->dev_addr, priv_sl2->mac_addr, ETH_ALEN);

	priv_sl2->emac_port = 1;
	cpsw->slaves[1].ndev = ndev;
	ndev->features |= NETIF_F_HW_VLAN_CTAG_FILTER | NETIF_F_HW_VLAN_CTAG_RX;

	ndev->netdev_ops = &cpsw_netdev_ops;
	ndev->ethtool_ops = &cpsw_ethtool_ops;

	/* register the network device */
	SET_NETDEV_DEV(ndev, cpsw->dev);
	ndev->dev.of_node = cpsw->slaves[1].data->slave_node;
	ret = register_netdev(ndev);
	if (ret)
		dev_err(cpsw->dev, "cpsw: error registering net device\n");

	return ret;
}