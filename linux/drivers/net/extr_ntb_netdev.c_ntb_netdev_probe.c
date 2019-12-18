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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ntb_netdev {int /*<<< orphan*/  qp; struct pci_dev* pdev; struct net_device* ndev; } ;
struct ntb_dev {struct pci_dev* pdev; } ;
struct net_device {int /*<<< orphan*/  name; scalar_t__ mtu; int /*<<< orphan*/  max_mtu; scalar_t__ min_mtu; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  perm_addr; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/  features; int /*<<< orphan*/  hw_features; int /*<<< orphan*/  priv_flags; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  ETH_MAX_MTU ; 
 int /*<<< orphan*/  IFF_LIVE_ADDR_CHANGE ; 
 int /*<<< orphan*/  NETIF_F_HIGHDMA ; 
 int /*<<< orphan*/  NTB_TX_TIMEOUT_MS ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,struct device*) ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct ntb_dev* dev_ntb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct net_device*) ; 
 int /*<<< orphan*/  eth_random_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 struct ntb_netdev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ntb_ethtool_ops ; 
 int /*<<< orphan*/  ntb_netdev_handlers ; 
 int /*<<< orphan*/  ntb_netdev_ops ; 
 int /*<<< orphan*/  ntb_transport_create_queue (struct net_device*,struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntb_transport_free_queue (int /*<<< orphan*/ ) ; 
 scalar_t__ ntb_transport_max_size (int /*<<< orphan*/ ) ; 
 int register_netdev (struct net_device*) ; 

__attribute__((used)) static int ntb_netdev_probe(struct device *client_dev)
{
	struct ntb_dev *ntb;
	struct net_device *ndev;
	struct pci_dev *pdev;
	struct ntb_netdev *dev;
	int rc;

	ntb = dev_ntb(client_dev->parent);
	pdev = ntb->pdev;
	if (!pdev)
		return -ENODEV;

	ndev = alloc_etherdev(sizeof(*dev));
	if (!ndev)
		return -ENOMEM;

	SET_NETDEV_DEV(ndev, client_dev);

	dev = netdev_priv(ndev);
	dev->ndev = ndev;
	dev->pdev = pdev;
	ndev->features = NETIF_F_HIGHDMA;

	ndev->priv_flags |= IFF_LIVE_ADDR_CHANGE;

	ndev->hw_features = ndev->features;
	ndev->watchdog_timeo = msecs_to_jiffies(NTB_TX_TIMEOUT_MS);

	eth_random_addr(ndev->perm_addr);
	memcpy(ndev->dev_addr, ndev->perm_addr, ndev->addr_len);

	ndev->netdev_ops = &ntb_netdev_ops;
	ndev->ethtool_ops = &ntb_ethtool_ops;

	ndev->min_mtu = 0;
	ndev->max_mtu = ETH_MAX_MTU;

	dev->qp = ntb_transport_create_queue(ndev, client_dev,
					     &ntb_netdev_handlers);
	if (!dev->qp) {
		rc = -EIO;
		goto err;
	}

	ndev->mtu = ntb_transport_max_size(dev->qp) - ETH_HLEN;

	rc = register_netdev(ndev);
	if (rc)
		goto err1;

	dev_set_drvdata(client_dev, ndev);
	dev_info(&pdev->dev, "%s created\n", ndev->name);
	return 0;

err1:
	ntb_transport_free_queue(dev->qp);
err:
	free_netdev(ndev);
	return rc;
}