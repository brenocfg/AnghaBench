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
typedef  int u64 ;
struct mmc_request {int /*<<< orphan*/  (* done ) (struct mmc_request*) ;scalar_t__ data; TYPE_1__* cmd; } ;
struct cvm_mmc_host {int /*<<< orphan*/  irq_handler_lock; scalar_t__ need_irq_handler_lock; int /*<<< orphan*/  (* release_bus ) (struct cvm_mmc_host*) ;int /*<<< orphan*/  (* dmar_fixup_done ) (struct cvm_mmc_host*) ;struct mmc_request* current_req; scalar_t__ dma_active; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 scalar_t__ MIO_EMM_INT (struct cvm_mmc_host*) ; 
 int MIO_EMM_INT_BUF_DONE ; 
 int MIO_EMM_INT_CMD_DONE ; 
 int MIO_EMM_INT_CMD_ERR ; 
 int MIO_EMM_INT_DMA_DONE ; 
 int MIO_EMM_INT_DMA_ERR ; 
 int MIO_EMM_INT_SWITCH_ERR ; 
 scalar_t__ MIO_EMM_RSP_STS (struct cvm_mmc_host*) ; 
 int MIO_EMM_RSP_STS_DBUF ; 
 int MIO_EMM_RSP_STS_DMA_PEND ; 
 int MIO_EMM_RSP_STS_DMA_VAL ; 
 int /*<<< orphan*/  __acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_status (int) ; 
 int /*<<< orphan*/  check_switch_errors (struct cvm_mmc_host*) ; 
 int /*<<< orphan*/  cleanup_dma (struct cvm_mmc_host*,int) ; 
 int /*<<< orphan*/  do_read (struct cvm_mmc_host*,struct mmc_request*,int) ; 
 int /*<<< orphan*/  do_write (struct mmc_request*) ; 
 int /*<<< orphan*/  finish_dma (struct cvm_mmc_host*,scalar_t__) ; 
 int readq (scalar_t__) ; 
 int /*<<< orphan*/  set_cmd_response (struct cvm_mmc_host*,struct mmc_request*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct mmc_request*) ; 
 int /*<<< orphan*/  stub2 (struct cvm_mmc_host*) ; 
 int /*<<< orphan*/  stub3 (struct cvm_mmc_host*) ; 
 int /*<<< orphan*/  writeq (int,scalar_t__) ; 

irqreturn_t cvm_mmc_interrupt(int irq, void *dev_id)
{
	struct cvm_mmc_host *host = dev_id;
	struct mmc_request *req;
	unsigned long flags = 0;
	u64 emm_int, rsp_sts;
	bool host_done;

	if (host->need_irq_handler_lock)
		spin_lock_irqsave(&host->irq_handler_lock, flags);
	else
		__acquire(&host->irq_handler_lock);

	/* Clear interrupt bits (write 1 clears ). */
	emm_int = readq(host->base + MIO_EMM_INT(host));
	writeq(emm_int, host->base + MIO_EMM_INT(host));

	if (emm_int & MIO_EMM_INT_SWITCH_ERR)
		check_switch_errors(host);

	req = host->current_req;
	if (!req)
		goto out;

	rsp_sts = readq(host->base + MIO_EMM_RSP_STS(host));
	/*
	 * dma_val set means DMA is still in progress. Don't touch
	 * the request and wait for the interrupt indicating that
	 * the DMA is finished.
	 */
	if ((rsp_sts & MIO_EMM_RSP_STS_DMA_VAL) && host->dma_active)
		goto out;

	if (!host->dma_active && req->data &&
	    (emm_int & MIO_EMM_INT_BUF_DONE)) {
		unsigned int type = (rsp_sts >> 7) & 3;

		if (type == 1)
			do_read(host, req, rsp_sts & MIO_EMM_RSP_STS_DBUF);
		else if (type == 2)
			do_write(req);
	}

	host_done = emm_int & MIO_EMM_INT_CMD_DONE ||
		    emm_int & MIO_EMM_INT_DMA_DONE ||
		    emm_int & MIO_EMM_INT_CMD_ERR  ||
		    emm_int & MIO_EMM_INT_DMA_ERR;

	if (!(host_done && req->done))
		goto no_req_done;

	req->cmd->error = check_status(rsp_sts);

	if (host->dma_active && req->data)
		if (!finish_dma(host, req->data))
			goto no_req_done;

	set_cmd_response(host, req, rsp_sts);
	if ((emm_int & MIO_EMM_INT_DMA_ERR) &&
	    (rsp_sts & MIO_EMM_RSP_STS_DMA_PEND))
		cleanup_dma(host, rsp_sts);

	host->current_req = NULL;
	req->done(req);

no_req_done:
	if (host->dmar_fixup_done)
		host->dmar_fixup_done(host);
	if (host_done)
		host->release_bus(host);
out:
	if (host->need_irq_handler_lock)
		spin_unlock_irqrestore(&host->irq_handler_lock, flags);
	else
		__release(&host->irq_handler_lock);
	return IRQ_RETVAL(emm_int != 0);
}