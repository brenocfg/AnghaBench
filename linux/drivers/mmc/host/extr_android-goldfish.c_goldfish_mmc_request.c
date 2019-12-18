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
struct mmc_request {TYPE_1__* cmd; } ;
struct mmc_host {int dummy; } ;
struct goldfish_mmc_host {struct mmc_request* mrq; } ;
struct TYPE_2__ {scalar_t__ opcode; int flags; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int MMC_CMD_BCR ; 
 int MMC_RSP_R4 ; 
 int MMC_RSP_SPI_R4 ; 
 scalar_t__ SD_IO_SEND_OP_COND ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  goldfish_mmc_prepare_data (struct goldfish_mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  goldfish_mmc_start_command (struct goldfish_mmc_host*,TYPE_1__*) ; 
 struct goldfish_mmc_host* mmc_priv (struct mmc_host*) ; 

__attribute__((used)) static void goldfish_mmc_request(struct mmc_host *mmc, struct mmc_request *req)
{
	struct goldfish_mmc_host *host = mmc_priv(mmc);

	WARN_ON(host->mrq != NULL);

	host->mrq = req;
	goldfish_mmc_prepare_data(host, req);
	goldfish_mmc_start_command(host, req->cmd);

	/*
	 * This is to avoid accidentally being detected as an SDIO card
	 * in mmc_attach_sdio().
	 */
	if (req->cmd->opcode == SD_IO_SEND_OP_COND &&
	    req->cmd->flags == (MMC_RSP_SPI_R4 | MMC_RSP_R4 | MMC_CMD_BCR))
		req->cmd->error = -EINVAL;
}