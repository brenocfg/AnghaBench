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
struct sdhci_host {int /*<<< orphan*/  finish_tasklet; struct mmc_request** mrqs_done; } ;
struct mmc_request {int dummy; } ;

/* Variables and functions */
 int SDHCI_MAX_MRQS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __sdhci_finish_mrq(struct sdhci_host *host, struct mmc_request *mrq)
{
	int i;

	for (i = 0; i < SDHCI_MAX_MRQS; i++) {
		if (host->mrqs_done[i] == mrq) {
			WARN_ON(1);
			return;
		}
	}

	for (i = 0; i < SDHCI_MAX_MRQS; i++) {
		if (!host->mrqs_done[i]) {
			host->mrqs_done[i] = mrq;
			break;
		}
	}

	WARN_ON(i >= SDHCI_MAX_MRQS);

	tasklet_schedule(&host->finish_tasklet);
}