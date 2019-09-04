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
struct mmc_host {int dummy; } ;
struct bcm2835_host {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm2835_sdhost_reset_internal (struct bcm2835_host*) ; 
 int /*<<< orphan*/  log_event (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bcm2835_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void bcm2835_sdhost_reset(struct mmc_host *mmc)
{
	struct bcm2835_host *host = mmc_priv(mmc);
	unsigned long flags;
	spin_lock_irqsave(&host->lock, flags);
	log_event("RST<", 0, 0);

	bcm2835_sdhost_reset_internal(host);

	spin_unlock_irqrestore(&host->lock, flags);
}