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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int features; int hw_features; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  max_mtu; } ;
struct lan743x_adapter {int msg_enable; struct net_device* netdev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  LAN743X_MAX_FRAME_SIZE ; 
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int NETIF_MSG_DRV ; 
 int NETIF_MSG_IFDOWN ; 
 int NETIF_MSG_IFUP ; 
 int NETIF_MSG_LINK ; 
 int NETIF_MSG_PROBE ; 
 int NETIF_MSG_TX_QUEUED ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* devm_alloc_etherdev (int /*<<< orphan*/ *,int) ; 
 int lan743x_csr_init (struct lan743x_adapter*) ; 
 int /*<<< orphan*/  lan743x_ethtool_ops ; 
 int /*<<< orphan*/  lan743x_hardware_cleanup (struct lan743x_adapter*) ; 
 int lan743x_hardware_init (struct lan743x_adapter*,struct pci_dev*) ; 
 int /*<<< orphan*/  lan743x_mdiobus_cleanup (struct lan743x_adapter*) ; 
 int lan743x_mdiobus_init (struct lan743x_adapter*) ; 
 int /*<<< orphan*/  lan743x_netdev_ops ; 
 int /*<<< orphan*/  lan743x_pci_cleanup (struct lan743x_adapter*) ; 
 int lan743x_pci_init (struct lan743x_adapter*,struct pci_dev*) ; 
 struct lan743x_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct net_device*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int register_netdev (struct net_device*) ; 

__attribute__((used)) static int lan743x_pcidev_probe(struct pci_dev *pdev,
				const struct pci_device_id *id)
{
	struct lan743x_adapter *adapter = NULL;
	struct net_device *netdev = NULL;
	int ret = -ENODEV;

	netdev = devm_alloc_etherdev(&pdev->dev,
				     sizeof(struct lan743x_adapter));
	if (!netdev)
		goto return_error;

	SET_NETDEV_DEV(netdev, &pdev->dev);
	pci_set_drvdata(pdev, netdev);
	adapter = netdev_priv(netdev);
	adapter->netdev = netdev;
	adapter->msg_enable = NETIF_MSG_DRV | NETIF_MSG_PROBE |
			      NETIF_MSG_LINK | NETIF_MSG_IFUP |
			      NETIF_MSG_IFDOWN | NETIF_MSG_TX_QUEUED;
	netdev->max_mtu = LAN743X_MAX_FRAME_SIZE;

	ret = lan743x_pci_init(adapter, pdev);
	if (ret)
		goto return_error;

	ret = lan743x_csr_init(adapter);
	if (ret)
		goto cleanup_pci;

	ret = lan743x_hardware_init(adapter, pdev);
	if (ret)
		goto cleanup_pci;

	ret = lan743x_mdiobus_init(adapter);
	if (ret)
		goto cleanup_hardware;

	adapter->netdev->netdev_ops = &lan743x_netdev_ops;
	adapter->netdev->ethtool_ops = &lan743x_ethtool_ops;
	adapter->netdev->features = NETIF_F_SG | NETIF_F_TSO | NETIF_F_HW_CSUM;
	adapter->netdev->hw_features = adapter->netdev->features;

	/* carrier off reporting is important to ethtool even BEFORE open */
	netif_carrier_off(netdev);

	ret = register_netdev(adapter->netdev);
	if (ret < 0)
		goto cleanup_mdiobus;
	return 0;

cleanup_mdiobus:
	lan743x_mdiobus_cleanup(adapter);

cleanup_hardware:
	lan743x_hardware_cleanup(adapter);

cleanup_pci:
	lan743x_pci_cleanup(adapter);

return_error:
	pr_warn("Initialization failed\n");
	return ret;
}