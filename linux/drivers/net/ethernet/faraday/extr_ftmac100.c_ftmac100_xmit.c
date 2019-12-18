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
struct sk_buff {unsigned int len; } ;
struct net_device {int dummy; } ;
struct ftmac100_txdes {int dummy; } ;
struct ftmac100 {scalar_t__ tx_pending; int /*<<< orphan*/  tx_lock; struct net_device* netdev; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned int ETH_ZLEN ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ TX_QUEUE_ENTRIES ; 
 struct ftmac100_txdes* ftmac100_current_txdes (struct ftmac100*) ; 
 int /*<<< orphan*/  ftmac100_tx_pointer_advance (struct ftmac100*) ; 
 int /*<<< orphan*/  ftmac100_txdes_set_buffer_size (struct ftmac100_txdes*,unsigned int) ; 
 int /*<<< orphan*/  ftmac100_txdes_set_dma_addr (struct ftmac100_txdes*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftmac100_txdes_set_dma_own (struct ftmac100_txdes*) ; 
 int /*<<< orphan*/  ftmac100_txdes_set_first_segment (struct ftmac100_txdes*) ; 
 int /*<<< orphan*/  ftmac100_txdes_set_last_segment (struct ftmac100_txdes*) ; 
 int /*<<< orphan*/  ftmac100_txdes_set_skb (struct ftmac100_txdes*,struct sk_buff*) ; 
 int /*<<< orphan*/  ftmac100_txdes_set_txint (struct ftmac100_txdes*) ; 
 int /*<<< orphan*/  ftmac100_txdma_start_polling (struct ftmac100*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static netdev_tx_t ftmac100_xmit(struct ftmac100 *priv, struct sk_buff *skb,
				 dma_addr_t map)
{
	struct net_device *netdev = priv->netdev;
	struct ftmac100_txdes *txdes;
	unsigned int len = (skb->len < ETH_ZLEN) ? ETH_ZLEN : skb->len;

	txdes = ftmac100_current_txdes(priv);
	ftmac100_tx_pointer_advance(priv);

	/* setup TX descriptor */
	ftmac100_txdes_set_skb(txdes, skb);
	ftmac100_txdes_set_dma_addr(txdes, map);

	ftmac100_txdes_set_first_segment(txdes);
	ftmac100_txdes_set_last_segment(txdes);
	ftmac100_txdes_set_txint(txdes);
	ftmac100_txdes_set_buffer_size(txdes, len);

	spin_lock(&priv->tx_lock);
	priv->tx_pending++;
	if (priv->tx_pending == TX_QUEUE_ENTRIES)
		netif_stop_queue(netdev);

	/* start transmit */
	ftmac100_txdes_set_dma_own(txdes);
	spin_unlock(&priv->tx_lock);

	ftmac100_txdma_start_polling(priv);
	return NETDEV_TX_OK;
}