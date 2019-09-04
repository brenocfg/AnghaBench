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
struct pci_device_id {int driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  dev_flags; int /*<<< orphan*/  pm_cap; } ;
struct net_device {int hw_features; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  perm_addr; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/  irq; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_2__ {int mode_support; int /*<<< orphan*/  mdio_write; int /*<<< orphan*/  mdio_read; struct net_device* dev; scalar_t__ mmds; scalar_t__ prtad; } ;
struct alx_hw {int /*<<< orphan*/  hw_addr; TYPE_1__ mdio; int /*<<< orphan*/  perm_addr; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  flowctrl; int /*<<< orphan*/  adv_cfg; struct pci_dev* pdev; int /*<<< orphan*/  mdio_lock; } ;
struct alx_priv {int msg_enable; int /*<<< orphan*/  reset_wk; int /*<<< orphan*/  link_check_wk; struct alx_hw hw; struct net_device* dev; int /*<<< orphan*/  stats_lock; int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int ALX_DEV_QUIRK_MSI_INTX_DISABLE_BUG ; 
 int /*<<< orphan*/  ALX_MAX_TX_QUEUES ; 
 int /*<<< orphan*/  ALX_WATCHDOG_TIME ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MDIO_EMULATE_C22 ; 
 int MDIO_SUPPORTS_C22 ; 
 int MDIO_SUPPORTS_C45 ; 
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int NETIF_MSG_HW ; 
 int NETIF_MSG_IFUP ; 
 int NETIF_MSG_LINK ; 
 int NETIF_MSG_RX_ERR ; 
 int NETIF_MSG_TX_ERR ; 
 int NETIF_MSG_WOL ; 
 int /*<<< orphan*/  PCI_DEV_FLAGS_MSI_INTX_DISABLE_BUG ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_etherdev_mqs (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  alx_drv_name ; 
 int /*<<< orphan*/  alx_ethtool_ops ; 
 scalar_t__ alx_get_perm_macaddr (struct alx_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alx_get_phy_info (struct alx_hw*) ; 
 int alx_init_sw (struct alx_priv*) ; 
 int /*<<< orphan*/  alx_link_check ; 
 int /*<<< orphan*/  alx_mdio_read ; 
 int /*<<< orphan*/  alx_mdio_write ; 
 int /*<<< orphan*/  alx_netdev_ops ; 
 int alx_phy_configured (struct alx_hw*) ; 
 int /*<<< orphan*/  alx_reset ; 
 int alx_reset_mac (struct alx_hw*) ; 
 int /*<<< orphan*/  alx_reset_pcie (struct alx_hw*) ; 
 int /*<<< orphan*/  alx_reset_phy (struct alx_hw*) ; 
 int alx_setup_speed_duplex (struct alx_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 struct alx_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device_mem (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_pcie_error_reporting (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_ioremap_bar (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_mem_regions (struct pci_dev*) ; 
 int pci_request_mem_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct alx_priv*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alx_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	struct net_device *netdev;
	struct alx_priv *alx;
	struct alx_hw *hw;
	bool phy_configured;
	int err;

	err = pci_enable_device_mem(pdev);
	if (err)
		return err;

	/* The alx chip can DMA to 64-bit addresses, but it uses a single
	 * shared register for the high 32 bits, so only a single, aligned,
	 * 4 GB physical address range can be used for descriptors.
	 */
	if (!dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64))) {
		dev_dbg(&pdev->dev, "DMA to 64-BIT addresses\n");
	} else {
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		if (err) {
			dev_err(&pdev->dev, "No usable DMA config, aborting\n");
			goto out_pci_disable;
		}
	}

	err = pci_request_mem_regions(pdev, alx_drv_name);
	if (err) {
		dev_err(&pdev->dev,
			"pci_request_mem_regions failed\n");
		goto out_pci_disable;
	}

	pci_enable_pcie_error_reporting(pdev);
	pci_set_master(pdev);

	if (!pdev->pm_cap) {
		dev_err(&pdev->dev,
			"Can't find power management capability, aborting\n");
		err = -EIO;
		goto out_pci_release;
	}

	netdev = alloc_etherdev_mqs(sizeof(*alx),
				    ALX_MAX_TX_QUEUES, 1);
	if (!netdev) {
		err = -ENOMEM;
		goto out_pci_release;
	}

	SET_NETDEV_DEV(netdev, &pdev->dev);
	alx = netdev_priv(netdev);
	spin_lock_init(&alx->hw.mdio_lock);
	spin_lock_init(&alx->irq_lock);
	spin_lock_init(&alx->stats_lock);
	alx->dev = netdev;
	alx->hw.pdev = pdev;
	alx->msg_enable = NETIF_MSG_LINK | NETIF_MSG_HW | NETIF_MSG_IFUP |
			  NETIF_MSG_TX_ERR | NETIF_MSG_RX_ERR | NETIF_MSG_WOL;
	hw = &alx->hw;
	pci_set_drvdata(pdev, alx);

	hw->hw_addr = pci_ioremap_bar(pdev, 0);
	if (!hw->hw_addr) {
		dev_err(&pdev->dev, "cannot map device registers\n");
		err = -EIO;
		goto out_free_netdev;
	}

	netdev->netdev_ops = &alx_netdev_ops;
	netdev->ethtool_ops = &alx_ethtool_ops;
	netdev->irq = pci_irq_vector(pdev, 0);
	netdev->watchdog_timeo = ALX_WATCHDOG_TIME;

	if (ent->driver_data & ALX_DEV_QUIRK_MSI_INTX_DISABLE_BUG)
		pdev->dev_flags |= PCI_DEV_FLAGS_MSI_INTX_DISABLE_BUG;

	err = alx_init_sw(alx);
	if (err) {
		dev_err(&pdev->dev, "net device private data init failed\n");
		goto out_unmap;
	}

	alx_reset_pcie(hw);

	phy_configured = alx_phy_configured(hw);

	if (!phy_configured)
		alx_reset_phy(hw);

	err = alx_reset_mac(hw);
	if (err) {
		dev_err(&pdev->dev, "MAC Reset failed, error = %d\n", err);
		goto out_unmap;
	}

	/* setup link to put it in a known good starting state */
	if (!phy_configured) {
		err = alx_setup_speed_duplex(hw, hw->adv_cfg, hw->flowctrl);
		if (err) {
			dev_err(&pdev->dev,
				"failed to configure PHY speed/duplex (err=%d)\n",
				err);
			goto out_unmap;
		}
	}

	netdev->hw_features = NETIF_F_SG |
			      NETIF_F_HW_CSUM |
			      NETIF_F_RXCSUM |
			      NETIF_F_TSO |
			      NETIF_F_TSO6;

	if (alx_get_perm_macaddr(hw, hw->perm_addr)) {
		dev_warn(&pdev->dev,
			 "Invalid permanent address programmed, using random one\n");
		eth_hw_addr_random(netdev);
		memcpy(hw->perm_addr, netdev->dev_addr, netdev->addr_len);
	}

	memcpy(hw->mac_addr, hw->perm_addr, ETH_ALEN);
	memcpy(netdev->dev_addr, hw->mac_addr, ETH_ALEN);
	memcpy(netdev->perm_addr, hw->perm_addr, ETH_ALEN);

	hw->mdio.prtad = 0;
	hw->mdio.mmds = 0;
	hw->mdio.dev = netdev;
	hw->mdio.mode_support = MDIO_SUPPORTS_C45 |
				MDIO_SUPPORTS_C22 |
				MDIO_EMULATE_C22;
	hw->mdio.mdio_read = alx_mdio_read;
	hw->mdio.mdio_write = alx_mdio_write;

	if (!alx_get_phy_info(hw)) {
		dev_err(&pdev->dev, "failed to identify PHY\n");
		err = -EIO;
		goto out_unmap;
	}

	INIT_WORK(&alx->link_check_wk, alx_link_check);
	INIT_WORK(&alx->reset_wk, alx_reset);
	netif_carrier_off(netdev);

	err = register_netdev(netdev);
	if (err) {
		dev_err(&pdev->dev, "register netdevice failed\n");
		goto out_unmap;
	}

	netdev_info(netdev,
		    "Qualcomm Atheros AR816x/AR817x Ethernet [%pM]\n",
		    netdev->dev_addr);

	return 0;

out_unmap:
	iounmap(hw->hw_addr);
out_free_netdev:
	free_netdev(netdev);
out_pci_release:
	pci_release_mem_regions(pdev);
out_pci_disable:
	pci_disable_device(pdev);
	return err;
}