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
struct vpdma_data {TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPDMA_BG_RGB ; 
 int /*<<< orphan*/  VPDMA_BG_YUV ; 
 int /*<<< orphan*/  VPDMA_DEI_CHROMA1_CSTAT ; 
 int /*<<< orphan*/  VPDMA_DEI_CHROMA2_CSTAT ; 
 int /*<<< orphan*/  VPDMA_DEI_CHROMA3_CSTAT ; 
 int /*<<< orphan*/  VPDMA_DEI_LUMA1_CSTAT ; 
 int /*<<< orphan*/  VPDMA_DEI_LUMA2_CSTAT ; 
 int /*<<< orphan*/  VPDMA_DEI_LUMA3_CSTAT ; 
 int /*<<< orphan*/  VPDMA_DEI_MV_IN_CSTAT ; 
 int /*<<< orphan*/  VPDMA_DEI_MV_OUT_CSTAT ; 
 int /*<<< orphan*/  VPDMA_INT_CHAN_MASK (int) ; 
 int /*<<< orphan*/  VPDMA_INT_CHAN_STAT (int) ; 
 int /*<<< orphan*/  VPDMA_INT_CLIENT0_MASK ; 
 int /*<<< orphan*/  VPDMA_INT_CLIENT0_STAT ; 
 int /*<<< orphan*/  VPDMA_INT_CLIENT1_MASK ; 
 int /*<<< orphan*/  VPDMA_INT_CLIENT1_STAT ; 
 int /*<<< orphan*/  VPDMA_INT_LIST0_MASK ; 
 int /*<<< orphan*/  VPDMA_INT_LIST0_STAT ; 
 int /*<<< orphan*/  VPDMA_LIST_ADDR ; 
 int /*<<< orphan*/  VPDMA_LIST_ATTR ; 
 int /*<<< orphan*/  VPDMA_LIST_STAT_SYNC ; 
 int /*<<< orphan*/  VPDMA_MAX_SIZE1 ; 
 int /*<<< orphan*/  VPDMA_MAX_SIZE2 ; 
 int /*<<< orphan*/  VPDMA_MAX_SIZE3 ; 
 int /*<<< orphan*/  VPDMA_PID ; 
 int /*<<< orphan*/  VPDMA_SETUP ; 
 int /*<<< orphan*/  VPDMA_VIP_UP_UV_CSTAT ; 
 int /*<<< orphan*/  VPDMA_VIP_UP_Y_CSTAT ; 
 int /*<<< orphan*/  VPDMA_VPI_CTL_CSTAT ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  read_reg (struct vpdma_data*,int /*<<< orphan*/ ) ; 

void vpdma_dump_regs(struct vpdma_data *vpdma)
{
	struct device *dev = &vpdma->pdev->dev;

#define DUMPREG(r) dev_dbg(dev, "%-35s %08x\n", #r, read_reg(vpdma, VPDMA_##r))

	dev_dbg(dev, "VPDMA Registers:\n");

	DUMPREG(PID);
	DUMPREG(LIST_ADDR);
	DUMPREG(LIST_ATTR);
	DUMPREG(LIST_STAT_SYNC);
	DUMPREG(BG_RGB);
	DUMPREG(BG_YUV);
	DUMPREG(SETUP);
	DUMPREG(MAX_SIZE1);
	DUMPREG(MAX_SIZE2);
	DUMPREG(MAX_SIZE3);

	/*
	 * dumping registers of only group0 and group3, because VPE channels
	 * lie within group0 and group3 registers
	 */
	DUMPREG(INT_CHAN_STAT(0));
	DUMPREG(INT_CHAN_MASK(0));
	DUMPREG(INT_CHAN_STAT(3));
	DUMPREG(INT_CHAN_MASK(3));
	DUMPREG(INT_CLIENT0_STAT);
	DUMPREG(INT_CLIENT0_MASK);
	DUMPREG(INT_CLIENT1_STAT);
	DUMPREG(INT_CLIENT1_MASK);
	DUMPREG(INT_LIST0_STAT);
	DUMPREG(INT_LIST0_MASK);

	/*
	 * these are registers specific to VPE clients, we can make this
	 * function dump client registers specific to VPE or VIP based on
	 * who is using it
	 */
	DUMPREG(DEI_CHROMA1_CSTAT);
	DUMPREG(DEI_LUMA1_CSTAT);
	DUMPREG(DEI_CHROMA2_CSTAT);
	DUMPREG(DEI_LUMA2_CSTAT);
	DUMPREG(DEI_CHROMA3_CSTAT);
	DUMPREG(DEI_LUMA3_CSTAT);
	DUMPREG(DEI_MV_IN_CSTAT);
	DUMPREG(DEI_MV_OUT_CSTAT);
	DUMPREG(VIP_UP_Y_CSTAT);
	DUMPREG(VIP_UP_UV_CSTAT);
	DUMPREG(VPI_CTL_CSTAT);
}