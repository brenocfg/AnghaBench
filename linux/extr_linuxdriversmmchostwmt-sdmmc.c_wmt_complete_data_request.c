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
struct wmt_mci_priv {int /*<<< orphan*/  mmc; TYPE_2__* cmd; int /*<<< orphan*/ * comp_cmd; int /*<<< orphan*/  cmdcomp; struct mmc_request* req; } ;
struct mmc_request {TYPE_3__* data; TYPE_1__* cmd; } ;
struct TYPE_6__ {int bytes_xfered; int blksz; int blocks; int flags; TYPE_2__* stop; scalar_t__ error; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct TYPE_5__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  opcode; } ;
struct TYPE_4__ {scalar_t__ error; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int MMC_DATA_WRITE ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_request_done (int /*<<< orphan*/ ,struct mmc_request*) ; 
 int /*<<< orphan*/  wmt_mci_read_response (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmt_mci_send_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmt_mci_start_command (struct wmt_mci_priv*) ; 

__attribute__((used)) static void wmt_complete_data_request(struct wmt_mci_priv *priv)
{
	struct mmc_request *req;
	req = priv->req;

	req->data->bytes_xfered = req->data->blksz * req->data->blocks;

	/* unmap the DMA pages used for write data */
	if (req->data->flags & MMC_DATA_WRITE)
		dma_unmap_sg(mmc_dev(priv->mmc), req->data->sg,
			     req->data->sg_len, DMA_TO_DEVICE);
	else
		dma_unmap_sg(mmc_dev(priv->mmc), req->data->sg,
			     req->data->sg_len, DMA_FROM_DEVICE);

	/* Check if the DMA ISR returned a data error */
	if ((req->cmd->error) || (req->data->error))
		mmc_request_done(priv->mmc, req);
	else {
		wmt_mci_read_response(priv->mmc);
		if (!req->data->stop) {
			/* single-block read/write requests end here */
			mmc_request_done(priv->mmc, req);
		} else {
			/*
			 * we change the priv->cmd variable so the response is
			 * stored in the stop struct rather than the original
			 * calling command struct
			 */
			priv->comp_cmd = &priv->cmdcomp;
			init_completion(priv->comp_cmd);
			priv->cmd = req->data->stop;
			wmt_mci_send_command(priv->mmc, req->data->stop->opcode,
					     7, req->data->stop->arg, 9);
			wmt_mci_start_command(priv);
		}
	}
}