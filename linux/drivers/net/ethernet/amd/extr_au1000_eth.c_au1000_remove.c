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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct au1000_private {int /*<<< orphan*/  enable; int /*<<< orphan*/  mac; int /*<<< orphan*/  macdma; int /*<<< orphan*/  dma_addr; scalar_t__ vaddr; scalar_t__* tx_db_inuse; scalar_t__* rx_db_inuse; int /*<<< orphan*/  mii_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_NON_CONSISTENT ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int MAX_BUF_SIZE ; 
 int NUM_RX_BUFFS ; 
 int NUM_RX_DMA ; 
 int NUM_TX_BUFFS ; 
 int NUM_TX_DMA ; 
 int /*<<< orphan*/  au1000_ReleaseDB (struct au1000_private*,scalar_t__) ; 
 int /*<<< orphan*/  dma_free_attrs (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 struct au1000_private* netdev_priv (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int au1000_remove(struct platform_device *pdev)
{
	struct net_device *dev = platform_get_drvdata(pdev);
	struct au1000_private *aup = netdev_priv(dev);
	int i;
	struct resource *base, *macen;

	unregister_netdev(dev);
	mdiobus_unregister(aup->mii_bus);
	mdiobus_free(aup->mii_bus);

	for (i = 0; i < NUM_RX_DMA; i++)
		if (aup->rx_db_inuse[i])
			au1000_ReleaseDB(aup, aup->rx_db_inuse[i]);

	for (i = 0; i < NUM_TX_DMA; i++)
		if (aup->tx_db_inuse[i])
			au1000_ReleaseDB(aup, aup->tx_db_inuse[i]);

	dma_free_attrs(&pdev->dev, MAX_BUF_SIZE * (NUM_TX_BUFFS + NUM_RX_BUFFS),
			(void *)aup->vaddr, aup->dma_addr,
			DMA_ATTR_NON_CONSISTENT);

	iounmap(aup->macdma);
	iounmap(aup->mac);
	iounmap(aup->enable);

	base = platform_get_resource(pdev, IORESOURCE_MEM, 2);
	release_mem_region(base->start, resource_size(base));

	base = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(base->start, resource_size(base));

	macen = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	release_mem_region(macen->start, resource_size(macen));

	free_netdev(dev);

	return 0;
}