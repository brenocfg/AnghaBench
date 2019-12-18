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
struct mtk_eth {int /*<<< orphan*/  dev; TYPE_1__* soc; } ;
struct TYPE_2__ {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 scalar_t__ MTK_DMA_BUSY_TIMEOUT ; 
 scalar_t__ MTK_HAS_CAPS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTK_PDMA_GLO_CFG ; 
 int /*<<< orphan*/  MTK_QDMA ; 
 int /*<<< orphan*/  MTK_QDMA_GLO_CFG ; 
 int MTK_RX_DMA_BUSY ; 
 int MTK_TX_DMA_BUSY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 int mtk_r32 (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 

__attribute__((used)) static int mtk_dma_busy_wait(struct mtk_eth *eth)
{
	unsigned long t_start = jiffies;

	while (1) {
		if (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA)) {
			if (!(mtk_r32(eth, MTK_QDMA_GLO_CFG) &
			      (MTK_RX_DMA_BUSY | MTK_TX_DMA_BUSY)))
				return 0;
		} else {
			if (!(mtk_r32(eth, MTK_PDMA_GLO_CFG) &
			      (MTK_RX_DMA_BUSY | MTK_TX_DMA_BUSY)))
				return 0;
		}

		if (time_after(jiffies, t_start + MTK_DMA_BUSY_TIMEOUT))
			break;
	}

	dev_err(eth->dev, "DMA init timeout\n");
	return -1;
}