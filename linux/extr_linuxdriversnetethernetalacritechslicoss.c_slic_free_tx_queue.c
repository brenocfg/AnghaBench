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
struct slic_tx_queue {unsigned int len; struct slic_tx_buffer* txbuffs; int /*<<< orphan*/  dma_pool; } ;
struct slic_tx_buffer {int /*<<< orphan*/  skb; int /*<<< orphan*/  desc_paddr; int /*<<< orphan*/  desc; } ;
struct slic_device {TYPE_1__* pdev; struct slic_tx_queue txq; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  consume_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct slic_tx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (struct slic_tx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct slic_tx_buffer*) ; 
 int /*<<< orphan*/  map_addr ; 
 int /*<<< orphan*/  map_len ; 

__attribute__((used)) static void slic_free_tx_queue(struct slic_device *sdev)
{
	struct slic_tx_queue *txq = &sdev->txq;
	struct slic_tx_buffer *buff;
	unsigned int i;

	for (i = 0; i < txq->len; i++) {
		buff = &txq->txbuffs[i];
		dma_pool_free(txq->dma_pool, buff->desc, buff->desc_paddr);
		if (!buff->skb)
			continue;

		dma_unmap_single(&sdev->pdev->dev,
				 dma_unmap_addr(buff, map_addr),
				 dma_unmap_len(buff, map_len), DMA_TO_DEVICE);
		consume_skb(buff->skb);
	}
	dma_pool_destroy(txq->dma_pool);

	kfree(txq->txbuffs);
}