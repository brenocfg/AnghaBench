#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  hw_addr; int /*<<< orphan*/  mac_addr; struct atl1e_adapter* adapter; } ;
struct TYPE_5__ {int phy_id_mask; int /*<<< orphan*/  reg_num_mask; int /*<<< orphan*/  mdio_write; int /*<<< orphan*/  mdio_read; struct net_device* dev; } ;
struct atl1e_adapter {int bd_number; TYPE_2__ hw; int /*<<< orphan*/  link_chg_task; int /*<<< orphan*/  reset_task; int /*<<< orphan*/  phy_config_timer; int /*<<< orphan*/  napi; TYPE_1__ mii; struct pci_dev* pdev; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAR_0 ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_TSO_SEG_SIZE ; 
 int /*<<< orphan*/  MDIO_REG_ADDR_MASK ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  atl1e_check_options (struct atl1e_adapter*) ; 
 int /*<<< orphan*/  atl1e_clean ; 
 int /*<<< orphan*/  atl1e_driver_name ; 
 int atl1e_init_netdev (struct net_device*,struct pci_dev*) ; 
 int /*<<< orphan*/  atl1e_link_chg_task ; 
 int /*<<< orphan*/  atl1e_mdio_read ; 
 int /*<<< orphan*/  atl1e_mdio_write ; 
 int /*<<< orphan*/  atl1e_phy_config ; 
 int /*<<< orphan*/  atl1e_phy_init (TYPE_2__*) ; 
 scalar_t__ atl1e_read_mac_addr (TYPE_2__*) ; 
 int atl1e_reset_hw (TYPE_2__*) ; 
 int /*<<< orphan*/  atl1e_reset_task ; 
 int /*<<< orphan*/  atl1e_setup_pcicmd (struct pci_dev*) ; 
 int atl1e_sw_init (struct atl1e_adapter*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct atl1e_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_set_gso_max_size (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iomap (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atl1e_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	struct net_device *netdev;
	struct atl1e_adapter *adapter = NULL;
	static int cards_found;

	int err = 0;

	err = pci_enable_device(pdev);
	if (err) {
		dev_err(&pdev->dev, "cannot enable PCI device\n");
		return err;
	}

	/*
	 * The atl1e chip can DMA to 64-bit addresses, but it uses a single
	 * shared register for the high 32 bits, so only a single, aligned,
	 * 4 GB physical address range can be used at a time.
	 *
	 * Supporting 64-bit DMA on this hardware is more trouble than it's
	 * worth.  It is far easier to limit to 32-bit DMA than update
	 * various kernel subsystems to support the mechanics required by a
	 * fixed-high-32-bit system.
	 */
	if ((pci_set_dma_mask(pdev, DMA_BIT_MASK(32)) != 0) ||
	    (pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32)) != 0)) {
		dev_err(&pdev->dev, "No usable DMA configuration,aborting\n");
		goto err_dma;
	}

	err = pci_request_regions(pdev, atl1e_driver_name);
	if (err) {
		dev_err(&pdev->dev, "cannot obtain PCI resources\n");
		goto err_pci_reg;
	}

	pci_set_master(pdev);

	netdev = alloc_etherdev(sizeof(struct atl1e_adapter));
	if (netdev == NULL) {
		err = -ENOMEM;
		goto err_alloc_etherdev;
	}

	err = atl1e_init_netdev(netdev, pdev);
	if (err) {
		netdev_err(netdev, "init netdevice failed\n");
		goto err_init_netdev;
	}
	adapter = netdev_priv(netdev);
	adapter->bd_number = cards_found;
	adapter->netdev = netdev;
	adapter->pdev = pdev;
	adapter->hw.adapter = adapter;
	adapter->hw.hw_addr = pci_iomap(pdev, BAR_0, 0);
	if (!adapter->hw.hw_addr) {
		err = -EIO;
		netdev_err(netdev, "cannot map device registers\n");
		goto err_ioremap;
	}

	/* init mii data */
	adapter->mii.dev = netdev;
	adapter->mii.mdio_read  = atl1e_mdio_read;
	adapter->mii.mdio_write = atl1e_mdio_write;
	adapter->mii.phy_id_mask = 0x1f;
	adapter->mii.reg_num_mask = MDIO_REG_ADDR_MASK;

	netif_napi_add(netdev, &adapter->napi, atl1e_clean, 64);

	timer_setup(&adapter->phy_config_timer, atl1e_phy_config, 0);

	/* get user settings */
	atl1e_check_options(adapter);
	/*
	 * Mark all PCI regions associated with PCI device
	 * pdev as being reserved by owner atl1e_driver_name
	 * Enables bus-mastering on the device and calls
	 * pcibios_set_master to do the needed arch specific settings
	 */
	atl1e_setup_pcicmd(pdev);
	/* setup the private structure */
	err = atl1e_sw_init(adapter);
	if (err) {
		netdev_err(netdev, "net device private data init failed\n");
		goto err_sw_init;
	}

	/* Init GPHY as early as possible due to power saving issue  */
	atl1e_phy_init(&adapter->hw);
	/* reset the controller to
	 * put the device in a known good starting state */
	err = atl1e_reset_hw(&adapter->hw);
	if (err) {
		err = -EIO;
		goto err_reset;
	}

	if (atl1e_read_mac_addr(&adapter->hw) != 0) {
		err = -EIO;
		netdev_err(netdev, "get mac address failed\n");
		goto err_eeprom;
	}

	memcpy(netdev->dev_addr, adapter->hw.mac_addr, netdev->addr_len);
	netdev_dbg(netdev, "mac address : %pM\n", adapter->hw.mac_addr);

	INIT_WORK(&adapter->reset_task, atl1e_reset_task);
	INIT_WORK(&adapter->link_chg_task, atl1e_link_chg_task);
	netif_set_gso_max_size(netdev, MAX_TSO_SEG_SIZE);
	err = register_netdev(netdev);
	if (err) {
		netdev_err(netdev, "register netdevice failed\n");
		goto err_register;
	}

	/* assume we have no link for now */
	netif_stop_queue(netdev);
	netif_carrier_off(netdev);

	cards_found++;

	return 0;

err_reset:
err_register:
err_sw_init:
err_eeprom:
	pci_iounmap(pdev, adapter->hw.hw_addr);
err_init_netdev:
err_ioremap:
	free_netdev(netdev);
err_alloc_etherdev:
	pci_release_regions(pdev);
err_pci_reg:
err_dma:
	pci_disable_device(pdev);
	return err;
}