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
struct arc_emac_priv {struct buffer_state* rx_buff; struct arc_emac_bd* rxbd; } ;
struct arc_emac_bd {scalar_t__ data; scalar_t__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 unsigned int RX_BD_NUM ; 
 int /*<<< orphan*/  addr ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct buffer_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (struct buffer_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  len ; 
 struct arc_emac_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void arc_free_rx_queue(struct net_device *ndev)
{
	struct arc_emac_priv *priv = netdev_priv(ndev);
	unsigned int i;

	for (i = 0; i < RX_BD_NUM; i++) {
		struct arc_emac_bd *rxbd = &priv->rxbd[i];
		struct buffer_state *rx_buff = &priv->rx_buff[i];

		if (rx_buff->skb) {
			dma_unmap_single(&ndev->dev,
					 dma_unmap_addr(rx_buff, addr),
					 dma_unmap_len(rx_buff, len),
					 DMA_FROM_DEVICE);

			/* return the sk_buff to system */
			dev_kfree_skb_irq(rx_buff->skb);
		}

		rxbd->info = 0;
		rxbd->data = 0;
		rx_buff->skb = NULL;
	}
}