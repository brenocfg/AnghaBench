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
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static inline u32 bcm2835_mmc_readl(struct bcm2835_host *host, int reg)
{
	lockdep_assert_held_once(&host->lock);
	return readl(host->ioaddr + reg);
}