#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mtk_rx_ring {int phys; int dma_size; int calc_idx_update; int calc_idx; scalar_t__ crx_idx_reg; int /*<<< orphan*/  buf_size; TYPE_2__* dma; scalar_t__* data; int /*<<< orphan*/  frag_size; } ;
struct mtk_eth {TYPE_1__* soc; int /*<<< orphan*/  dev; scalar_t__ ip_align; struct mtk_rx_ring* rx_ring; struct mtk_rx_ring rx_ring_qdma; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_4__ {unsigned int rxd1; int /*<<< orphan*/  rxd2; } ;
struct TYPE_3__ {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ETH_DATA_LEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MTK_DMA_SIZE ; 
 scalar_t__ MTK_HAS_CAPS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MTK_HW_LRO_DMA_SIZE ; 
 int MTK_MAX_LRO_RX_LENGTH ; 
 scalar_t__ MTK_PDMA_RST_IDX ; 
 scalar_t__ MTK_PRX_BASE_PTR_CFG (int) ; 
 scalar_t__ MTK_PRX_CRX_IDX_CFG (int) ; 
 scalar_t__ MTK_PRX_MAX_CNT_CFG (int) ; 
 int MTK_PST_DRX_IDX_CFG (int) ; 
 int MTK_RX_FLAGS_HWLRO ; 
 int MTK_RX_FLAGS_QDMA ; 
 int /*<<< orphan*/  MTK_SOC_MT7628 ; 
 scalar_t__ NET_SKB_PAD ; 
 int /*<<< orphan*/  RX_DMA_LSO ; 
 int /*<<< orphan*/  RX_DMA_PLEN0 (int /*<<< orphan*/ ) ; 
 TYPE_2__* dma_alloc_coherent (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_max_buf_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_max_frag_size (int) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,int,scalar_t__) ; 
 scalar_t__ netdev_alloc_frag (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int mtk_rx_alloc(struct mtk_eth *eth, int ring_no, int rx_flag)
{
	struct mtk_rx_ring *ring;
	int rx_data_len, rx_dma_size;
	int i;
	u32 offset = 0;

	if (rx_flag == MTK_RX_FLAGS_QDMA) {
		if (ring_no)
			return -EINVAL;
		ring = &eth->rx_ring_qdma;
		offset = 0x1000;
	} else {
		ring = &eth->rx_ring[ring_no];
	}

	if (rx_flag == MTK_RX_FLAGS_HWLRO) {
		rx_data_len = MTK_MAX_LRO_RX_LENGTH;
		rx_dma_size = MTK_HW_LRO_DMA_SIZE;
	} else {
		rx_data_len = ETH_DATA_LEN;
		rx_dma_size = MTK_DMA_SIZE;
	}

	ring->frag_size = mtk_max_frag_size(rx_data_len);
	ring->buf_size = mtk_max_buf_size(ring->frag_size);
	ring->data = kcalloc(rx_dma_size, sizeof(*ring->data),
			     GFP_KERNEL);
	if (!ring->data)
		return -ENOMEM;

	for (i = 0; i < rx_dma_size; i++) {
		ring->data[i] = netdev_alloc_frag(ring->frag_size);
		if (!ring->data[i])
			return -ENOMEM;
	}

	ring->dma = dma_alloc_coherent(eth->dev,
				       rx_dma_size * sizeof(*ring->dma),
				       &ring->phys, GFP_ATOMIC);
	if (!ring->dma)
		return -ENOMEM;

	for (i = 0; i < rx_dma_size; i++) {
		dma_addr_t dma_addr = dma_map_single(eth->dev,
				ring->data[i] + NET_SKB_PAD + eth->ip_align,
				ring->buf_size,
				DMA_FROM_DEVICE);
		if (unlikely(dma_mapping_error(eth->dev, dma_addr)))
			return -ENOMEM;
		ring->dma[i].rxd1 = (unsigned int)dma_addr;

		if (MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628))
			ring->dma[i].rxd2 = RX_DMA_LSO;
		else
			ring->dma[i].rxd2 = RX_DMA_PLEN0(ring->buf_size);
	}
	ring->dma_size = rx_dma_size;
	ring->calc_idx_update = false;
	ring->calc_idx = rx_dma_size - 1;
	ring->crx_idx_reg = MTK_PRX_CRX_IDX_CFG(ring_no);
	/* make sure that all changes to the dma ring are flushed before we
	 * continue
	 */
	wmb();

	mtk_w32(eth, ring->phys, MTK_PRX_BASE_PTR_CFG(ring_no) + offset);
	mtk_w32(eth, rx_dma_size, MTK_PRX_MAX_CNT_CFG(ring_no) + offset);
	mtk_w32(eth, ring->calc_idx, ring->crx_idx_reg + offset);
	mtk_w32(eth, MTK_PST_DRX_IDX_CFG(ring_no), MTK_PDMA_RST_IDX + offset);

	return 0;
}