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
struct mmc_request {int dummy; } ;
struct mmc_host {struct cqhci_host* cqe_private; } ;
struct cqhci_slot {int /*<<< orphan*/  flags; struct mmc_request* mrq; } ;
struct cqhci_host {int recovery_halt; int /*<<< orphan*/  lock; struct cqhci_slot* slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  CQHCI_EXTERNAL_TIMEOUT ; 
 int /*<<< orphan*/  cqhci_dumpregs (struct cqhci_host*) ; 
 int /*<<< orphan*/  cqhci_recovery_needed (struct mmc_host*,struct mmc_request*,int) ; 
 int cqhci_tag (struct mmc_request*) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool cqhci_timeout(struct mmc_host *mmc, struct mmc_request *mrq,
			  bool *recovery_needed)
{
	struct cqhci_host *cq_host = mmc->cqe_private;
	int tag = cqhci_tag(mrq);
	struct cqhci_slot *slot = &cq_host->slot[tag];
	unsigned long flags;
	bool timed_out;

	spin_lock_irqsave(&cq_host->lock, flags);
	timed_out = slot->mrq == mrq;
	if (timed_out) {
		slot->flags |= CQHCI_EXTERNAL_TIMEOUT;
		cqhci_recovery_needed(mmc, mrq, false);
		*recovery_needed = cq_host->recovery_halt;
	}
	spin_unlock_irqrestore(&cq_host->lock, flags);

	if (timed_out) {
		pr_err("%s: cqhci: timeout for tag %d\n",
		       mmc_hostname(mmc), tag);
		cqhci_dumpregs(cq_host);
	}

	return timed_out;
}