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
struct usdhi6_host {int /*<<< orphan*/  wait; scalar_t__ dma_active; scalar_t__ io_error; struct mmc_request* mrq; } ;
struct mmc_request {TYPE_1__* data; int /*<<< orphan*/  stop; struct mmc_command* cmd; } ;
struct mmc_command {scalar_t__ opcode; int /*<<< orphan*/  error; } ;
struct TYPE_2__ {int flags; int blocks; } ;

/* Variables and functions */
 int MMC_DATA_READ ; 
 scalar_t__ MMC_READ_MULTIPLE_BLOCK ; 
 scalar_t__ MMC_WRITE_MULTIPLE_BLOCK ; 
 scalar_t__ SD_IO_RW_EXTENDED ; 
 int /*<<< orphan*/  USDHI6_WAIT_FOR_DMA ; 
 int /*<<< orphan*/  USDHI6_WAIT_FOR_MREAD ; 
 int /*<<< orphan*/  USDHI6_WAIT_FOR_MWRITE ; 
 int /*<<< orphan*/  USDHI6_WAIT_FOR_READ ; 
 int /*<<< orphan*/  USDHI6_WAIT_FOR_WRITE ; 
 int /*<<< orphan*/  usdhi6_dma_kick (struct usdhi6_host*) ; 
 int /*<<< orphan*/  usdhi6_error_code (struct usdhi6_host*) ; 
 int /*<<< orphan*/  usdhi6_resp_read (struct usdhi6_host*) ; 
 scalar_t__ usdhi6_stop_cmd (struct usdhi6_host*) ; 

__attribute__((used)) static bool usdhi6_end_cmd(struct usdhi6_host *host)
{
	struct mmc_request *mrq = host->mrq;
	struct mmc_command *cmd = mrq->cmd;

	if (host->io_error) {
		cmd->error = usdhi6_error_code(host);
		return false;
	}

	usdhi6_resp_read(host);

	if (!mrq->data)
		return false;

	if (host->dma_active) {
		usdhi6_dma_kick(host);
		if (!mrq->stop)
			host->wait = USDHI6_WAIT_FOR_DMA;
		else if (usdhi6_stop_cmd(host) < 0)
			return false;
	} else if (mrq->data->flags & MMC_DATA_READ) {
		if (cmd->opcode == MMC_READ_MULTIPLE_BLOCK ||
		    (cmd->opcode == SD_IO_RW_EXTENDED &&
		     mrq->data->blocks > 1))
			host->wait = USDHI6_WAIT_FOR_MREAD;
		else
			host->wait = USDHI6_WAIT_FOR_READ;
	} else {
		if (cmd->opcode == MMC_WRITE_MULTIPLE_BLOCK ||
		    (cmd->opcode == SD_IO_RW_EXTENDED &&
		     mrq->data->blocks > 1))
			host->wait = USDHI6_WAIT_FOR_MWRITE;
		else
			host->wait = USDHI6_WAIT_FOR_WRITE;
	}

	return true;
}