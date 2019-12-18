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
struct mxs_ssp {int /*<<< orphan*/  dma_dir; scalar_t__ base; } ;
struct mxs_mmc_host {int /*<<< orphan*/  mmc; struct mmc_request* mrq; struct mmc_data* data; struct mxs_ssp ssp; struct mmc_command* cmd; } ;
struct mmc_request {int /*<<< orphan*/  stop; struct mmc_command* sbc; int /*<<< orphan*/  cmd; } ;
struct mmc_data {int bytes_xfered; int blocks; int blksz; scalar_t__ error; scalar_t__ stop; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct mmc_command {void** resp; } ;

/* Variables and functions */
 scalar_t__ HW_SSP_SDRESP0 (struct mxs_ssp*) ; 
 scalar_t__ HW_SSP_SDRESP1 (struct mxs_ssp*) ; 
 scalar_t__ HW_SSP_SDRESP2 (struct mxs_ssp*) ; 
 scalar_t__ HW_SSP_SDRESP3 (struct mxs_ssp*) ; 
 int MMC_RSP_136 ; 
 int MMC_RSP_PRESENT ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_request_done (int /*<<< orphan*/ ,struct mmc_request*) ; 
 int mmc_resp_type (struct mmc_command*) ; 
 int /*<<< orphan*/  mxs_mmc_start_cmd (struct mxs_mmc_host*,int /*<<< orphan*/ ) ; 
 void* readl (scalar_t__) ; 

__attribute__((used)) static void mxs_mmc_request_done(struct mxs_mmc_host *host)
{
	struct mmc_command *cmd = host->cmd;
	struct mmc_data *data = host->data;
	struct mmc_request *mrq = host->mrq;
	struct mxs_ssp *ssp = &host->ssp;

	if (mmc_resp_type(cmd) & MMC_RSP_PRESENT) {
		if (mmc_resp_type(cmd) & MMC_RSP_136) {
			cmd->resp[3] = readl(ssp->base + HW_SSP_SDRESP0(ssp));
			cmd->resp[2] = readl(ssp->base + HW_SSP_SDRESP1(ssp));
			cmd->resp[1] = readl(ssp->base + HW_SSP_SDRESP2(ssp));
			cmd->resp[0] = readl(ssp->base + HW_SSP_SDRESP3(ssp));
		} else {
			cmd->resp[0] = readl(ssp->base + HW_SSP_SDRESP0(ssp));
		}
	}

	if (cmd == mrq->sbc) {
		/* Finished CMD23, now send actual command. */
		mxs_mmc_start_cmd(host, mrq->cmd);
		return;
	} else if (data) {
		dma_unmap_sg(mmc_dev(host->mmc), data->sg,
			     data->sg_len, ssp->dma_dir);
		/*
		 * If there was an error on any block, we mark all
		 * data blocks as being in error.
		 */
		if (!data->error)
			data->bytes_xfered = data->blocks * data->blksz;
		else
			data->bytes_xfered = 0;

		host->data = NULL;
		if (data->stop && (data->error || !mrq->sbc)) {
			mxs_mmc_start_cmd(host, mrq->stop);
			return;
		}
	}

	host->mrq = NULL;
	mmc_request_done(host->mmc, mrq);
}