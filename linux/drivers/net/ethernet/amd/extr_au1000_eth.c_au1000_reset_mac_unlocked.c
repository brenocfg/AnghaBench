#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct au1000_private {scalar_t__ mac_enabled; TYPE_2__** tx_dma_ring; TYPE_1__** rx_dma_ring; scalar_t__ tx_full; int /*<<< orphan*/  enable; } ;
struct TYPE_4__ {int buff_stat; } ;
struct TYPE_3__ {int buff_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_EN_CLOCK_ENABLE ; 
 int NUM_RX_DMA ; 
 int NUM_TX_DMA ; 
 int /*<<< orphan*/  au1000_hard_stop (struct net_device*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct au1000_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void au1000_reset_mac_unlocked(struct net_device *dev)
{
	struct au1000_private *const aup = netdev_priv(dev);
	int i;

	au1000_hard_stop(dev);

	writel(MAC_EN_CLOCK_ENABLE, aup->enable);
	wmb(); /* drain writebuffer */
	mdelay(2);
	writel(0, aup->enable);
	wmb(); /* drain writebuffer */
	mdelay(2);

	aup->tx_full = 0;
	for (i = 0; i < NUM_RX_DMA; i++) {
		/* reset control bits */
		aup->rx_dma_ring[i]->buff_stat &= ~0xf;
	}
	for (i = 0; i < NUM_TX_DMA; i++) {
		/* reset control bits */
		aup->tx_dma_ring[i]->buff_stat &= ~0xf;
	}

	aup->mac_enabled = 0;

}