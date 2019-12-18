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
struct net_device {int /*<<< orphan*/  phydev; int /*<<< orphan*/  name; } ;
struct bgmac {int /*<<< orphan*/  napi; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  bgmac_chip_init (struct bgmac*) ; 
 int /*<<< orphan*/  bgmac_chip_reset (struct bgmac*) ; 
 int /*<<< orphan*/  bgmac_dma_cleanup (struct bgmac*) ; 
 int bgmac_dma_init (struct bgmac*) ; 
 int /*<<< orphan*/  bgmac_interrupt ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct bgmac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int bgmac_open(struct net_device *net_dev)
{
	struct bgmac *bgmac = netdev_priv(net_dev);
	int err = 0;

	bgmac_chip_reset(bgmac);

	err = bgmac_dma_init(bgmac);
	if (err)
		return err;

	/* Specs say about reclaiming rings here, but we do that in DMA init */
	bgmac_chip_init(bgmac);

	err = request_irq(bgmac->irq, bgmac_interrupt, IRQF_SHARED,
			  net_dev->name, net_dev);
	if (err < 0) {
		dev_err(bgmac->dev, "IRQ request error: %d!\n", err);
		bgmac_dma_cleanup(bgmac);
		return err;
	}
	napi_enable(&bgmac->napi);

	phy_start(net_dev->phydev);

	netif_start_queue(net_dev);

	return 0;
}