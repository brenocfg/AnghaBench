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
struct sdhci_host {int /*<<< orphan*/  complete_work; int /*<<< orphan*/  complete_wq; } ;
struct mmc_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sdhci_finish_mrq (struct sdhci_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sdhci_finish_mrq(struct sdhci_host *host, struct mmc_request *mrq)
{
	__sdhci_finish_mrq(host, mrq);

	queue_work(host->complete_wq, &host->complete_work);
}