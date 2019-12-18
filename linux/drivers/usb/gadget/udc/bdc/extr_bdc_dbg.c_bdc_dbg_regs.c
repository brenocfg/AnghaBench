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
 int /*<<< orphan*/  BDC_BDCCAP0 ; 
 int /*<<< orphan*/  BDC_BDCCAP1 ; 
 int /*<<< orphan*/  BDC_BDCCFG0 ; 
 int /*<<< orphan*/  BDC_BDCCFG1 ; 
 int /*<<< orphan*/  BDC_DVCSA ; 
 int /*<<< orphan*/  BDC_DVCSB ; 
 int /*<<< orphan*/  BDC_USPC ; 
 int /*<<< orphan*/  bdc_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void bdc_dbg_regs(struct bdc *bdc)
{
	u32 temp;

	dev_vdbg(bdc->dev, "bdc->regs:%p\n", bdc->regs);
	temp = bdc_readl(bdc->regs, BDC_BDCCFG0);
	dev_vdbg(bdc->dev, "bdccfg0:0x%08x\n", temp);
	temp = bdc_readl(bdc->regs, BDC_BDCCFG1);
	dev_vdbg(bdc->dev, "bdccfg1:0x%08x\n", temp);
	temp = bdc_readl(bdc->regs, BDC_BDCCAP0);
	dev_vdbg(bdc->dev, "bdccap0:0x%08x\n", temp);
	temp = bdc_readl(bdc->regs, BDC_BDCCAP1);
	dev_vdbg(bdc->dev, "bdccap1:0x%08x\n", temp);
	temp = bdc_readl(bdc->regs, BDC_USPC);
	dev_vdbg(bdc->dev, "uspc:0x%08x\n", temp);
	temp = bdc_readl(bdc->regs, BDC_DVCSA);
	dev_vdbg(bdc->dev, "dvcsa:0x%08x\n", temp);
	temp = bdc_readl(bdc->regs, BDC_DVCSB);
	dev_vdbg(bdc->dev, "dvcsb:0x%x08\n", temp);
}