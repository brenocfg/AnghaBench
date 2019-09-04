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
struct mmc_host {scalar_t__ bus_refs; int /*<<< orphan*/  lock; scalar_t__ bus_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mmc_release_bus (struct mmc_host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void mmc_bus_put(struct mmc_host *host)
{
	unsigned long flags;

	spin_lock_irqsave(&host->lock, flags);
	host->bus_refs--;
	if ((host->bus_refs == 0) && host->bus_ops)
		__mmc_release_bus(host);
	spin_unlock_irqrestore(&host->lock, flags);
}