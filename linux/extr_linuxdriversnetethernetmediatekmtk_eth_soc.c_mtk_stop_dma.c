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
typedef  int u32 ;
struct mtk_eth {int /*<<< orphan*/  page_lock; } ;

/* Variables and functions */
 int MTK_RX_DMA_BUSY ; 
 int MTK_RX_DMA_EN ; 
 int MTK_TX_DMA_BUSY ; 
 int MTK_TX_DMA_EN ; 
 int MTK_TX_WB_DDONE ; 
 int /*<<< orphan*/  msleep (int) ; 
 int mtk_r32 (struct mtk_eth*,int) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,int,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mtk_stop_dma(struct mtk_eth *eth, u32 glo_cfg)
{
	u32 val;
	int i;

	/* stop the dma engine */
	spin_lock_bh(&eth->page_lock);
	val = mtk_r32(eth, glo_cfg);
	mtk_w32(eth, val & ~(MTK_TX_WB_DDONE | MTK_RX_DMA_EN | MTK_TX_DMA_EN),
		glo_cfg);
	spin_unlock_bh(&eth->page_lock);

	/* wait for dma stop */
	for (i = 0; i < 10; i++) {
		val = mtk_r32(eth, glo_cfg);
		if (val & (MTK_TX_DMA_BUSY | MTK_RX_DMA_BUSY)) {
			msleep(20);
			continue;
		}
		break;
	}
}