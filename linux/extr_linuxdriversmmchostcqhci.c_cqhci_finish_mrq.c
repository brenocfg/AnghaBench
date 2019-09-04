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
struct mmc_request {struct mmc_data* data; } ;
struct mmc_host {struct cqhci_host* cqe_private; } ;
struct mmc_data {int bytes_xfered; int blksz; int blocks; scalar_t__ error; } ;
struct cqhci_slot {struct mmc_request* mrq; int /*<<< orphan*/  flags; } ;
struct cqhci_host {int qcnt; scalar_t__ recovery_halt; struct cqhci_slot* slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  CQHCI_COMPLETED ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mmc_cqe_request_done (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 

__attribute__((used)) static void cqhci_finish_mrq(struct mmc_host *mmc, unsigned int tag)
{
	struct cqhci_host *cq_host = mmc->cqe_private;
	struct cqhci_slot *slot = &cq_host->slot[tag];
	struct mmc_request *mrq = slot->mrq;
	struct mmc_data *data;

	if (!mrq) {
		WARN_ONCE(1, "%s: cqhci: spurious TCN for tag %d\n",
			  mmc_hostname(mmc), tag);
		return;
	}

	/* No completions allowed during recovery */
	if (cq_host->recovery_halt) {
		slot->flags |= CQHCI_COMPLETED;
		return;
	}

	slot->mrq = NULL;

	cq_host->qcnt -= 1;

	data = mrq->data;
	if (data) {
		if (data->error)
			data->bytes_xfered = 0;
		else
			data->bytes_xfered = data->blksz * data->blocks;
	}

	mmc_cqe_request_done(mmc, mrq);
}