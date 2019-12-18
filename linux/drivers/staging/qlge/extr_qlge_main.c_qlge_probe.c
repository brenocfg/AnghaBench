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
struct ql_adapter {int /*<<< orphan*/  lb_count; int /*<<< orphan*/  timer; int /*<<< orphan*/  tx_ring_size; int /*<<< orphan*/  flags; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct net_device {int hw_features; int features; int vlan_features; int watchdog_timeo; int max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  irq; int /*<<< orphan*/  tx_queue_len; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_DATA_LEN ; 
 int HZ ; 
 int /*<<< orphan*/  MAX_CPUS ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO_ECN ; 
 int /*<<< orphan*/  QL_DMA64 ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIMER_DEFERRABLE ; 
 struct net_device* alloc_etherdev_mq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct ql_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_get_num_default_rss_queues () ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  ql_display_dev_info (struct net_device*) ; 
 int ql_init_device (struct pci_dev*,struct net_device*,int) ; 
 int /*<<< orphan*/  ql_link_off (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_release_all (struct pci_dev*) ; 
 int /*<<< orphan*/  ql_timer ; 
 int /*<<< orphan*/  qlge_ethtool_ops ; 
 int /*<<< orphan*/  qlge_netdev_ops ; 
 int register_netdev (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qlge_probe(struct pci_dev *pdev,
		      const struct pci_device_id *pci_entry)
{
	struct net_device *ndev = NULL;
	struct ql_adapter *qdev = NULL;
	static int cards_found = 0;
	int err = 0;

	ndev = alloc_etherdev_mq(sizeof(struct ql_adapter),
			min(MAX_CPUS, netif_get_num_default_rss_queues()));
	if (!ndev)
		return -ENOMEM;

	err = ql_init_device(pdev, ndev, cards_found);
	if (err < 0) {
		free_netdev(ndev);
		return err;
	}

	qdev = netdev_priv(ndev);
	SET_NETDEV_DEV(ndev, &pdev->dev);
	ndev->hw_features = NETIF_F_SG |
			    NETIF_F_IP_CSUM |
			    NETIF_F_TSO |
			    NETIF_F_TSO_ECN |
			    NETIF_F_HW_VLAN_CTAG_TX |
			    NETIF_F_HW_VLAN_CTAG_RX |
			    NETIF_F_HW_VLAN_CTAG_FILTER |
			    NETIF_F_RXCSUM;
	ndev->features = ndev->hw_features;
	ndev->vlan_features = ndev->hw_features;
	/* vlan gets same features (except vlan filter) */
	ndev->vlan_features &= ~(NETIF_F_HW_VLAN_CTAG_FILTER |
				 NETIF_F_HW_VLAN_CTAG_TX |
				 NETIF_F_HW_VLAN_CTAG_RX);

	if (test_bit(QL_DMA64, &qdev->flags))
		ndev->features |= NETIF_F_HIGHDMA;

	/*
	 * Set up net_device structure.
	 */
	ndev->tx_queue_len = qdev->tx_ring_size;
	ndev->irq = pdev->irq;

	ndev->netdev_ops = &qlge_netdev_ops;
	ndev->ethtool_ops = &qlge_ethtool_ops;
	ndev->watchdog_timeo = 10 * HZ;

	/* MTU range: this driver only supports 1500 or 9000, so this only
	 * filters out values above or below, and we'll rely on
	 * qlge_change_mtu to make sure only 1500 or 9000 are allowed
	 */
	ndev->min_mtu = ETH_DATA_LEN;
	ndev->max_mtu = 9000;

	err = register_netdev(ndev);
	if (err) {
		dev_err(&pdev->dev, "net device registration failed.\n");
		ql_release_all(pdev);
		pci_disable_device(pdev);
		free_netdev(ndev);
		return err;
	}
	/* Start up the timer to trigger EEH if
	 * the bus goes dead
	 */
	timer_setup(&qdev->timer, ql_timer, TIMER_DEFERRABLE);
	mod_timer(&qdev->timer, jiffies + (5*HZ));
	ql_link_off(qdev);
	ql_display_dev_info(ndev);
	atomic_set(&qdev->lb_count, 0);
	cards_found++;
	return 0;
}