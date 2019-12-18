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
struct mmc_host {struct cqhci_host* cqe_private; } ;
struct cqhci_host {scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cqhci_disable (struct cqhci_host*) ; 

int cqhci_suspend(struct mmc_host *mmc)
{
	struct cqhci_host *cq_host = mmc->cqe_private;

	if (cq_host->enabled)
		__cqhci_disable(cq_host);

	return 0;
}