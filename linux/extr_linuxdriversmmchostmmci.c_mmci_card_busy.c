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
struct mmci_host {int /*<<< orphan*/  lock; TYPE_1__* variant; scalar_t__ base; } ;
struct mmc_host {int dummy; } ;
struct TYPE_2__ {int busy_detect_flag; } ;

/* Variables and functions */
 scalar_t__ MMCISTATUS ; 
 struct mmci_host* mmc_priv (struct mmc_host*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mmci_card_busy(struct mmc_host *mmc)
{
	struct mmci_host *host = mmc_priv(mmc);
	unsigned long flags;
	int busy = 0;

	spin_lock_irqsave(&host->lock, flags);
	if (readl(host->base + MMCISTATUS) & host->variant->busy_detect_flag)
		busy = 1;
	spin_unlock_irqrestore(&host->lock, flags);

	return busy;
}