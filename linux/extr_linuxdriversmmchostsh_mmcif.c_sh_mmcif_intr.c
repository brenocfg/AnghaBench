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
struct sh_mmcif_host {int sd_error; int /*<<< orphan*/  dma_active; int /*<<< orphan*/  mrq; int /*<<< orphan*/  addr; scalar_t__ ccs_enable; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int INT_ALL ; 
 int INT_CCS ; 
 int INT_CMD12CRE ; 
 int INT_CMD12RBE ; 
 int INT_ERR_STS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int MASK_CLEAN ; 
 int /*<<< orphan*/  MMCIF_CE_INT ; 
 int /*<<< orphan*/  MMCIF_CE_INT_MASK ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  sh_mmcif_bitclr (struct sh_mmcif_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sh_mmcif_dma_complete (struct sh_mmcif_host*) ; 
 struct device* sh_mmcif_host_to_dev (struct sh_mmcif_host*) ; 
 int sh_mmcif_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_mmcif_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t sh_mmcif_intr(int irq, void *dev_id)
{
	struct sh_mmcif_host *host = dev_id;
	struct device *dev = sh_mmcif_host_to_dev(host);
	u32 state, mask;

	state = sh_mmcif_readl(host->addr, MMCIF_CE_INT);
	mask = sh_mmcif_readl(host->addr, MMCIF_CE_INT_MASK);
	if (host->ccs_enable)
		sh_mmcif_writel(host->addr, MMCIF_CE_INT, ~(state & mask));
	else
		sh_mmcif_writel(host->addr, MMCIF_CE_INT, INT_CCS | ~(state & mask));
	sh_mmcif_bitclr(host, MMCIF_CE_INT_MASK, state & MASK_CLEAN);

	if (state & ~MASK_CLEAN)
		dev_dbg(dev, "IRQ state = 0x%08x incompletely cleared\n",
			state);

	if (state & INT_ERR_STS || state & ~INT_ALL) {
		host->sd_error = true;
		dev_dbg(dev, "int err state = 0x%08x\n", state);
	}
	if (state & ~(INT_CMD12RBE | INT_CMD12CRE)) {
		if (!host->mrq)
			dev_dbg(dev, "NULL IRQ state = 0x%08x\n", state);
		if (!host->dma_active)
			return IRQ_WAKE_THREAD;
		else if (host->sd_error)
			sh_mmcif_dma_complete(host);
	} else {
		dev_dbg(dev, "Unexpected IRQ 0x%x\n", state);
	}

	return IRQ_HANDLED;
}