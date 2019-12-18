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
struct mxcmci_host {int /*<<< orphan*/ * cmd; int /*<<< orphan*/  lock; struct mmc_request* req; int /*<<< orphan*/  data; } ;
struct mmc_request {scalar_t__ stop; } ;

/* Variables and functions */
 int mxcmci_finish_data (struct mxcmci_host*,unsigned int) ; 
 int /*<<< orphan*/  mxcmci_finish_request (struct mxcmci_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  mxcmci_read_response (struct mxcmci_host*,unsigned int) ; 
 scalar_t__ mxcmci_start_cmd (struct mxcmci_host*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mxcmci_data_done(struct mxcmci_host *host, unsigned int stat)
{
	struct mmc_request *req;
	int data_error;
	unsigned long flags;

	spin_lock_irqsave(&host->lock, flags);

	if (!host->data) {
		spin_unlock_irqrestore(&host->lock, flags);
		return;
	}

	if (!host->req) {
		spin_unlock_irqrestore(&host->lock, flags);
		return;
	}

	req = host->req;
	if (!req->stop)
		host->req = NULL; /* we will handle finish req below */

	data_error = mxcmci_finish_data(host, stat);

	spin_unlock_irqrestore(&host->lock, flags);

	if (data_error)
		return;

	mxcmci_read_response(host, stat);
	host->cmd = NULL;

	if (req->stop) {
		if (mxcmci_start_cmd(host, req->stop, 0)) {
			mxcmci_finish_request(host, req);
			return;
		}
	} else {
		mxcmci_finish_request(host, req);
	}
}