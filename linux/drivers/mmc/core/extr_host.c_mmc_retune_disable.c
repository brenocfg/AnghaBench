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
struct mmc_host {scalar_t__ need_retune; scalar_t__ retune_now; int /*<<< orphan*/  retune_timer; scalar_t__ can_retune; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_retune_unpause (struct mmc_host*) ; 

void mmc_retune_disable(struct mmc_host *host)
{
	mmc_retune_unpause(host);
	host->can_retune = 0;
	del_timer_sync(&host->retune_timer);
	host->retune_now = 0;
	host->need_retune = 0;
}