#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct temac_local {void const* regs; int temac_features; void const* sdma_regs; int rx_irq; int tx_irq; int tx_chnl_ctrl; int rx_chnl_ctrl; void const* phy_node; TYPE_2__* dev; struct net_device* ndev; int /*<<< orphan*/  phy_interface; int /*<<< orphan*/  phy_name; TYPE_1__* mii_bus; void* dma_out; void* dma_in; int /*<<< orphan*/  temac_iow; int /*<<< orphan*/  temac_ior; int /*<<< orphan*/ * indirect_lock; int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  options; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_13__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_2__ dev; } ;
struct net_device {int /*<<< orphan*/  features; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;
struct ll_temac_platform_data {int reg_little_endian; int tx_irq_timeout; int tx_irq_count; int rx_irq_timeout; int rx_irq_count; void const* mac_addr; int /*<<< orphan*/  phy_interface; int /*<<< orphan*/  phy_addr; scalar_t__ dma_little_endian; scalar_t__ rxcsum; scalar_t__ txcsum; int /*<<< orphan*/ * indirect_lock; } ;
typedef  void const device_node ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_12__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void const*) ; 
 int /*<<< orphan*/  NETIF_F_GSO ; 
 int /*<<< orphan*/  NETIF_F_HIGHDMA ; 
 int /*<<< orphan*/  NETIF_F_HW_CSUM ; 
 int /*<<< orphan*/  NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int /*<<< orphan*/  NETIF_F_HW_VLAN_CTAG_RX ; 
 int /*<<< orphan*/  NETIF_F_HW_VLAN_CTAG_TX ; 
 int /*<<< orphan*/  NETIF_F_IPV6_CSUM ; 
 int /*<<< orphan*/  NETIF_F_IP_CSUM ; 
 int /*<<< orphan*/  NETIF_F_LRO ; 
 int /*<<< orphan*/  NETIF_F_MULTI_QUEUE ; 
 int /*<<< orphan*/  NETIF_F_SG ; 
 int /*<<< orphan*/  NETIF_F_VLAN_CHALLENGED ; 
 char* PHY_ID_FMT ; 
 int PTR_ERR (void const*) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,TYPE_2__*) ; 
 int TEMAC_FEATURE_RX_CSUM ; 
 int TEMAC_FEATURE_TX_CSUM ; 
 int /*<<< orphan*/  XTE_OPTION_DEFAULTS ; 
 int /*<<< orphan*/  _temac_ior_be ; 
 int /*<<< orphan*/  _temac_ior_le ; 
 int /*<<< orphan*/  _temac_iow_be ; 
 int /*<<< orphan*/  _temac_iow_le ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,void const*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 struct ll_temac_platform_data* dev_get_platdata (TYPE_2__*) ; 
 void const* dev_of_node (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 struct net_device* devm_alloc_etherdev (TYPE_2__*,int) ; 
 void* devm_ioremap_nocache (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_kmalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 void const* devm_of_iomap (TYPE_2__*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* irq_of_parse_and_map (void const*,int) ; 
 struct temac_local* netdev_priv (struct net_device*) ; 
 void* of_get_mac_address (void const*) ; 
 scalar_t__ of_get_property (void const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (void const*) ; 
 void* of_parse_phandle (void const*,char*,int /*<<< orphan*/ ) ; 
 void* platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  temac_attr_group ; 
 scalar_t__ temac_dcr_setup (struct temac_local*,struct platform_device*,void const*) ; 
 void* temac_dma_in32_be ; 
 void* temac_dma_in32_le ; 
 void* temac_dma_out32_be ; 
 void* temac_dma_out32_le ; 
 int /*<<< orphan*/  temac_ethtool_ops ; 
 int /*<<< orphan*/  temac_init_mac_address (struct net_device*,void const*) ; 
 int temac_mdio_setup (struct temac_local*,struct platform_device*) ; 
 int /*<<< orphan*/  temac_mdio_teardown (struct temac_local*) ; 
 int /*<<< orphan*/  temac_netdev_ops ; 

__attribute__((used)) static int temac_probe(struct platform_device *pdev)
{
	struct ll_temac_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct device_node *temac_np = dev_of_node(&pdev->dev), *dma_np;
	struct temac_local *lp;
	struct net_device *ndev;
	struct resource *res;
	const void *addr;
	__be32 *p;
	bool little_endian;
	int rc = 0;

	/* Init network device structure */
	ndev = devm_alloc_etherdev(&pdev->dev, sizeof(*lp));
	if (!ndev)
		return -ENOMEM;

	platform_set_drvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, &pdev->dev);
	ndev->features = NETIF_F_SG;
	ndev->netdev_ops = &temac_netdev_ops;
	ndev->ethtool_ops = &temac_ethtool_ops;
#if 0
	ndev->features |= NETIF_F_IP_CSUM; /* Can checksum TCP/UDP over IPv4. */
	ndev->features |= NETIF_F_HW_CSUM; /* Can checksum all the packets. */
	ndev->features |= NETIF_F_IPV6_CSUM; /* Can checksum IPV6 TCP/UDP */
	ndev->features |= NETIF_F_HIGHDMA; /* Can DMA to high memory. */
	ndev->features |= NETIF_F_HW_VLAN_CTAG_TX; /* Transmit VLAN hw accel */
	ndev->features |= NETIF_F_HW_VLAN_CTAG_RX; /* Receive VLAN hw acceleration */
	ndev->features |= NETIF_F_HW_VLAN_CTAG_FILTER; /* Receive VLAN filtering */
	ndev->features |= NETIF_F_VLAN_CHALLENGED; /* cannot handle VLAN pkts */
	ndev->features |= NETIF_F_GSO; /* Enable software GSO. */
	ndev->features |= NETIF_F_MULTI_QUEUE; /* Has multiple TX/RX queues */
	ndev->features |= NETIF_F_LRO; /* large receive offload */
#endif

	/* setup temac private info structure */
	lp = netdev_priv(ndev);
	lp->ndev = ndev;
	lp->dev = &pdev->dev;
	lp->options = XTE_OPTION_DEFAULTS;
	spin_lock_init(&lp->rx_lock);

	/* Setup mutex for synchronization of indirect register access */
	if (pdata) {
		if (!pdata->indirect_lock) {
			dev_err(&pdev->dev,
				"indirect_lock missing in platform_data\n");
			return -EINVAL;
		}
		lp->indirect_lock = pdata->indirect_lock;
	} else {
		lp->indirect_lock = devm_kmalloc(&pdev->dev,
						 sizeof(*lp->indirect_lock),
						 GFP_KERNEL);
		spin_lock_init(lp->indirect_lock);
	}

	/* map device registers */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	lp->regs = devm_ioremap_nocache(&pdev->dev, res->start,
					resource_size(res));
	if (IS_ERR(lp->regs)) {
		dev_err(&pdev->dev, "could not map TEMAC registers\n");
		return PTR_ERR(lp->regs);
	}

	/* Select register access functions with the specified
	 * endianness mode.  Default for OF devices is big-endian.
	 */
	little_endian = false;
	if (temac_np) {
		if (of_get_property(temac_np, "little-endian", NULL))
			little_endian = true;
	} else if (pdata) {
		little_endian = pdata->reg_little_endian;
	}
	if (little_endian) {
		lp->temac_ior = _temac_ior_le;
		lp->temac_iow = _temac_iow_le;
	} else {
		lp->temac_ior = _temac_ior_be;
		lp->temac_iow = _temac_iow_be;
	}

	/* Setup checksum offload, but default to off if not specified */
	lp->temac_features = 0;
	if (temac_np) {
		p = (__be32 *)of_get_property(temac_np, "xlnx,txcsum", NULL);
		if (p && be32_to_cpu(*p))
			lp->temac_features |= TEMAC_FEATURE_TX_CSUM;
		p = (__be32 *)of_get_property(temac_np, "xlnx,rxcsum", NULL);
		if (p && be32_to_cpu(*p))
			lp->temac_features |= TEMAC_FEATURE_RX_CSUM;
	} else if (pdata) {
		if (pdata->txcsum)
			lp->temac_features |= TEMAC_FEATURE_TX_CSUM;
		if (pdata->rxcsum)
			lp->temac_features |= TEMAC_FEATURE_RX_CSUM;
	}
	if (lp->temac_features & TEMAC_FEATURE_TX_CSUM)
		/* Can checksum TCP/UDP over IPv4. */
		ndev->features |= NETIF_F_IP_CSUM;

	/* Setup LocalLink DMA */
	if (temac_np) {
		/* Find the DMA node, map the DMA registers, and
		 * decode the DMA IRQs.
		 */
		dma_np = of_parse_phandle(temac_np, "llink-connected", 0);
		if (!dma_np) {
			dev_err(&pdev->dev, "could not find DMA node\n");
			return -ENODEV;
		}

		/* Setup the DMA register accesses, could be DCR or
		 * memory mapped.
		 */
		if (temac_dcr_setup(lp, pdev, dma_np)) {
			/* no DCR in the device tree, try non-DCR */
			lp->sdma_regs = devm_of_iomap(&pdev->dev, dma_np, 0,
						      NULL);
			if (IS_ERR(lp->sdma_regs)) {
				dev_err(&pdev->dev,
					"unable to map DMA registers\n");
				of_node_put(dma_np);
				return PTR_ERR(lp->sdma_regs);
			}
			if (of_get_property(dma_np, "little-endian", NULL)) {
				lp->dma_in = temac_dma_in32_le;
				lp->dma_out = temac_dma_out32_le;
			} else {
				lp->dma_in = temac_dma_in32_be;
				lp->dma_out = temac_dma_out32_be;
			}
			dev_dbg(&pdev->dev, "MEM base: %p\n", lp->sdma_regs);
		}

		/* Get DMA RX and TX interrupts */
		lp->rx_irq = irq_of_parse_and_map(dma_np, 0);
		lp->tx_irq = irq_of_parse_and_map(dma_np, 1);

		/* Use defaults for IRQ delay/coalescing setup.  These
		 * are configuration values, so does not belong in
		 * device-tree.
		 */
		lp->tx_chnl_ctrl = 0x10220000;
		lp->rx_chnl_ctrl = 0xff070000;

		/* Finished with the DMA node; drop the reference */
		of_node_put(dma_np);
	} else if (pdata) {
		/* 2nd memory resource specifies DMA registers */
		res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
		lp->sdma_regs = devm_ioremap_nocache(&pdev->dev, res->start,
						     resource_size(res));
		if (IS_ERR(lp->sdma_regs)) {
			dev_err(&pdev->dev,
				"could not map DMA registers\n");
			return PTR_ERR(lp->sdma_regs);
		}
		if (pdata->dma_little_endian) {
			lp->dma_in = temac_dma_in32_le;
			lp->dma_out = temac_dma_out32_le;
		} else {
			lp->dma_in = temac_dma_in32_be;
			lp->dma_out = temac_dma_out32_be;
		}

		/* Get DMA RX and TX interrupts */
		lp->rx_irq = platform_get_irq(pdev, 0);
		lp->tx_irq = platform_get_irq(pdev, 1);

		/* IRQ delay/coalescing setup */
		if (pdata->tx_irq_timeout || pdata->tx_irq_count)
			lp->tx_chnl_ctrl = (pdata->tx_irq_timeout << 24) |
				(pdata->tx_irq_count << 16);
		else
			lp->tx_chnl_ctrl = 0x10220000;
		if (pdata->rx_irq_timeout || pdata->rx_irq_count)
			lp->rx_chnl_ctrl = (pdata->rx_irq_timeout << 24) |
				(pdata->rx_irq_count << 16);
		else
			lp->rx_chnl_ctrl = 0xff070000;
	}

	/* Error handle returned DMA RX and TX interrupts */
	if (lp->rx_irq < 0) {
		if (lp->rx_irq != -EPROBE_DEFER)
			dev_err(&pdev->dev, "could not get DMA RX irq\n");
		return lp->rx_irq;
	}
	if (lp->tx_irq < 0) {
		if (lp->tx_irq != -EPROBE_DEFER)
			dev_err(&pdev->dev, "could not get DMA TX irq\n");
		return lp->tx_irq;
	}

	if (temac_np) {
		/* Retrieve the MAC address */
		addr = of_get_mac_address(temac_np);
		if (IS_ERR(addr)) {
			dev_err(&pdev->dev, "could not find MAC address\n");
			return -ENODEV;
		}
		temac_init_mac_address(ndev, addr);
	} else if (pdata) {
		temac_init_mac_address(ndev, pdata->mac_addr);
	}

	rc = temac_mdio_setup(lp, pdev);
	if (rc)
		dev_warn(&pdev->dev, "error registering MDIO bus\n");

	if (temac_np) {
		lp->phy_node = of_parse_phandle(temac_np, "phy-handle", 0);
		if (lp->phy_node)
			dev_dbg(lp->dev, "using PHY node %pOF\n", temac_np);
	} else if (pdata) {
		snprintf(lp->phy_name, sizeof(lp->phy_name),
			 PHY_ID_FMT, lp->mii_bus->id, pdata->phy_addr);
		lp->phy_interface = pdata->phy_interface;
	}

	/* Add the device attributes */
	rc = sysfs_create_group(&lp->dev->kobj, &temac_attr_group);
	if (rc) {
		dev_err(lp->dev, "Error creating sysfs files\n");
		goto err_sysfs_create;
	}

	rc = register_netdev(lp->ndev);
	if (rc) {
		dev_err(lp->dev, "register_netdev() error (%i)\n", rc);
		goto err_register_ndev;
	}

	return 0;

err_register_ndev:
	sysfs_remove_group(&lp->dev->kobj, &temac_attr_group);
err_sysfs_create:
	if (lp->phy_node)
		of_node_put(lp->phy_node);
	temac_mdio_teardown(lp);
	return rc;
}