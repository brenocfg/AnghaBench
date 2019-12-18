#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct resource {scalar_t__ start; } ;
struct platform_device {char* name; int id; int /*<<< orphan*/  dev; } ;
struct net_device {int irq; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; scalar_t__ base_addr; int /*<<< orphan*/  dev_addr; } ;
typedef  scalar_t__ mac_reg ;
struct db_dest {scalar_t__ dma_addr; scalar_t__* vaddr; struct db_dest* pnext; } ;
struct au1000_private {int msg_enable; int mac_id; int phy1_search_mac0; size_t phy_addr; scalar_t__ phy_busid; int /*<<< orphan*/  dma_addr; scalar_t__ vaddr; scalar_t__* mac; scalar_t__* enable; scalar_t__* macdma; TYPE_3__* mii_bus; struct db_dest** tx_db_inuse; struct db_dest** rx_db_inuse; TYPE_2__** tx_dma_ring; TYPE_1__** rx_dma_ring; struct db_dest* pDBfree; struct db_dest* db; scalar_t__ phy_irq; scalar_t__ phy_static_config; int /*<<< orphan*/  phy_search_highest_addr; scalar_t__ mac_enabled; int /*<<< orphan*/  lock; } ;
struct au1000_eth_platform_data {int phy1_search_mac0; size_t phy_addr; scalar_t__ phy_busid; scalar_t__ phy_irq; int /*<<< orphan*/  phy_search_highest_addr; scalar_t__ phy_static_config; int /*<<< orphan*/  mac; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_9__ {char* name; scalar_t__* irq; int /*<<< orphan*/  id; int /*<<< orphan*/  reset; int /*<<< orphan*/  write; int /*<<< orphan*/  read; struct net_device* priv; } ;
struct TYPE_8__ {unsigned int buff_stat; scalar_t__ len; } ;
struct TYPE_7__ {unsigned int buff_stat; } ;

/* Variables and functions */
 int AU1000_DEF_MSG_ENABLE ; 
 int /*<<< orphan*/  DMA_ATTR_NON_CONSISTENT ; 
 int /*<<< orphan*/  DRV_AUTHOR ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  DRV_VERSION ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  ETH_TX_TIMEOUT ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int MAX_BUF_SIZE ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int NUM_RX_BUFFS ; 
 int NUM_RX_DMA ; 
 int NUM_TX_BUFFS ; 
 int NUM_TX_DMA ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_etherdev (int) ; 
 struct db_dest* au1000_GetFreeDB (struct au1000_private*) ; 
 int /*<<< orphan*/  au1000_ReleaseDB (struct au1000_private*,struct db_dest*) ; 
 int au1000_debug ; 
 int /*<<< orphan*/  au1000_ethtool_ops ; 
 int /*<<< orphan*/  au1000_mdiobus_read ; 
 int /*<<< orphan*/  au1000_mdiobus_reset ; 
 int /*<<< orphan*/  au1000_mdiobus_write ; 
 int au1000_mii_probe (struct net_device*) ; 
 int /*<<< orphan*/  au1000_netdev_ops ; 
 int /*<<< orphan*/  au1000_reset_mac (struct net_device*) ; 
 int /*<<< orphan*/  au1000_setup_hw_rings (struct au1000_private*,scalar_t__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct au1000_eth_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ dma_alloc_attrs (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_attrs (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 scalar_t__* ioremap_nocache (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (scalar_t__*) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 TYPE_3__* mdiobus_alloc () ; 
 int /*<<< orphan*/  mdiobus_free (TYPE_3__*) ; 
 int mdiobus_register (TYPE_3__*) ; 
 int /*<<< orphan*/  mdiobus_unregister (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,unsigned long,int) ; 
 struct au1000_private* netdev_priv (struct net_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int /*<<< orphan*/  pr_info_once (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_mem_region (scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ virt_to_bus (scalar_t__*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int au1000_probe(struct platform_device *pdev)
{
	struct au1000_private *aup = NULL;
	struct au1000_eth_platform_data *pd;
	struct net_device *dev = NULL;
	struct db_dest *pDB, *pDBfree;
	int irq, i, err = 0;
	struct resource *base, *macen, *macdma;

	base = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!base) {
		dev_err(&pdev->dev, "failed to retrieve base register\n");
		err = -ENODEV;
		goto out;
	}

	macen = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (!macen) {
		dev_err(&pdev->dev, "failed to retrieve MAC Enable register\n");
		err = -ENODEV;
		goto out;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		err = -ENODEV;
		goto out;
	}

	macdma = platform_get_resource(pdev, IORESOURCE_MEM, 2);
	if (!macdma) {
		dev_err(&pdev->dev, "failed to retrieve MACDMA registers\n");
		err = -ENODEV;
		goto out;
	}

	if (!request_mem_region(base->start, resource_size(base),
							pdev->name)) {
		dev_err(&pdev->dev, "failed to request memory region for base registers\n");
		err = -ENXIO;
		goto out;
	}

	if (!request_mem_region(macen->start, resource_size(macen),
							pdev->name)) {
		dev_err(&pdev->dev, "failed to request memory region for MAC enable register\n");
		err = -ENXIO;
		goto err_request;
	}

	if (!request_mem_region(macdma->start, resource_size(macdma),
							pdev->name)) {
		dev_err(&pdev->dev, "failed to request MACDMA memory region\n");
		err = -ENXIO;
		goto err_macdma;
	}

	dev = alloc_etherdev(sizeof(struct au1000_private));
	if (!dev) {
		err = -ENOMEM;
		goto err_alloc;
	}

	SET_NETDEV_DEV(dev, &pdev->dev);
	platform_set_drvdata(pdev, dev);
	aup = netdev_priv(dev);

	spin_lock_init(&aup->lock);
	aup->msg_enable = (au1000_debug < 4 ?
				AU1000_DEF_MSG_ENABLE : au1000_debug);

	/* Allocate the data buffers
	 * Snooping works fine with eth on all au1xxx
	 */
	aup->vaddr = (u32)dma_alloc_attrs(&pdev->dev, MAX_BUF_SIZE *
					  (NUM_TX_BUFFS + NUM_RX_BUFFS),
					  &aup->dma_addr, 0,
					  DMA_ATTR_NON_CONSISTENT);
	if (!aup->vaddr) {
		dev_err(&pdev->dev, "failed to allocate data buffers\n");
		err = -ENOMEM;
		goto err_vaddr;
	}

	/* aup->mac is the base address of the MAC's registers */
	aup->mac = (struct mac_reg *)
			ioremap_nocache(base->start, resource_size(base));
	if (!aup->mac) {
		dev_err(&pdev->dev, "failed to ioremap MAC registers\n");
		err = -ENXIO;
		goto err_remap1;
	}

	/* Setup some variables for quick register address access */
	aup->enable = (u32 *)ioremap_nocache(macen->start,
						resource_size(macen));
	if (!aup->enable) {
		dev_err(&pdev->dev, "failed to ioremap MAC enable register\n");
		err = -ENXIO;
		goto err_remap2;
	}
	aup->mac_id = pdev->id;

	aup->macdma = ioremap_nocache(macdma->start, resource_size(macdma));
	if (!aup->macdma) {
		dev_err(&pdev->dev, "failed to ioremap MACDMA registers\n");
		err = -ENXIO;
		goto err_remap3;
	}

	au1000_setup_hw_rings(aup, aup->macdma);

	writel(0, aup->enable);
	aup->mac_enabled = 0;

	pd = dev_get_platdata(&pdev->dev);
	if (!pd) {
		dev_info(&pdev->dev, "no platform_data passed,"
					" PHY search on MAC0\n");
		aup->phy1_search_mac0 = 1;
	} else {
		if (is_valid_ether_addr(pd->mac)) {
			memcpy(dev->dev_addr, pd->mac, ETH_ALEN);
		} else {
			/* Set a random MAC since no valid provided by platform_data. */
			eth_hw_addr_random(dev);
		}

		aup->phy_static_config = pd->phy_static_config;
		aup->phy_search_highest_addr = pd->phy_search_highest_addr;
		aup->phy1_search_mac0 = pd->phy1_search_mac0;
		aup->phy_addr = pd->phy_addr;
		aup->phy_busid = pd->phy_busid;
		aup->phy_irq = pd->phy_irq;
	}

	if (aup->phy_busid > 0) {
		dev_err(&pdev->dev, "MAC0-associated PHY attached 2nd MACs MII bus not supported yet\n");
		err = -ENODEV;
		goto err_mdiobus_alloc;
	}

	aup->mii_bus = mdiobus_alloc();
	if (aup->mii_bus == NULL) {
		dev_err(&pdev->dev, "failed to allocate mdiobus structure\n");
		err = -ENOMEM;
		goto err_mdiobus_alloc;
	}

	aup->mii_bus->priv = dev;
	aup->mii_bus->read = au1000_mdiobus_read;
	aup->mii_bus->write = au1000_mdiobus_write;
	aup->mii_bus->reset = au1000_mdiobus_reset;
	aup->mii_bus->name = "au1000_eth_mii";
	snprintf(aup->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		pdev->name, aup->mac_id);

	/* if known, set corresponding PHY IRQs */
	if (aup->phy_static_config)
		if (aup->phy_irq && aup->phy_busid == aup->mac_id)
			aup->mii_bus->irq[aup->phy_addr] = aup->phy_irq;

	err = mdiobus_register(aup->mii_bus);
	if (err) {
		dev_err(&pdev->dev, "failed to register MDIO bus\n");
		goto err_mdiobus_reg;
	}

	err = au1000_mii_probe(dev);
	if (err != 0)
		goto err_out;

	pDBfree = NULL;
	/* setup the data buffer descriptors and attach a buffer to each one */
	pDB = aup->db;
	for (i = 0; i < (NUM_TX_BUFFS+NUM_RX_BUFFS); i++) {
		pDB->pnext = pDBfree;
		pDBfree = pDB;
		pDB->vaddr = (u32 *)((unsigned)aup->vaddr + MAX_BUF_SIZE*i);
		pDB->dma_addr = (dma_addr_t)virt_to_bus(pDB->vaddr);
		pDB++;
	}
	aup->pDBfree = pDBfree;

	err = -ENODEV;
	for (i = 0; i < NUM_RX_DMA; i++) {
		pDB = au1000_GetFreeDB(aup);
		if (!pDB)
			goto err_out;

		aup->rx_dma_ring[i]->buff_stat = (unsigned)pDB->dma_addr;
		aup->rx_db_inuse[i] = pDB;
	}

	err = -ENODEV;
	for (i = 0; i < NUM_TX_DMA; i++) {
		pDB = au1000_GetFreeDB(aup);
		if (!pDB)
			goto err_out;

		aup->tx_dma_ring[i]->buff_stat = (unsigned)pDB->dma_addr;
		aup->tx_dma_ring[i]->len = 0;
		aup->tx_db_inuse[i] = pDB;
	}

	dev->base_addr = base->start;
	dev->irq = irq;
	dev->netdev_ops = &au1000_netdev_ops;
	dev->ethtool_ops = &au1000_ethtool_ops;
	dev->watchdog_timeo = ETH_TX_TIMEOUT;

	/*
	 * The boot code uses the ethernet controller, so reset it to start
	 * fresh.  au1000_init() expects that the device is in reset state.
	 */
	au1000_reset_mac(dev);

	err = register_netdev(dev);
	if (err) {
		netdev_err(dev, "Cannot register net device, aborting.\n");
		goto err_out;
	}

	netdev_info(dev, "Au1xx0 Ethernet found at 0x%lx, irq %d\n",
			(unsigned long)base->start, irq);

	pr_info_once("%s version %s %s\n", DRV_NAME, DRV_VERSION, DRV_AUTHOR);

	return 0;

err_out:
	if (aup->mii_bus != NULL)
		mdiobus_unregister(aup->mii_bus);

	/* here we should have a valid dev plus aup-> register addresses
	 * so we can reset the mac properly.
	 */
	au1000_reset_mac(dev);

	for (i = 0; i < NUM_RX_DMA; i++) {
		if (aup->rx_db_inuse[i])
			au1000_ReleaseDB(aup, aup->rx_db_inuse[i]);
	}
	for (i = 0; i < NUM_TX_DMA; i++) {
		if (aup->tx_db_inuse[i])
			au1000_ReleaseDB(aup, aup->tx_db_inuse[i]);
	}
err_mdiobus_reg:
	mdiobus_free(aup->mii_bus);
err_mdiobus_alloc:
	iounmap(aup->macdma);
err_remap3:
	iounmap(aup->enable);
err_remap2:
	iounmap(aup->mac);
err_remap1:
	dma_free_attrs(&pdev->dev, MAX_BUF_SIZE * (NUM_TX_BUFFS + NUM_RX_BUFFS),
			(void *)aup->vaddr, aup->dma_addr,
			DMA_ATTR_NON_CONSISTENT);
err_vaddr:
	free_netdev(dev);
err_alloc:
	release_mem_region(macdma->start, resource_size(macdma));
err_macdma:
	release_mem_region(macen->start, resource_size(macen));
err_request:
	release_mem_region(base->start, resource_size(base));
out:
	return err;
}