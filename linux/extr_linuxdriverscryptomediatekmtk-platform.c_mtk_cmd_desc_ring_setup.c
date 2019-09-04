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
typedef  int u32 ;
struct mtk_sys_cap {int /*<<< orphan*/  hia_opt; } ;
struct mtk_cryp {scalar_t__ base; TYPE_1__** ring; } ;
struct TYPE_2__ {int cmd_dma; } ;

/* Variables and functions */
 scalar_t__ CDR_BASE_ADDR_HI (int) ; 
 scalar_t__ CDR_BASE_ADDR_LO (int) ; 
 scalar_t__ CDR_CFG (int) ; 
 scalar_t__ CDR_DESC_SIZE (int) ; 
 scalar_t__ CDR_DMA_CFG (int) ; 
 scalar_t__ CDR_PREP_COUNT (int) ; 
 scalar_t__ CDR_PREP_PNTR (int) ; 
 scalar_t__ CDR_PROC_COUNT (int) ; 
 scalar_t__ CDR_PROC_PNTR (int) ; 
 scalar_t__ CDR_RING_SIZE (int) ; 
 scalar_t__ CDR_STAT (int) ; 
 int MTK_CDR_STAT_CLR ; 
 int MTK_CMD_FIFO_SIZE (int /*<<< orphan*/ ) ; 
 int MTK_CNT_RST ; 
 int MTK_DESC_ATP_PRESENT ; 
 int MTK_DESC_FETCH_SIZE (int) ; 
 int MTK_DESC_FETCH_THRESH (int) ; 
 int MTK_DESC_OFF ; 
 int MTK_DESC_OFFSET (int) ; 
 int MTK_DESC_RING_SZ ; 
 int MTK_DESC_SIZE (int) ; 
 int MTK_DESC_SZ ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mtk_cmd_desc_ring_setup(struct mtk_cryp *cryp,
				    int i, struct mtk_sys_cap *cap)
{
	/* Full descriptor that fits FIFO minus one */
	u32 count =
		((1 << MTK_CMD_FIFO_SIZE(cap->hia_opt)) / MTK_DESC_SZ) - 1;

	/* Temporarily disable external triggering */
	writel(0, cryp->base + CDR_CFG(i));

	/* Clear CDR count */
	writel(MTK_CNT_RST, cryp->base + CDR_PREP_COUNT(i));
	writel(MTK_CNT_RST, cryp->base + CDR_PROC_COUNT(i));

	writel(0, cryp->base + CDR_PREP_PNTR(i));
	writel(0, cryp->base + CDR_PROC_PNTR(i));
	writel(0, cryp->base + CDR_DMA_CFG(i));

	/* Configure CDR host address space */
	writel(0, cryp->base + CDR_BASE_ADDR_HI(i));
	writel(cryp->ring[i]->cmd_dma, cryp->base + CDR_BASE_ADDR_LO(i));

	writel(MTK_DESC_RING_SZ, cryp->base + CDR_RING_SIZE(i));

	/* Clear and disable all CDR interrupts */
	writel(MTK_CDR_STAT_CLR, cryp->base + CDR_STAT(i));

	/*
	 * Set command descriptor offset and enable additional
	 * token present in descriptor.
	 */
	writel(MTK_DESC_SIZE(MTK_DESC_SZ) |
		   MTK_DESC_OFFSET(MTK_DESC_OFF) |
	       MTK_DESC_ATP_PRESENT,
	       cryp->base + CDR_DESC_SIZE(i));

	writel(MTK_DESC_FETCH_SIZE(count * MTK_DESC_OFF) |
		   MTK_DESC_FETCH_THRESH(count * MTK_DESC_SZ),
		   cryp->base + CDR_CFG(i));
}