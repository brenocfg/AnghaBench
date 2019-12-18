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
struct ravb_tx_desc {int dummy; } ;
struct ravb_private {int num_tx_desc; int* num_rx_ring; int* num_tx_ring; int /*<<< orphan*/ ** tx_skb; int /*<<< orphan*/ ** tx_align; int /*<<< orphan*/ ** rx_skb; struct ravb_ex_rx_desc** tx_ring; int /*<<< orphan*/ * tx_desc_dma; struct ravb_ex_rx_desc** rx_ring; int /*<<< orphan*/ * rx_desc_dma; int /*<<< orphan*/  rx_buf_sz; } ;
struct ravb_ex_rx_desc {int /*<<< orphan*/  dptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,struct ravb_ex_rx_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ravb_tx_free (struct net_device*,int,int) ; 

__attribute__((used)) static void ravb_ring_free(struct net_device *ndev, int q)
{
	struct ravb_private *priv = netdev_priv(ndev);
	int num_tx_desc = priv->num_tx_desc;
	int ring_size;
	int i;

	if (priv->rx_ring[q]) {
		for (i = 0; i < priv->num_rx_ring[q]; i++) {
			struct ravb_ex_rx_desc *desc = &priv->rx_ring[q][i];

			if (!dma_mapping_error(ndev->dev.parent,
					       le32_to_cpu(desc->dptr)))
				dma_unmap_single(ndev->dev.parent,
						 le32_to_cpu(desc->dptr),
						 priv->rx_buf_sz,
						 DMA_FROM_DEVICE);
		}
		ring_size = sizeof(struct ravb_ex_rx_desc) *
			    (priv->num_rx_ring[q] + 1);
		dma_free_coherent(ndev->dev.parent, ring_size, priv->rx_ring[q],
				  priv->rx_desc_dma[q]);
		priv->rx_ring[q] = NULL;
	}

	if (priv->tx_ring[q]) {
		ravb_tx_free(ndev, q, false);

		ring_size = sizeof(struct ravb_tx_desc) *
			    (priv->num_tx_ring[q] * num_tx_desc + 1);
		dma_free_coherent(ndev->dev.parent, ring_size, priv->tx_ring[q],
				  priv->tx_desc_dma[q]);
		priv->tx_ring[q] = NULL;
	}

	/* Free RX skb ringbuffer */
	if (priv->rx_skb[q]) {
		for (i = 0; i < priv->num_rx_ring[q]; i++)
			dev_kfree_skb(priv->rx_skb[q][i]);
	}
	kfree(priv->rx_skb[q]);
	priv->rx_skb[q] = NULL;

	/* Free aligned TX buffers */
	kfree(priv->tx_align[q]);
	priv->tx_align[q] = NULL;

	/* Free TX skb ringbuffer.
	 * SKBs are freed by ravb_tx_free() call above.
	 */
	kfree(priv->tx_skb[q]);
	priv->tx_skb[q] = NULL;
}