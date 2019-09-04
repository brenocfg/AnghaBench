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
struct net_device {int /*<<< orphan*/  phydev; } ;
struct bgmac {int /*<<< orphan*/  irq; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  bgmac_chip_intrs_off (struct bgmac*) ; 
 int /*<<< orphan*/  bgmac_chip_reset (struct bgmac*) ; 
 int /*<<< orphan*/  bgmac_dma_cleanup (struct bgmac*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct bgmac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bgmac_stop(struct net_device *net_dev)
{
	struct bgmac *bgmac = netdev_priv(net_dev);

	netif_carrier_off(net_dev);

	phy_stop(net_dev->phydev);

	napi_disable(&bgmac->napi);
	bgmac_chip_intrs_off(bgmac);
	free_irq(bgmac->irq, net_dev);

	bgmac_chip_reset(bgmac);
	bgmac_dma_cleanup(bgmac);

	return 0;
}