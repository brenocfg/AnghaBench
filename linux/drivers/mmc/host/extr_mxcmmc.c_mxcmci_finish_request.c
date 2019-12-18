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
struct mxcmci_host {int /*<<< orphan*/  mmc; int /*<<< orphan*/ * data; int /*<<< orphan*/ * cmd; int /*<<< orphan*/ * req; int /*<<< orphan*/  lock; scalar_t__ use_sdio; int /*<<< orphan*/  default_irq_mask; } ;
struct mmc_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_SDIO_IRQ_EN ; 
 int /*<<< orphan*/  MMC_REG_INT_CNTR ; 
 int /*<<< orphan*/  mmc_request_done (int /*<<< orphan*/ ,struct mmc_request*) ; 
 int /*<<< orphan*/  mxcmci_writel (struct mxcmci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mxcmci_finish_request(struct mxcmci_host *host,
		struct mmc_request *req)
{
	u32 int_cntr = host->default_irq_mask;
	unsigned long flags;

	spin_lock_irqsave(&host->lock, flags);
	if (host->use_sdio)
		int_cntr |= INT_SDIO_IRQ_EN;
	mxcmci_writel(host, int_cntr, MMC_REG_INT_CNTR);
	spin_unlock_irqrestore(&host->lock, flags);

	host->req = NULL;
	host->cmd = NULL;
	host->data = NULL;

	mmc_request_done(host->mmc, req);
}