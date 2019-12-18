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
struct mmci_host {TYPE_1__* ops; int /*<<< orphan*/  use_dma; } ;
struct mmc_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dma_finalize ) (struct mmci_host*,struct mmc_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct mmci_host*,struct mmc_data*) ; 

void mmci_dma_finalize(struct mmci_host *host, struct mmc_data *data)
{
	if (!host->use_dma)
		return;

	if (host->ops && host->ops->dma_finalize)
		host->ops->dma_finalize(host, data);
}