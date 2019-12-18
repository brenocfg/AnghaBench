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
struct mtk_eth {int dummy; } ;

/* Variables and functions */
 int MTK_ADMA_MODE ; 
 int MTK_HW_LRO_BW_THRE ; 
 int MTK_HW_LRO_MAX_AGG_CNT ; 
 int MTK_HW_LRO_REFRESH_TIME ; 
 int MTK_HW_LRO_REPLACE_DELTA ; 
 int MTK_HW_LRO_TIMER_UNIT ; 
 int MTK_L3_CKS_UPD_EN ; 
 int MTK_LRO_ALT_PKT_CNT_MODE ; 
 int /*<<< orphan*/  MTK_LRO_CTRL_DW1_CFG (int) ; 
 int /*<<< orphan*/  MTK_LRO_CTRL_DW2_CFG (int) ; 
 int /*<<< orphan*/  MTK_LRO_CTRL_DW3_CFG (int) ; 
 int MTK_LRO_EN ; 
 int MTK_LRO_MIN_RXD_SDL ; 
 int MTK_MAX_RX_RING_NUM ; 
 int /*<<< orphan*/  MTK_PDMA_LRO_ALT_REFRESH_TIMER ; 
 int /*<<< orphan*/  MTK_PDMA_LRO_ALT_SCORE_DELTA ; 
 int /*<<< orphan*/  MTK_PDMA_LRO_CTRL_DW0 ; 
 int /*<<< orphan*/  MTK_PDMA_LRO_CTRL_DW2 ; 
 int /*<<< orphan*/  MTK_PDMA_LRO_CTRL_DW3 ; 
 int MTK_RING_AGE_TIME_H ; 
 int MTK_RING_AGE_TIME_L ; 
 int MTK_RING_AUTO_LERAN_MODE ; 
 int MTK_RING_MAX_AGG_CNT_H ; 
 int MTK_RING_MAX_AGG_CNT_L ; 
 int MTK_RING_MAX_AGG_TIME ; 
 int MTK_RING_VLD ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_hwlro_rx_init(struct mtk_eth *eth)
{
	int i;
	u32 ring_ctrl_dw1 = 0, ring_ctrl_dw2 = 0, ring_ctrl_dw3 = 0;
	u32 lro_ctrl_dw0 = 0, lro_ctrl_dw3 = 0;

	/* set LRO rings to auto-learn modes */
	ring_ctrl_dw2 |= MTK_RING_AUTO_LERAN_MODE;

	/* validate LRO ring */
	ring_ctrl_dw2 |= MTK_RING_VLD;

	/* set AGE timer (unit: 20us) */
	ring_ctrl_dw2 |= MTK_RING_AGE_TIME_H;
	ring_ctrl_dw1 |= MTK_RING_AGE_TIME_L;

	/* set max AGG timer (unit: 20us) */
	ring_ctrl_dw2 |= MTK_RING_MAX_AGG_TIME;

	/* set max LRO AGG count */
	ring_ctrl_dw2 |= MTK_RING_MAX_AGG_CNT_L;
	ring_ctrl_dw3 |= MTK_RING_MAX_AGG_CNT_H;

	for (i = 1; i < MTK_MAX_RX_RING_NUM; i++) {
		mtk_w32(eth, ring_ctrl_dw1, MTK_LRO_CTRL_DW1_CFG(i));
		mtk_w32(eth, ring_ctrl_dw2, MTK_LRO_CTRL_DW2_CFG(i));
		mtk_w32(eth, ring_ctrl_dw3, MTK_LRO_CTRL_DW3_CFG(i));
	}

	/* IPv4 checksum update enable */
	lro_ctrl_dw0 |= MTK_L3_CKS_UPD_EN;

	/* switch priority comparison to packet count mode */
	lro_ctrl_dw0 |= MTK_LRO_ALT_PKT_CNT_MODE;

	/* bandwidth threshold setting */
	mtk_w32(eth, MTK_HW_LRO_BW_THRE, MTK_PDMA_LRO_CTRL_DW2);

	/* auto-learn score delta setting */
	mtk_w32(eth, MTK_HW_LRO_REPLACE_DELTA, MTK_PDMA_LRO_ALT_SCORE_DELTA);

	/* set refresh timer for altering flows to 1 sec. (unit: 20us) */
	mtk_w32(eth, (MTK_HW_LRO_TIMER_UNIT << 16) | MTK_HW_LRO_REFRESH_TIME,
		MTK_PDMA_LRO_ALT_REFRESH_TIMER);

	/* set HW LRO mode & the max aggregation count for rx packets */
	lro_ctrl_dw3 |= MTK_ADMA_MODE | (MTK_HW_LRO_MAX_AGG_CNT & 0xff);

	/* the minimal remaining room of SDL0 in RXD for lro aggregation */
	lro_ctrl_dw3 |= MTK_LRO_MIN_RXD_SDL;

	/* enable HW LRO */
	lro_ctrl_dw0 |= MTK_LRO_EN;

	mtk_w32(eth, lro_ctrl_dw3, MTK_PDMA_LRO_CTRL_DW3);
	mtk_w32(eth, lro_ctrl_dw0, MTK_PDMA_LRO_CTRL_DW0);

	return 0;
}