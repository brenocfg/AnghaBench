#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mxcmci_host {unsigned int cmdat; int do_dma; scalar_t__ dma; struct mmc_request* req; } ;
struct mmc_request {TYPE_1__* cmd; TYPE_2__* data; } ;
struct mmc_host {int dummy; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {int error; } ;

/* Variables and functions */
 unsigned int CMD_DAT_CONT_DATA_ENABLE ; 
 unsigned int CMD_DAT_CONT_INIT ; 
 unsigned int CMD_DAT_CONT_WRITE ; 
 int MMC_DATA_WRITE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct mxcmci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mxcmci_finish_request (struct mxcmci_host*,struct mmc_request*) ; 
 int mxcmci_setup_data (struct mxcmci_host*,TYPE_2__*) ; 
 int mxcmci_start_cmd (struct mxcmci_host*,TYPE_1__*,unsigned int) ; 

__attribute__((used)) static void mxcmci_request(struct mmc_host *mmc, struct mmc_request *req)
{
	struct mxcmci_host *host = mmc_priv(mmc);
	unsigned int cmdat = host->cmdat;
	int error;

	WARN_ON(host->req != NULL);

	host->req = req;
	host->cmdat &= ~CMD_DAT_CONT_INIT;

	if (host->dma)
		host->do_dma = 1;

	if (req->data) {
		error = mxcmci_setup_data(host, req->data);
		if (error) {
			req->cmd->error = error;
			goto out;
		}


		cmdat |= CMD_DAT_CONT_DATA_ENABLE;

		if (req->data->flags & MMC_DATA_WRITE)
			cmdat |= CMD_DAT_CONT_WRITE;
	}

	error = mxcmci_start_cmd(host, req->cmd, cmdat);

out:
	if (error)
		mxcmci_finish_request(host, req);
}