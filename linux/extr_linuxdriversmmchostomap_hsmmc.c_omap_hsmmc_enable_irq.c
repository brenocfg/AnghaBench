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
struct omap_hsmmc_host {int flags; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  base; scalar_t__ use_dma; } ;
struct mmc_command {scalar_t__ opcode; } ;

/* Variables and functions */
 int BRR_EN ; 
 int BWR_EN ; 
 int CIRQ_EN ; 
 int DTO_EN ; 
 int HSMMC_SDIO_IRQ_ENABLED ; 
 int /*<<< orphan*/  IE ; 
 int INT_EN_MASK ; 
 int /*<<< orphan*/  ISE ; 
 scalar_t__ MMC_ERASE ; 
 int /*<<< orphan*/  OMAP_HSMMC_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STAT ; 
 int STAT_CLEAR ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void omap_hsmmc_enable_irq(struct omap_hsmmc_host *host,
				  struct mmc_command *cmd)
{
	u32 irq_mask = INT_EN_MASK;
	unsigned long flags;

	if (host->use_dma)
		irq_mask &= ~(BRR_EN | BWR_EN);

	/* Disable timeout for erases */
	if (cmd->opcode == MMC_ERASE)
		irq_mask &= ~DTO_EN;

	spin_lock_irqsave(&host->irq_lock, flags);
	OMAP_HSMMC_WRITE(host->base, STAT, STAT_CLEAR);
	OMAP_HSMMC_WRITE(host->base, ISE, irq_mask);

	/* latch pending CIRQ, but don't signal MMC core */
	if (host->flags & HSMMC_SDIO_IRQ_ENABLED)
		irq_mask |= CIRQ_EN;
	OMAP_HSMMC_WRITE(host->base, IE, irq_mask);
	spin_unlock_irqrestore(&host->irq_lock, flags);
}