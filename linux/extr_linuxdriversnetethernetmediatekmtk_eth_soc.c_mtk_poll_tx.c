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
struct mtk_tx_ring {scalar_t__ thresh; int /*<<< orphan*/  free_count; struct mtk_tx_dma* last_free; } ;
struct mtk_tx_dma {scalar_t__ txd2; int txd3; } ;
struct mtk_tx_buf {int flags; struct sk_buff* skb; } ;
struct mtk_eth {int /*<<< orphan*/ * netdev; struct mtk_tx_ring tx_ring; } ;
typedef  int /*<<< orphan*/  done ;
typedef  int /*<<< orphan*/  bytes ;

/* Variables and functions */
 scalar_t__ MTK_DMA_DUMMY_DESC ; 
 int MTK_MAC_COUNT ; 
 int MTK_MAX_DEVS ; 
 int /*<<< orphan*/  MTK_QTX_CRX_PTR ; 
 int /*<<< orphan*/  MTK_QTX_DRX_PTR ; 
 int MTK_TX_FLAGS_FPORT1 ; 
 int TX_DMA_OWNER_CPU ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,int) ; 
 struct mtk_tx_buf* mtk_desc_to_tx_buf (struct mtk_tx_ring*,struct mtk_tx_dma*) ; 
 struct mtk_tx_dma* mtk_qdma_phys_to_virt (struct mtk_tx_ring*,scalar_t__) ; 
 scalar_t__ mtk_queue_stopped (struct mtk_eth*) ; 
 scalar_t__ mtk_r32 (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_tx_unmap (struct mtk_eth*,struct mtk_tx_buf*) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_wake_queue (struct mtk_eth*) ; 
 int /*<<< orphan*/  netdev_completed_queue (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int mtk_poll_tx(struct mtk_eth *eth, int budget)
{
	struct mtk_tx_ring *ring = &eth->tx_ring;
	struct mtk_tx_dma *desc;
	struct sk_buff *skb;
	struct mtk_tx_buf *tx_buf;
	unsigned int done[MTK_MAX_DEVS];
	unsigned int bytes[MTK_MAX_DEVS];
	u32 cpu, dma;
	int total = 0, i;

	memset(done, 0, sizeof(done));
	memset(bytes, 0, sizeof(bytes));

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

	for (i = 0; i < MTK_MAC_COUNT; i++) {
		if (!eth->netdev[i] || !done[i])
			continue;
		netdev_completed_queue(eth->netdev[i], done[i], bytes[i]);
		total += done[i];
	}

	if (mtk_queue_stopped(eth) &&
	    (atomic_read(&ring->free_count) > ring->thresh))
		mtk_wake_queue(eth);

	return total;
}