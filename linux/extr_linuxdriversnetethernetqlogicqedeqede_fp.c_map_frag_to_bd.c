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
struct qede_tx_queue {int /*<<< orphan*/  dev; } ;
struct eth_tx_bd {int dummy; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BD_SET_UNMAP_ADDR_LEN (struct eth_tx_bd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_dma_map (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_size (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int map_frag_to_bd(struct qede_tx_queue *txq,
			  skb_frag_t *frag, struct eth_tx_bd *bd)
{
	dma_addr_t mapping;

	/* Map skb non-linear frag data for DMA */
	mapping = skb_frag_dma_map(txq->dev, frag, 0,
				   skb_frag_size(frag), DMA_TO_DEVICE);
	if (unlikely(dma_mapping_error(txq->dev, mapping)))
		return -ENOMEM;

	/* Setup the data pointer of the frag data */
	BD_SET_UNMAP_ADDR_LEN(bd, mapping, skb_frag_size(frag));

	return 0;
}