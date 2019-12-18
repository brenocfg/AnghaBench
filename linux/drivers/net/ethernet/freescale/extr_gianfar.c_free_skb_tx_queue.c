#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct txbd8 {int /*<<< orphan*/  length; int /*<<< orphan*/  bufPtr; scalar_t__ lstatus; } ;
struct gfar_private {int /*<<< orphan*/  dev; } ;
struct gfar_priv_tx_q {int tx_ring_size; int /*<<< orphan*/ ** tx_skbuff; struct txbd8* tx_bd_base; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int nr_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ **) ; 
 struct gfar_private* netdev_priv (int /*<<< orphan*/ ) ; 
 TYPE_1__* skb_shinfo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_skb_tx_queue(struct gfar_priv_tx_q *tx_queue)
{
	struct txbd8 *txbdp;
	struct gfar_private *priv = netdev_priv(tx_queue->dev);
	int i, j;

	txbdp = tx_queue->tx_bd_base;

	for (i = 0; i < tx_queue->tx_ring_size; i++) {
		if (!tx_queue->tx_skbuff[i])
			continue;

		dma_unmap_single(priv->dev, be32_to_cpu(txbdp->bufPtr),
				 be16_to_cpu(txbdp->length), DMA_TO_DEVICE);
		txbdp->lstatus = 0;
		for (j = 0; j < skb_shinfo(tx_queue->tx_skbuff[i])->nr_frags;
		     j++) {
			txbdp++;
			dma_unmap_page(priv->dev, be32_to_cpu(txbdp->bufPtr),
				       be16_to_cpu(txbdp->length),
				       DMA_TO_DEVICE);
		}
		txbdp++;
		dev_kfree_skb_any(tx_queue->tx_skbuff[i]);
		tx_queue->tx_skbuff[i] = NULL;
	}
	kfree(tx_queue->tx_skbuff);
	tx_queue->tx_skbuff = NULL;
}