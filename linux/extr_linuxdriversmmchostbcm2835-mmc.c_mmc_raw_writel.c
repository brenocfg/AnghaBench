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
struct bcm2835_host {scalar_t__ ioaddr; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_held_once (int /*<<< orphan*/ *) ; 
 int mmc_debug ; 
 int /*<<< orphan*/  udelay (unsigned int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void mmc_raw_writel(struct bcm2835_host *host, u32 val, int reg)
{
	unsigned delay;
	lockdep_assert_held_once(&host->lock);
	writel(val, host->ioaddr + reg);

	delay = ((mmc_debug >> 24) & 0xf) << ((mmc_debug >> 28) & 0xf);
	if (delay)
		udelay(delay);
}