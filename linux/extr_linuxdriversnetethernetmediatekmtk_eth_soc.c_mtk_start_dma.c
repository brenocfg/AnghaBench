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
struct mtk_eth {int dummy; } ;

/* Variables and functions */
 int MTK_DMA_SIZE_16DWORDS ; 
 int MTK_MULTI_EN ; 
 int MTK_NDP_CO_PRO ; 
 int /*<<< orphan*/  MTK_PDMA_GLO_CFG ; 
 int /*<<< orphan*/  MTK_QDMA_GLO_CFG ; 
 int MTK_RX_2B_OFFSET ; 
 int MTK_RX_BT_32DWORDS ; 
 int MTK_RX_DMA_EN ; 
 int MTK_TX_DMA_EN ; 
 int MTK_TX_WB_DDONE ; 
 int /*<<< orphan*/  mtk_dma_free (struct mtk_eth*) ; 
 int mtk_dma_init (struct mtk_eth*) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_start_dma(struct mtk_eth *eth)
{
	int err;

	err = mtk_dma_init(eth);
	if (err) {
		mtk_dma_free(eth);
		return err;
	}

	mtk_w32(eth,
		MTK_TX_WB_DDONE | MTK_TX_DMA_EN |
		MTK_DMA_SIZE_16DWORDS | MTK_NDP_CO_PRO |
		MTK_RX_DMA_EN | MTK_RX_2B_OFFSET |
		MTK_RX_BT_32DWORDS,
		MTK_QDMA_GLO_CFG);

	mtk_w32(eth,
		MTK_RX_DMA_EN | MTK_RX_2B_OFFSET |
		MTK_RX_BT_32DWORDS | MTK_MULTI_EN,
		MTK_PDMA_GLO_CFG);

	return 0;
}