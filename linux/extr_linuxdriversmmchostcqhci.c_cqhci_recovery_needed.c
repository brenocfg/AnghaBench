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
struct mmc_request {int /*<<< orphan*/  (* recovery_notifier ) (struct mmc_request*) ;} ;
struct mmc_host {struct cqhci_host* cqe_private; } ;
struct cqhci_host {int recovery_halt; int /*<<< orphan*/  wait_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mmc_request*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cqhci_recovery_needed(struct mmc_host *mmc, struct mmc_request *mrq,
				  bool notify)
{
	struct cqhci_host *cq_host = mmc->cqe_private;

	if (!cq_host->recovery_halt) {
		cq_host->recovery_halt = true;
		pr_debug("%s: cqhci: recovery needed\n", mmc_hostname(mmc));
		wake_up(&cq_host->wait_queue);
		if (notify && mrq->recovery_notifier)
			mrq->recovery_notifier(mrq);
	}
}