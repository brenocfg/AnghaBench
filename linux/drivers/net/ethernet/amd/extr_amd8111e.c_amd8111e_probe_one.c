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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; scalar_t__ pm_cap; } ;
struct net_device {int features; int /*<<< orphan*/ * dev_addr; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/  irq; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_6__ {scalar_t__ expires; } ;
struct TYPE_5__ {int /*<<< orphan*/  ipg_state; int /*<<< orphan*/  ipg; TYPE_3__ ipg_timer; } ;
struct TYPE_4__ {int /*<<< orphan*/  phy_id; int /*<<< orphan*/  mdio_write; int /*<<< orphan*/  mdio_read; struct net_device* dev; } ;
struct amd8111e_priv {int options; int ext_phy_id; int /*<<< orphan*/  ext_phy_addr; scalar_t__ mmio; TYPE_2__ ipg_data; TYPE_1__ mii_if; int /*<<< orphan*/  napi; int /*<<< orphan*/  ext_phy_option; int /*<<< orphan*/  lock; scalar_t__ pm_cap; struct net_device* amd8111e_net_dev; struct pci_dev* pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD8111E_MAX_MTU ; 
 int /*<<< orphan*/  AMD8111E_MIN_MTU ; 
 int /*<<< orphan*/  AMD8111E_TX_TIMEOUT ; 
 scalar_t__ CHIPID ; 
 int /*<<< orphan*/  CSTATE ; 
 int /*<<< orphan*/  DEFAULT_IPG ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int IORESOURCE_MEM ; 
 scalar_t__ IPG_CONVERGE_JIFFIES ; 
 int /*<<< orphan*/  MODULE_NAME ; 
 int /*<<< orphan*/  MODULE_VERS ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int OPTION_DYN_IPG_ENABLE ; 
 int OPTION_INTR_COAL_ENABLE ; 
 scalar_t__ PADR ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  amd8111e_config_ipg ; 
 int /*<<< orphan*/  amd8111e_mdio_read ; 
 int /*<<< orphan*/  amd8111e_mdio_write ; 
 int /*<<< orphan*/  amd8111e_netdev_ops ; 
 int /*<<< orphan*/  amd8111e_probe_ext_phy (struct net_device*) ; 
 int /*<<< orphan*/  amd8111e_rx_poll ; 
 int /*<<< orphan*/  amd8111e_set_rx_buff_len (struct net_device*) ; 
 size_t card_idx ; 
 int chip_version ; 
 scalar_t__* coalesce ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ devm_ioremap (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 scalar_t__* dynamic_ipg ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 scalar_t__ jiffies ; 
 struct amd8111e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ops ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_resource_flags (struct pci_dev*,int /*<<< orphan*/ ) ; 
 unsigned long pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 unsigned long pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct net_device*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int readl (scalar_t__) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/ * speed_duplex ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amd8111e_probe_one(struct pci_dev *pdev,
				  const struct pci_device_id *ent)
{
	int err, i;
	unsigned long reg_addr,reg_len;
	struct amd8111e_priv *lp;
	struct net_device *dev;

	err = pci_enable_device(pdev);
	if(err){
		dev_err(&pdev->dev, "Cannot enable new PCI device\n");
		return err;
	}

	if(!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)){
		dev_err(&pdev->dev, "Cannot find PCI base address\n");
		err = -ENODEV;
		goto err_disable_pdev;
	}

	err = pci_request_regions(pdev, MODULE_NAME);
	if(err){
		dev_err(&pdev->dev, "Cannot obtain PCI resources\n");
		goto err_disable_pdev;
	}

	pci_set_master(pdev);

	/* Find power-management capability. */
	if (!pdev->pm_cap) {
		dev_err(&pdev->dev, "No Power Management capability\n");
		err = -ENODEV;
		goto err_free_reg;
	}

	/* Initialize DMA */
	if (pci_set_dma_mask(pdev, DMA_BIT_MASK(32)) < 0) {
		dev_err(&pdev->dev, "DMA not supported\n");
		err = -ENODEV;
		goto err_free_reg;
	}

	reg_addr = pci_resource_start(pdev, 0);
	reg_len = pci_resource_len(pdev, 0);

	dev = alloc_etherdev(sizeof(struct amd8111e_priv));
	if (!dev) {
		err = -ENOMEM;
		goto err_free_reg;
	}

	SET_NETDEV_DEV(dev, &pdev->dev);

#if AMD8111E_VLAN_TAG_USED
	dev->features |= NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX ;
#endif

	lp = netdev_priv(dev);
	lp->pci_dev = pdev;
	lp->amd8111e_net_dev = dev;
	lp->pm_cap = pdev->pm_cap;

	spin_lock_init(&lp->lock);

	lp->mmio = devm_ioremap(&pdev->dev, reg_addr, reg_len);
	if (!lp->mmio) {
		dev_err(&pdev->dev, "Cannot map device registers\n");
		err = -ENOMEM;
		goto err_free_dev;
	}

	/* Initializing MAC address */
	for (i = 0; i < ETH_ALEN; i++)
		dev->dev_addr[i] = readb(lp->mmio + PADR + i);

	/* Setting user defined parametrs */
	lp->ext_phy_option = speed_duplex[card_idx];
	if(coalesce[card_idx])
		lp->options |= OPTION_INTR_COAL_ENABLE;
	if(dynamic_ipg[card_idx++])
		lp->options |= OPTION_DYN_IPG_ENABLE;


	/* Initialize driver entry points */
	dev->netdev_ops = &amd8111e_netdev_ops;
	dev->ethtool_ops = &ops;
	dev->irq =pdev->irq;
	dev->watchdog_timeo = AMD8111E_TX_TIMEOUT;
	dev->min_mtu = AMD8111E_MIN_MTU;
	dev->max_mtu = AMD8111E_MAX_MTU;
	netif_napi_add(dev, &lp->napi, amd8111e_rx_poll, 32);

#if AMD8111E_VLAN_TAG_USED
	dev->features |= NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX;
#endif
	/* Probe the external PHY */
	amd8111e_probe_ext_phy(dev);

	/* setting mii default values */
	lp->mii_if.dev = dev;
	lp->mii_if.mdio_read = amd8111e_mdio_read;
	lp->mii_if.mdio_write = amd8111e_mdio_write;
	lp->mii_if.phy_id = lp->ext_phy_addr;

	/* Set receive buffer length and set jumbo option*/
	amd8111e_set_rx_buff_len(dev);


	err = register_netdev(dev);
	if (err) {
		dev_err(&pdev->dev, "Cannot register net device\n");
		goto err_free_dev;
	}

	pci_set_drvdata(pdev, dev);

	/* Initialize software ipg timer */
	if(lp->options & OPTION_DYN_IPG_ENABLE){
		timer_setup(&lp->ipg_data.ipg_timer, amd8111e_config_ipg, 0);
		lp->ipg_data.ipg_timer.expires = jiffies +
						 IPG_CONVERGE_JIFFIES;
		lp->ipg_data.ipg = DEFAULT_IPG;
		lp->ipg_data.ipg_state = CSTATE;
	}

	/*  display driver and device information */
    	chip_version = (readl(lp->mmio + CHIPID) & 0xf0000000)>>28;
	dev_info(&pdev->dev, "AMD-8111e Driver Version: %s\n", MODULE_VERS);
	dev_info(&pdev->dev, "[ Rev %x ] PCI 10/100BaseT Ethernet %pM\n",
		 chip_version, dev->dev_addr);
	if (lp->ext_phy_id)
		dev_info(&pdev->dev, "Found MII PHY ID 0x%08x at address 0x%02x\n",
			 lp->ext_phy_id, lp->ext_phy_addr);
	else
		dev_info(&pdev->dev, "Couldn't detect MII PHY, assuming address 0x01\n");

    	return 0;

err_free_dev:
	free_netdev(dev);

err_free_reg:
	pci_release_regions(pdev);

err_disable_pdev:
	pci_disable_device(pdev);
	return err;

}