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
struct mmc_davinci_host {int /*<<< orphan*/  mmc; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ DAVINCI_SDIOIST ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int SDIOIST_IOINT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_signal_sdio_irq (int /*<<< orphan*/ ) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t mmc_davinci_sdio_irq(int irq, void *dev_id)
{
	struct mmc_davinci_host *host = dev_id;
	unsigned int status;

	status = readl(host->base + DAVINCI_SDIOIST);
	if (status & SDIOIST_IOINT) {
		dev_dbg(mmc_dev(host->mmc),
			"SDIO interrupt status %x\n", status);
		writel(status | SDIOIST_IOINT, host->base + DAVINCI_SDIOIST);
		mmc_signal_sdio_irq(host->mmc);
	}
	return IRQ_HANDLED;
}