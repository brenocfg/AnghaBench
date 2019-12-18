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
struct tmio_mmc_host {int /*<<< orphan*/  (* hw_reset ) (struct tmio_mmc_host*) ;int /*<<< orphan*/  (* reset ) (struct tmio_mmc_host*) ;} ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 struct tmio_mmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  stub1 (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  stub2 (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  tmio_mmc_abort_dma (struct tmio_mmc_host*) ; 

__attribute__((used)) static void tmio_mmc_hw_reset(struct mmc_host *mmc)
{
	struct tmio_mmc_host *host = mmc_priv(mmc);

	host->reset(host);

	tmio_mmc_abort_dma(host);

	if (host->hw_reset)
		host->hw_reset(host);
}