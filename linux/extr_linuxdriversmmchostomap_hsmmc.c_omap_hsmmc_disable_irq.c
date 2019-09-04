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
struct omap_hsmmc_host {int flags; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIRQ_EN ; 
 int HSMMC_SDIO_IRQ_ENABLED ; 
 int /*<<< orphan*/  IE ; 
 int /*<<< orphan*/  ISE ; 
 int /*<<< orphan*/  OMAP_HSMMC_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAT ; 
 int /*<<< orphan*/  STAT_CLEAR ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void omap_hsmmc_disable_irq(struct omap_hsmmc_host *host)
{
	u32 irq_mask = 0;
	unsigned long flags;

	spin_lock_irqsave(&host->irq_lock, flags);
	/* no transfer running but need to keep cirq if enabled */
	if (host->flags & HSMMC_SDIO_IRQ_ENABLED)
		irq_mask |= CIRQ_EN;
	OMAP_HSMMC_WRITE(host->base, ISE, irq_mask);
	OMAP_HSMMC_WRITE(host->base, IE, irq_mask);
	OMAP_HSMMC_WRITE(host->base, STAT, STAT_CLEAR);
	spin_unlock_irqrestore(&host->irq_lock, flags);
}