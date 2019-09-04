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
struct sdhci_host {int /*<<< orphan*/ * align_buffer; int /*<<< orphan*/ * adma_table; int /*<<< orphan*/  align_addr; scalar_t__ adma_table_sz; scalar_t__ align_buffer_sz; struct mmc_host* mmc; } ;
struct TYPE_2__ {int /*<<< orphan*/  vqmmc; } ;
struct mmc_host {TYPE_1__ supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (struct mmc_host*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

void sdhci_cleanup_host(struct sdhci_host *host)
{
	struct mmc_host *mmc = host->mmc;

	if (!IS_ERR(mmc->supply.vqmmc))
		regulator_disable(mmc->supply.vqmmc);

	if (host->align_buffer)
		dma_free_coherent(mmc_dev(mmc), host->align_buffer_sz +
				  host->adma_table_sz, host->align_buffer,
				  host->align_addr);
	host->adma_table = NULL;
	host->align_buffer = NULL;
}