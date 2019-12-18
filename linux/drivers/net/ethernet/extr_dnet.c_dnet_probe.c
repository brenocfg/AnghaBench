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
struct resource {scalar_t__ start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct phy_device {int dummy; } ;
struct net_device {unsigned int irq; unsigned long base_addr; struct phy_device* phydev; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  features; } ;
struct dnet {int capabilities; scalar_t__ regs; int /*<<< orphan*/  napi; int /*<<< orphan*/  lock; struct net_device* dev; } ;

/* Variables and functions */
 int DNET_CAPS_MASK ; 
 int DNET_HAS_DMA ; 
 int DNET_HAS_GIGABIT ; 
 int DNET_HAS_IRQ ; 
 int DNET_HAS_MDIO ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERCAPS ; 
 int /*<<< orphan*/  __dnet_set_hwaddr (struct dnet*) ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  dnet_ethtool_ops ; 
 int /*<<< orphan*/  dnet_get_hwaddr (struct dnet*) ; 
 int /*<<< orphan*/  dnet_interrupt ; 
 int dnet_mii_init (struct dnet*) ; 
 int /*<<< orphan*/  dnet_netdev_ops ; 
 int /*<<< orphan*/  dnet_phy_marvell_fixup ; 
 int /*<<< orphan*/  dnet_poll ; 
 int dnet_readl (struct dnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  free_irq (unsigned int,struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 struct dnet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phy_attached_info (struct phy_device*) ; 
 int phy_register_fixup_for_uid (int,int,int /*<<< orphan*/ ) ; 
 unsigned int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int register_netdev (struct net_device*) ; 
 int request_irq (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int dnet_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct net_device *dev;
	struct dnet *bp;
	struct phy_device *phydev;
	int err;
	unsigned int irq;

	irq = platform_get_irq(pdev, 0);

	dev = alloc_etherdev(sizeof(*bp));
	if (!dev)
		return -ENOMEM;

	/* TODO: Actually, we have some interesting features... */
	dev->features |= 0;

	bp = netdev_priv(dev);
	bp->dev = dev;

	platform_set_drvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	spin_lock_init(&bp->lock);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	bp->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(bp->regs)) {
		err = PTR_ERR(bp->regs);
		goto err_out_free_dev;
	}

	dev->irq = irq;
	err = request_irq(dev->irq, dnet_interrupt, 0, DRV_NAME, dev);
	if (err) {
		dev_err(&pdev->dev, "Unable to request IRQ %d (error %d)\n",
		       irq, err);
		goto err_out_free_dev;
	}

	dev->netdev_ops = &dnet_netdev_ops;
	netif_napi_add(dev, &bp->napi, dnet_poll, 64);
	dev->ethtool_ops = &dnet_ethtool_ops;

	dev->base_addr = (unsigned long)bp->regs;

	bp->capabilities = dnet_readl(bp, VERCAPS) & DNET_CAPS_MASK;

	dnet_get_hwaddr(bp);

	if (!is_valid_ether_addr(dev->dev_addr)) {
		/* choose a random ethernet address */
		eth_hw_addr_random(dev);
		__dnet_set_hwaddr(bp);
	}

	err = register_netdev(dev);
	if (err) {
		dev_err(&pdev->dev, "Cannot register net device, aborting.\n");
		goto err_out_free_irq;
	}

	/* register the PHY board fixup (for Marvell 88E1111) */
	err = phy_register_fixup_for_uid(0x01410cc0, 0xfffffff0,
					 dnet_phy_marvell_fixup);
	/* we can live without it, so just issue a warning */
	if (err)
		dev_warn(&pdev->dev, "Cannot register PHY board fixup.\n");

	err = dnet_mii_init(bp);
	if (err)
		goto err_out_unregister_netdev;

	dev_info(&pdev->dev, "Dave DNET at 0x%p (0x%08x) irq %d %pM\n",
	       bp->regs, (unsigned int)res->start, dev->irq, dev->dev_addr);
	dev_info(&pdev->dev, "has %smdio, %sirq, %sgigabit, %sdma\n",
	       (bp->capabilities & DNET_HAS_MDIO) ? "" : "no ",
	       (bp->capabilities & DNET_HAS_IRQ) ? "" : "no ",
	       (bp->capabilities & DNET_HAS_GIGABIT) ? "" : "no ",
	       (bp->capabilities & DNET_HAS_DMA) ? "" : "no ");
	phydev = dev->phydev;
	phy_attached_info(phydev);

	return 0;

err_out_unregister_netdev:
	unregister_netdev(dev);
err_out_free_irq:
	free_irq(dev->irq, dev);
err_out_free_dev:
	free_netdev(dev);
	return err;
}