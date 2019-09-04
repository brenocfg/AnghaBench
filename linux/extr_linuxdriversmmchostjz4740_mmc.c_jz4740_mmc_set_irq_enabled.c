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
struct jz4740_mmc_host {unsigned int irq_mask; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  jz4740_mmc_write_irq_mask (struct jz4740_mmc_host*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void jz4740_mmc_set_irq_enabled(struct jz4740_mmc_host *host,
	unsigned int irq, bool enabled)
{
	unsigned long flags;

	spin_lock_irqsave(&host->lock, flags);
	if (enabled)
		host->irq_mask &= ~irq;
	else
		host->irq_mask |= irq;

	jz4740_mmc_write_irq_mask(host, host->irq_mask);
	spin_unlock_irqrestore(&host->lock, flags);
}