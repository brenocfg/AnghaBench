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
struct net_device {int /*<<< orphan*/  dev; } ;
struct buffer_state {int /*<<< orphan*/ * skb; } ;
struct arc_emac_priv {struct buffer_state* tx_buff; struct arc_emac_bd* txbd; } ;
struct arc_emac_bd {scalar_t__ data; scalar_t__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 unsigned int TX_BD_NUM ; 
 int /*<<< orphan*/  addr ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct buffer_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (struct buffer_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  len ; 
 struct arc_emac_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void arc_free_tx_queue(struct net_device *ndev)
{
	struct arc_emac_priv *priv = netdev_priv(ndev);
	unsigned int i;

	for (i = 0; i < TX_BD_NUM; i++) {
		struct arc_emac_bd *txbd = &priv->txbd[i];
		struct buffer_state *tx_buff = &priv->tx_buff[i];

		if (tx_buff->skb) {
			dma_unmap_single(&ndev->dev,
					 dma_unmap_addr(tx_buff, addr),
					 dma_unmap_len(tx_buff, len),
					 DMA_TO_DEVICE);

			/* return the sk_buff to system */
			dev_kfree_skb_irq(tx_buff->skb);
		}

		txbd->info = 0;
		txbd->data = 0;
		tx_buff->skb = NULL;
	}
}