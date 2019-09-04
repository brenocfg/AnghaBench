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
struct bcm2835_host {int /*<<< orphan*/  clock; scalar_t__ ioaddr; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int BCM2835_SDHCI_WRITE_DELAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN_FREQ ; 
 int /*<<< orphan*/  lockdep_assert_held_once (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mmc_debug ; 
 int mmc_debug2 ; 
 int /*<<< orphan*/  udelay (unsigned int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void bcm2835_mmc_writel(struct bcm2835_host *host, u32 val, int reg, int from)
{
	unsigned delay;
	lockdep_assert_held_once(&host->lock);
	writel(val, host->ioaddr + reg);
	udelay(BCM2835_SDHCI_WRITE_DELAY(max(host->clock, MIN_FREQ)));

	delay = ((mmc_debug >> 16) & 0xf) << ((mmc_debug >> 20) & 0xf);
	if (delay && !((1<<from) & mmc_debug2))
		udelay(delay);
}