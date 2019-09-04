#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sdhci_host {int pending_reset; TYPE_1__* data; TYPE_3__* data_cmd; TYPE_2__* cmd; } ;
struct mmc_request {int dummy; } ;
struct TYPE_6__ {struct mmc_request* mrq; } ;
struct TYPE_5__ {struct mmc_request* mrq; } ;
struct TYPE_4__ {struct mmc_request* mrq; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sdhci_finish_mrq (struct sdhci_host*,struct mmc_request*) ; 
 scalar_t__ sdhci_needs_reset (struct sdhci_host*,struct mmc_request*) ; 

__attribute__((used)) static void sdhci_finish_mrq(struct sdhci_host *host, struct mmc_request *mrq)
{
	if (host->cmd && host->cmd->mrq == mrq)
		host->cmd = NULL;

	if (host->data_cmd && host->data_cmd->mrq == mrq)
		host->data_cmd = NULL;

	if (host->data && host->data->mrq == mrq)
		host->data = NULL;

	if (sdhci_needs_reset(host, mrq))
		host->pending_reset = true;

	__sdhci_finish_mrq(host, mrq);
}