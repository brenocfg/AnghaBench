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
struct mmc_host {int caps; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* hw_reset ) (struct mmc_host*) ;} ;

/* Variables and functions */
 int MMC_CAP_HW_RESET ; 
 int /*<<< orphan*/  mmc_pwrseq_reset (struct mmc_host*) ; 
 int /*<<< orphan*/  stub1 (struct mmc_host*) ; 

__attribute__((used)) static void mmc_hw_reset_for_init(struct mmc_host *host)
{
	mmc_pwrseq_reset(host);

	if (!(host->caps & MMC_CAP_HW_RESET) || !host->ops->hw_reset)
		return;
	host->ops->hw_reset(host);
}