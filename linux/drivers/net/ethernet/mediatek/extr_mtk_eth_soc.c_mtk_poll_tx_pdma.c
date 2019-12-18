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
typedef  size_t u32 ;
struct sk_buff {scalar_t__ len; } ;
struct mtk_tx_ring {size_t cpu_idx; int /*<<< orphan*/  dma_size; int /*<<< orphan*/  free_count; struct mtk_tx_dma* last_free; struct mtk_tx_dma* dma; struct mtk_tx_buf* buf; } ;
struct mtk_tx_dma {int dummy; } ;
struct mtk_tx_buf {struct sk_buff* skb; } ;
struct mtk_eth {struct mtk_tx_ring tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT7628_TX_DTX_IDX0 ; 
 scalar_t__ MTK_DMA_DUMMY_DESC ; 
 size_t NEXT_DESP_IDX (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 size_t mtk_r32 (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_tx_unmap (struct mtk_eth*,struct mtk_tx_buf*) ; 

__attribute__((used)) static int mtk_poll_tx_pdma(struct mtk_eth *eth, int budget,
			    unsigned int *done, unsigned int *bytes)
{
	struct mtk_tx_ring *ring = &eth->tx_ring;
	struct mtk_tx_dma *desc;
	struct sk_buff *skb;
	struct mtk_tx_buf *tx_buf;
	u32 cpu, dma;

	cpu = ring->cpu_idx;
	dma = mtk_r32(eth, MT7628_TX_DTX_IDX0);

	while ((cpu != dma) && budget) {
		tx_buf = &ring->buf[cpu];
		skb = tx_buf->skb;
		if (!skb)
			break;

		if (skb != (struct sk_buff *)MTK_DMA_DUMMY_DESC) {
			bytes[0] += skb->len;
			done[0]++;
			budget--;
		}

		mtk_tx_unmap(eth, tx_buf);

		desc = &ring->dma[cpu];
		ring->last_free = desc;
		atomic_inc(&ring->free_count);

		cpu = NEXT_DESP_IDX(cpu, ring->dma_size);
	}

	ring->cpu_idx = cpu;

	return budget;
}