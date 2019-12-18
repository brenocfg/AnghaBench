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
struct mtk_tx_dma {int dummy; } ;
struct mtk_eth {int phy_scratch_ring; TYPE_1__* scratch_ring; int /*<<< orphan*/  dev; int /*<<< orphan*/  scratch_head; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {int txd1; int /*<<< orphan*/  txd3; scalar_t__ txd2; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MTK_DMA_SIZE ; 
 int /*<<< orphan*/  MTK_QDMA_FQ_BLEN ; 
 int /*<<< orphan*/  MTK_QDMA_FQ_CNT ; 
 int /*<<< orphan*/  MTK_QDMA_FQ_HEAD ; 
 int /*<<< orphan*/  MTK_QDMA_FQ_TAIL ; 
 int MTK_QDMA_PAGE_SIZE ; 
 int /*<<< orphan*/  TX_DMA_SDL (int) ; 
 TYPE_1__* dma_alloc_coherent (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mtk_init_fq_dma(struct mtk_eth *eth)
{
	dma_addr_t phy_ring_tail;
	int cnt = MTK_DMA_SIZE;
	dma_addr_t dma_addr;
	int i;

	eth->scratch_ring = dma_alloc_coherent(eth->dev,
					       cnt * sizeof(struct mtk_tx_dma),
					       &eth->phy_scratch_ring,
					       GFP_ATOMIC);
	if (unlikely(!eth->scratch_ring))
		return -ENOMEM;

	eth->scratch_head = kcalloc(cnt, MTK_QDMA_PAGE_SIZE,
				    GFP_KERNEL);
	if (unlikely(!eth->scratch_head))
		return -ENOMEM;

	dma_addr = dma_map_single(eth->dev,
				  eth->scratch_head, cnt * MTK_QDMA_PAGE_SIZE,
				  DMA_FROM_DEVICE);
	if (unlikely(dma_mapping_error(eth->dev, dma_addr)))
		return -ENOMEM;

	phy_ring_tail = eth->phy_scratch_ring +
			(sizeof(struct mtk_tx_dma) * (cnt - 1));

	for (i = 0; i < cnt; i++) {
		eth->scratch_ring[i].txd1 =
					(dma_addr + (i * MTK_QDMA_PAGE_SIZE));
		if (i < cnt - 1)
			eth->scratch_ring[i].txd2 = (eth->phy_scratch_ring +
				((i + 1) * sizeof(struct mtk_tx_dma)));
		eth->scratch_ring[i].txd3 = TX_DMA_SDL(MTK_QDMA_PAGE_SIZE);
	}

	mtk_w32(eth, eth->phy_scratch_ring, MTK_QDMA_FQ_HEAD);
	mtk_w32(eth, phy_ring_tail, MTK_QDMA_FQ_TAIL);
	mtk_w32(eth, (cnt << 16) | cnt, MTK_QDMA_FQ_CNT);
	mtk_w32(eth, MTK_QDMA_PAGE_SIZE << 16, MTK_QDMA_FQ_BLEN);

	return 0;
}