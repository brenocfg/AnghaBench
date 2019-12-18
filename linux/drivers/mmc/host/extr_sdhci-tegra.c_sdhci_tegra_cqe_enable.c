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
struct mmc_host {struct cqhci_host* cqe_private; } ;
struct cqhci_host {int /*<<< orphan*/  activated; } ;

/* Variables and functions */
 int /*<<< orphan*/  CQHCI_CFG ; 
 int CQHCI_ENABLE ; 
 int /*<<< orphan*/  CQHCI_SSC1 ; 
 int CQHCI_SSC1_CBC_MASK ; 
 int cqhci_readl (struct cqhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cqhci_writel (struct cqhci_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_cqe_enable (struct mmc_host*) ; 

__attribute__((used)) static void sdhci_tegra_cqe_enable(struct mmc_host *mmc)
{
	struct cqhci_host *cq_host = mmc->cqe_private;
	u32 val;

	/*
	 * Tegra CQHCI/SDMMC design prevents write access to sdhci block size
	 * register when CQE is enabled and unhalted.
	 * CQHCI driver enables CQE prior to activation, so disable CQE before
	 * programming block size in sdhci controller and enable it back.
	 */
	if (!cq_host->activated) {
		val = cqhci_readl(cq_host, CQHCI_CFG);
		if (val & CQHCI_ENABLE)
			cqhci_writel(cq_host, (val & ~CQHCI_ENABLE),
				     CQHCI_CFG);
		sdhci_cqe_enable(mmc);
		if (val & CQHCI_ENABLE)
			cqhci_writel(cq_host, val, CQHCI_CFG);
	}

	/*
	 * CMD CRC errors are seen sometimes with some eMMC devices when status
	 * command is sent during transfer of last data block which is the
	 * default case as send status command block counter (CBC) is 1.
	 * Recommended fix to set CBC to 0 allowing send status command only
	 * when data lines are idle.
	 */
	val = cqhci_readl(cq_host, CQHCI_SSC1);
	val &= ~CQHCI_SSC1_CBC_MASK;
	cqhci_writel(cq_host, val, CQHCI_SSC1);
}