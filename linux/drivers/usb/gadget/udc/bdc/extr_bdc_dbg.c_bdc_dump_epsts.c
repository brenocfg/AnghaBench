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
typedef  int /*<<< orphan*/  u32 ;
struct bdc {int /*<<< orphan*/  dev; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDC_EPSTS0 ; 
 int /*<<< orphan*/  BDC_EPSTS1 ; 
 int /*<<< orphan*/  BDC_EPSTS2 ; 
 int /*<<< orphan*/  BDC_EPSTS3 ; 
 int /*<<< orphan*/  BDC_EPSTS4 ; 
 int /*<<< orphan*/  BDC_EPSTS5 ; 
 int /*<<< orphan*/  BDC_EPSTS6 ; 
 int /*<<< orphan*/  BDC_EPSTS7 ; 
 int /*<<< orphan*/  bdc_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void bdc_dump_epsts(struct bdc *bdc)
{
	u32 temp;

	temp = bdc_readl(bdc->regs, BDC_EPSTS0);
	dev_vdbg(bdc->dev, "BDC_EPSTS0:0x%08x\n", temp);

	temp = bdc_readl(bdc->regs, BDC_EPSTS1);
	dev_vdbg(bdc->dev, "BDC_EPSTS1:0x%x\n", temp);

	temp = bdc_readl(bdc->regs, BDC_EPSTS2);
	dev_vdbg(bdc->dev, "BDC_EPSTS2:0x%08x\n", temp);

	temp = bdc_readl(bdc->regs, BDC_EPSTS3);
	dev_vdbg(bdc->dev, "BDC_EPSTS3:0x%08x\n", temp);

	temp = bdc_readl(bdc->regs, BDC_EPSTS4);
	dev_vdbg(bdc->dev, "BDC_EPSTS4:0x%08x\n", temp);

	temp = bdc_readl(bdc->regs, BDC_EPSTS5);
	dev_vdbg(bdc->dev, "BDC_EPSTS5:0x%08x\n", temp);

	temp = bdc_readl(bdc->regs, BDC_EPSTS6);
	dev_vdbg(bdc->dev, "BDC_EPSTS6:0x%08x\n", temp);

	temp = bdc_readl(bdc->regs, BDC_EPSTS7);
	dev_vdbg(bdc->dev, "BDC_EPSTS7:0x%08x\n", temp);
}