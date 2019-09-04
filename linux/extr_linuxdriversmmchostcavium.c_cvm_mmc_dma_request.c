#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct mmc_request {int /*<<< orphan*/  (* done ) (struct mmc_request*) ;TYPE_2__* cmd; struct mmc_data* data; TYPE_1__* stop; } ;
struct mmc_host {TYPE_3__* card; } ;
struct mmc_data {int blocks; int blksz; scalar_t__ timeout_ns; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct cvm_mmc_slot {struct cvm_mmc_host* host; } ;
struct cvm_mmc_host {int dma_active; int /*<<< orphan*/  (* release_bus ) (struct cvm_mmc_host*) ;scalar_t__ base; int /*<<< orphan*/  (* dmar_fixup ) (struct cvm_mmc_host*,TYPE_2__*,struct mmc_data*,int) ;int /*<<< orphan*/  (* int_enable ) (struct cvm_mmc_host*,int) ;int /*<<< orphan*/ * dev; struct mmc_request* current_req; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  error; } ;
struct TYPE_4__ {scalar_t__ opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ MIO_EMM_DMA (struct cvm_mmc_host*) ; 
 int MIO_EMM_INT_CMD_ERR ; 
 int MIO_EMM_INT_DMA_DONE ; 
 int MIO_EMM_INT_DMA_ERR ; 
 scalar_t__ MIO_EMM_STS_MASK (struct cvm_mmc_host*) ; 
 scalar_t__ MMC_STOP_TRANSMISSION ; 
 int /*<<< orphan*/  WARN_ON (struct mmc_request*) ; 
 int /*<<< orphan*/  cvm_mmc_switch_to (struct cvm_mmc_slot*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ mmc_card_sd (TYPE_3__*) ; 
 struct cvm_mmc_slot* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int) ; 
 int prepare_dma (struct cvm_mmc_host*,struct mmc_data*) ; 
 int prepare_ext_dma (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  set_wdog (struct cvm_mmc_slot*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct cvm_mmc_host*,int) ; 
 int /*<<< orphan*/  stub2 (struct cvm_mmc_host*,TYPE_2__*,struct mmc_data*,int) ; 
 int /*<<< orphan*/  stub3 (struct mmc_request*) ; 
 int /*<<< orphan*/  stub4 (struct cvm_mmc_host*) ; 
 int /*<<< orphan*/  writeq (int,scalar_t__) ; 

__attribute__((used)) static void cvm_mmc_dma_request(struct mmc_host *mmc,
				struct mmc_request *mrq)
{
	struct cvm_mmc_slot *slot = mmc_priv(mmc);
	struct cvm_mmc_host *host = slot->host;
	struct mmc_data *data;
	u64 emm_dma, addr;

	if (!mrq->data || !mrq->data->sg || !mrq->data->sg_len ||
	    !mrq->stop || mrq->stop->opcode != MMC_STOP_TRANSMISSION) {
		dev_err(&mmc->card->dev,
			"Error: cmv_mmc_dma_request no data\n");
		goto error;
	}

	cvm_mmc_switch_to(slot);

	data = mrq->data;
	pr_debug("DMA request  blocks: %d  block_size: %d  total_size: %d\n",
		 data->blocks, data->blksz, data->blocks * data->blksz);
	if (data->timeout_ns)
		set_wdog(slot, data->timeout_ns);

	WARN_ON(host->current_req);
	host->current_req = mrq;

	emm_dma = prepare_ext_dma(mmc, mrq);
	addr = prepare_dma(host, data);
	if (!addr) {
		dev_err(host->dev, "prepare_dma failed\n");
		goto error;
	}

	host->dma_active = true;
	host->int_enable(host, MIO_EMM_INT_CMD_ERR | MIO_EMM_INT_DMA_DONE |
			 MIO_EMM_INT_DMA_ERR);

	if (host->dmar_fixup)
		host->dmar_fixup(host, mrq->cmd, data, addr);

	/*
	 * If we have a valid SD card in the slot, we set the response
	 * bit mask to check for CRC errors and timeouts only.
	 * Otherwise, use the default power reset value.
	 */
	if (mmc_card_sd(mmc->card))
		writeq(0x00b00000ull, host->base + MIO_EMM_STS_MASK(host));
	else
		writeq(0xe4390080ull, host->base + MIO_EMM_STS_MASK(host));
	writeq(emm_dma, host->base + MIO_EMM_DMA(host));
	return;

error:
	mrq->cmd->error = -EINVAL;
	if (mrq->done)
		mrq->done(mrq);
	host->release_bus(host);
}