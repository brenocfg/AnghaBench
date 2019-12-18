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
struct omap_hsmmc_host {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  base; int /*<<< orphan*/  req_in_progress; int /*<<< orphan*/  flags; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int CIRQ_EN ; 
 int CLKEXTFREE ; 
 int /*<<< orphan*/  CON ; 
 int CTPL ; 
 int /*<<< orphan*/  HSMMC_SDIO_IRQ_ENABLED ; 
 int /*<<< orphan*/  IE ; 
 int /*<<< orphan*/  ISE ; 
 int OMAP_HSMMC_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OMAP_HSMMC_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct omap_hsmmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void omap_hsmmc_enable_sdio_irq(struct mmc_host *mmc, int enable)
{
	struct omap_hsmmc_host *host = mmc_priv(mmc);
	u32 irq_mask, con;
	unsigned long flags;

	spin_lock_irqsave(&host->irq_lock, flags);

	con = OMAP_HSMMC_READ(host->base, CON);
	irq_mask = OMAP_HSMMC_READ(host->base, ISE);
	if (enable) {
		host->flags |= HSMMC_SDIO_IRQ_ENABLED;
		irq_mask |= CIRQ_EN;
		con |= CTPL | CLKEXTFREE;
	} else {
		host->flags &= ~HSMMC_SDIO_IRQ_ENABLED;
		irq_mask &= ~CIRQ_EN;
		con &= ~(CTPL | CLKEXTFREE);
	}
	OMAP_HSMMC_WRITE(host->base, CON, con);
	OMAP_HSMMC_WRITE(host->base, IE, irq_mask);

	/*
	 * if enable, piggy back detection on current request
	 * but always disable immediately
	 */
	if (!host->req_in_progress || !enable)
		OMAP_HSMMC_WRITE(host->base, ISE, irq_mask);

	/* flush posted write */
	OMAP_HSMMC_READ(host->base, IE);

	spin_unlock_irqrestore(&host->irq_lock, flags);
}