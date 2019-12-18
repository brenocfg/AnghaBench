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
struct spider_net_card {int /*<<< orphan*/  rx_chain; int /*<<< orphan*/  tx_chain; int /*<<< orphan*/  aneg_timer; int /*<<< orphan*/  tx_timer; int /*<<< orphan*/  napi; } ;
struct net_device {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPIDER_NET_DMA_TX_FEND_VALUE ; 
 int /*<<< orphan*/  SPIDER_NET_GDTDMACCNTR ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct spider_net_card* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spider_net_disable_interrupts (struct spider_net_card*) ; 
 int /*<<< orphan*/  spider_net_disable_rxdmac (struct spider_net_card*) ; 
 int /*<<< orphan*/  spider_net_free_chain (struct spider_net_card*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spider_net_free_rx_chain_contents (struct spider_net_card*) ; 
 int /*<<< orphan*/  spider_net_release_tx_chain (struct spider_net_card*,int) ; 
 int /*<<< orphan*/  spider_net_write_reg (struct spider_net_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
spider_net_stop(struct net_device *netdev)
{
	struct spider_net_card *card = netdev_priv(netdev);

	napi_disable(&card->napi);
	netif_carrier_off(netdev);
	netif_stop_queue(netdev);
	del_timer_sync(&card->tx_timer);
	del_timer_sync(&card->aneg_timer);

	spider_net_disable_interrupts(card);

	free_irq(netdev->irq, netdev);

	spider_net_write_reg(card, SPIDER_NET_GDTDMACCNTR,
			     SPIDER_NET_DMA_TX_FEND_VALUE);

	/* turn off DMA, force end */
	spider_net_disable_rxdmac(card);

	/* release chains */
	spider_net_release_tx_chain(card, 1);
	spider_net_free_rx_chain_contents(card);

	spider_net_free_chain(card, &card->tx_chain);
	spider_net_free_chain(card, &card->rx_chain);

	return 0;
}