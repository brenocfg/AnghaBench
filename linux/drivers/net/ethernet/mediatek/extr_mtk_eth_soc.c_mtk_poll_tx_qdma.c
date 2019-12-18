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
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ len; } ;
struct mtk_tx_ring {int /*<<< orphan*/  free_count; struct mtk_tx_dma* last_free; } ;
struct mtk_tx_dma {scalar_t__ txd2; int txd3; } ;
struct mtk_tx_buf {int flags; struct sk_buff* skb; } ;
struct mtk_eth {struct mtk_tx_ring tx_ring; } ;

/* Variables and functions */
 scalar_t__ MTK_DMA_DUMMY_DESC ; 
 int /*<<< orphan*/  MTK_QTX_CRX_PTR ; 
 int /*<<< orphan*/  MTK_QTX_DRX_PTR ; 
 int MTK_TX_FLAGS_FPORT1 ; 
 int TX_DMA_OWNER_CPU ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct mtk_tx_buf* mtk_desc_to_tx_buf (struct mtk_tx_ring*,struct mtk_tx_dma*) ; 
 struct mtk_tx_dma* mtk_qdma_phys_to_virt (struct mtk_tx_ring*,scalar_t__) ; 
 scalar_t__ mtk_r32 (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_tx_unmap (struct mtk_eth*,struct mtk_tx_buf*) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_poll_tx_qdma(struct mtk_eth *eth, int budget,
			    unsigned int *done, unsigned int *bytes)
{
	struct mtk_tx_ring *ring = &eth->tx_ring;
	struct mtk_tx_dma *desc;
	struct sk_buff *skb;
	struct mtk_tx_buf *tx_buf;
	u32 cpu, dma;

	cpu = mtk_r32(eth, MTK_QTX_CRX_PTR);
	dma = mtk_r32(eth, MTK_QTX_DRX_PTR);

	desc = mtk_qdma_phys_to_virt(ring, cpu);

	while ((cpu != dma) && budget) {
		u32 next_cpu = desc->txd2;
		int mac = 0;

		desc = mtk_qdma_phys_to_virt(ring, desc->txd2);
		if ((desc->txd3 & TX_DMA_OWNER_CPU) == 0)
			break;

		tx_buf = mtk_desc_to_tx_buf(ring, desc);
		if (tx_buf->flags & MTK_TX_FLAGS_FPORT1)
			mac = 1;

		skb = tx_buf->skb;
		if (!skb)
			break;

		if (skb != (struct sk_buff *)MTK_DMA_DUMMY_DESC) {
			bytes[mac] += skb->len;
			done[mac]++;
			budget--;
		}
		mtk_tx_unmap(eth, tx_buf);

		ring->last_free = desc;
		atomic_inc(&ring->free_count);

		cpu = next_cpu;
	}

	mtk_w32(eth, cpu, MTK_QTX_CRX_PTR);

	return budget;
}