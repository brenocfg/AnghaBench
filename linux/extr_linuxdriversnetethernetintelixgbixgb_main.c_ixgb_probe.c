#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int watchdog_timeo; int hw_features; int features; int vlan_features; int /*<<< orphan*/  name; int /*<<< orphan*/  dev_addr; scalar_t__ max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  hw_addr; int /*<<< orphan*/  io_base; struct ixgb_adapter* back; } ;
struct ixgb_adapter {int bd_number; TYPE_1__ hw; struct net_device* netdev; int /*<<< orphan*/  tx_timeout_task; int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  part_num; scalar_t__ link_duplex; scalar_t__ link_speed; int /*<<< orphan*/  napi; int /*<<< orphan*/  msg_enable; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAR_0 ; 
 int BAR_1 ; 
 int BAR_5 ; 
 int /*<<< orphan*/  DEFAULT_MSG_ENABLE ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  ETH_MIN_MTU ; 
 int HZ ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IORESOURCE_IO ; 
 scalar_t__ IXGB_MAX_JUMBO_FRAME_SIZE ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  debug ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgb_check_options (struct ixgb_adapter*) ; 
 int /*<<< orphan*/  ixgb_clean ; 
 int /*<<< orphan*/  ixgb_driver_name ; 
 int /*<<< orphan*/  ixgb_get_ee_mac_addr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgb_get_ee_pba_number (TYPE_1__*) ; 
 int /*<<< orphan*/  ixgb_netdev_ops ; 
 int /*<<< orphan*/  ixgb_reset (struct ixgb_adapter*) ; 
 int /*<<< orphan*/  ixgb_set_ethtool_ops (struct net_device*) ; 
 int ixgb_sw_init (struct ixgb_adapter*) ; 
 int /*<<< orphan*/  ixgb_tx_timeout_task ; 
 int /*<<< orphan*/  ixgb_validate_eeprom_checksum (TYPE_1__*) ; 
 int /*<<< orphan*/  ixgb_watchdog ; 
 struct ixgb_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct ixgb_adapter*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_info (struct ixgb_adapter*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_ioremap_bar (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_resource_flags (struct pci_dev*,int) ; 
 scalar_t__ pci_resource_len (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct net_device*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  probe ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ixgb_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	struct net_device *netdev = NULL;
	struct ixgb_adapter *adapter;
	static int cards_found = 0;
	int pci_using_dac;
	int i;
	int err;

	err = pci_enable_device(pdev);
	if (err)
		return err;

	pci_using_dac = 0;
	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	if (!err) {
		pci_using_dac = 1;
	} else {
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		if (err) {
			pr_err("No usable DMA configuration, aborting\n");
			goto err_dma_mask;
		}
	}

	err = pci_request_regions(pdev, ixgb_driver_name);
	if (err)
		goto err_request_regions;

	pci_set_master(pdev);

	netdev = alloc_etherdev(sizeof(struct ixgb_adapter));
	if (!netdev) {
		err = -ENOMEM;
		goto err_alloc_etherdev;
	}

	SET_NETDEV_DEV(netdev, &pdev->dev);

	pci_set_drvdata(pdev, netdev);
	adapter = netdev_priv(netdev);
	adapter->netdev = netdev;
	adapter->pdev = pdev;
	adapter->hw.back = adapter;
	adapter->msg_enable = netif_msg_init(debug, DEFAULT_MSG_ENABLE);

	adapter->hw.hw_addr = pci_ioremap_bar(pdev, BAR_0);
	if (!adapter->hw.hw_addr) {
		err = -EIO;
		goto err_ioremap;
	}

	for (i = BAR_1; i <= BAR_5; i++) {
		if (pci_resource_len(pdev, i) == 0)
			continue;
		if (pci_resource_flags(pdev, i) & IORESOURCE_IO) {
			adapter->hw.io_base = pci_resource_start(pdev, i);
			break;
		}
	}

	netdev->netdev_ops = &ixgb_netdev_ops;
	ixgb_set_ethtool_ops(netdev);
	netdev->watchdog_timeo = 5 * HZ;
	netif_napi_add(netdev, &adapter->napi, ixgb_clean, 64);

	strncpy(netdev->name, pci_name(pdev), sizeof(netdev->name) - 1);

	adapter->bd_number = cards_found;
	adapter->link_speed = 0;
	adapter->link_duplex = 0;

	/* setup the private structure */

	err = ixgb_sw_init(adapter);
	if (err)
		goto err_sw_init;

	netdev->hw_features = NETIF_F_SG |
			   NETIF_F_TSO |
			   NETIF_F_HW_CSUM |
			   NETIF_F_HW_VLAN_CTAG_TX |
			   NETIF_F_HW_VLAN_CTAG_RX;
	netdev->features = netdev->hw_features |
			   NETIF_F_HW_VLAN_CTAG_FILTER;
	netdev->hw_features |= NETIF_F_RXCSUM;

	if (pci_using_dac) {
		netdev->features |= NETIF_F_HIGHDMA;
		netdev->vlan_features |= NETIF_F_HIGHDMA;
	}

	/* MTU range: 68 - 16114 */
	netdev->min_mtu = ETH_MIN_MTU;
	netdev->max_mtu = IXGB_MAX_JUMBO_FRAME_SIZE - ETH_HLEN;

	/* make sure the EEPROM is good */

	if (!ixgb_validate_eeprom_checksum(&adapter->hw)) {
		netif_err(adapter, probe, adapter->netdev,
			  "The EEPROM Checksum Is Not Valid\n");
		err = -EIO;
		goto err_eeprom;
	}

	ixgb_get_ee_mac_addr(&adapter->hw, netdev->dev_addr);

	if (!is_valid_ether_addr(netdev->dev_addr)) {
		netif_err(adapter, probe, adapter->netdev, "Invalid MAC Address\n");
		err = -EIO;
		goto err_eeprom;
	}

	adapter->part_num = ixgb_get_ee_pba_number(&adapter->hw);

	timer_setup(&adapter->watchdog_timer, ixgb_watchdog, 0);

	INIT_WORK(&adapter->tx_timeout_task, ixgb_tx_timeout_task);

	strcpy(netdev->name, "eth%d");
	err = register_netdev(netdev);
	if (err)
		goto err_register;

	/* carrier off reporting is important to ethtool even BEFORE open */
	netif_carrier_off(netdev);

	netif_info(adapter, probe, adapter->netdev,
		   "Intel(R) PRO/10GbE Network Connection\n");
	ixgb_check_options(adapter);
	/* reset the hardware with the new settings */

	ixgb_reset(adapter);

	cards_found++;
	return 0;

err_register:
err_sw_init:
err_eeprom:
	iounmap(adapter->hw.hw_addr);
err_ioremap:
	free_netdev(netdev);
err_alloc_etherdev:
	pci_release_regions(pdev);
err_request_regions:
err_dma_mask:
	pci_disable_device(pdev);
	return err;
}