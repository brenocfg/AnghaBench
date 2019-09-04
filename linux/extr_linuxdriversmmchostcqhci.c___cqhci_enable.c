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
struct mmc_host {int caps2; int cqe_on; } ;
struct cqhci_host {int caps; int rca; int activated; TYPE_1__* ops; int /*<<< orphan*/  desc_dma_base; struct mmc_host* mmc; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable ) (struct mmc_host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CQHCI_CFG ; 
 int CQHCI_DCMD ; 
 int CQHCI_ENABLE ; 
 int /*<<< orphan*/  CQHCI_IS_MASK ; 
 int /*<<< orphan*/  CQHCI_SSC2 ; 
 int CQHCI_TASK_DESC_SZ ; 
 int CQHCI_TASK_DESC_SZ_128 ; 
 int /*<<< orphan*/  CQHCI_TDLBA ; 
 int /*<<< orphan*/  CQHCI_TDLBAU ; 
 int MMC_CAP2_CQE_DCMD ; 
 int cqhci_readl (struct cqhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cqhci_set_irqs (struct cqhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cqhci_writel (struct cqhci_host*,int,int /*<<< orphan*/ ) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mmc_host*) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void __cqhci_enable(struct cqhci_host *cq_host)
{
	struct mmc_host *mmc = cq_host->mmc;
	u32 cqcfg;

	cqcfg = cqhci_readl(cq_host, CQHCI_CFG);

	/* Configuration must not be changed while enabled */
	if (cqcfg & CQHCI_ENABLE) {
		cqcfg &= ~CQHCI_ENABLE;
		cqhci_writel(cq_host, cqcfg, CQHCI_CFG);
	}

	cqcfg &= ~(CQHCI_DCMD | CQHCI_TASK_DESC_SZ);

	if (mmc->caps2 & MMC_CAP2_CQE_DCMD)
		cqcfg |= CQHCI_DCMD;

	if (cq_host->caps & CQHCI_TASK_DESC_SZ_128)
		cqcfg |= CQHCI_TASK_DESC_SZ;

	cqhci_writel(cq_host, cqcfg, CQHCI_CFG);

	cqhci_writel(cq_host, lower_32_bits(cq_host->desc_dma_base),
		     CQHCI_TDLBA);
	cqhci_writel(cq_host, upper_32_bits(cq_host->desc_dma_base),
		     CQHCI_TDLBAU);

	cqhci_writel(cq_host, cq_host->rca, CQHCI_SSC2);

	cqhci_set_irqs(cq_host, 0);

	cqcfg |= CQHCI_ENABLE;

	cqhci_writel(cq_host, cqcfg, CQHCI_CFG);

	mmc->cqe_on = true;

	if (cq_host->ops->enable)
		cq_host->ops->enable(mmc);

	/* Ensure all writes are done before interrupts are enabled */
	wmb();

	cqhci_set_irqs(cq_host, CQHCI_IS_MASK);

	cq_host->activated = true;
}