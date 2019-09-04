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
struct slic_rx_queue {unsigned int len; struct slic_rx_buffer* rxbuffs; } ;
struct slic_rx_buffer {int /*<<< orphan*/  skb; } ;
struct slic_device {TYPE_1__* pdev; struct slic_rx_queue rxq; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  consume_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct slic_rx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (struct slic_rx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct slic_rx_buffer*) ; 
 int /*<<< orphan*/  map_addr ; 
 int /*<<< orphan*/  map_len ; 

__attribute__((used)) static void slic_free_rx_queue(struct slic_device *sdev)
{
	struct slic_rx_queue *rxq = &sdev->rxq;
	struct slic_rx_buffer *buff;
	unsigned int i;

	/* free rx buffers */
	for (i = 0; i < rxq->len; i++) {
		buff = &rxq->rxbuffs[i];

		if (!buff->skb)
			continue;

		dma_unmap_single(&sdev->pdev->dev,
				 dma_unmap_addr(buff, map_addr),
				 dma_unmap_len(buff, map_len),
				 DMA_FROM_DEVICE);
		consume_skb(buff->skb);
	}
	kfree(rxq->rxbuffs);
}