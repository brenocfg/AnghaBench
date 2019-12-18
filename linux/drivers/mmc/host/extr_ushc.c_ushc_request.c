#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ushc_data {int clock_freq; TYPE_4__* data_urb; TYPE_4__* cbw_urb; int /*<<< orphan*/  lock; TYPE_4__* csw_urb; int /*<<< orphan*/  usb_dev; TYPE_1__* cbw; struct mmc_request* current_req; int /*<<< orphan*/  flags; } ;
struct mmc_request {TYPE_3__* cmd; struct mmc_data* data; } ;
struct mmc_host {int dummy; } ;
struct mmc_data {int flags; TYPE_2__* sg; int /*<<< orphan*/  blksz; } ;
struct TYPE_10__ {int num_sgs; TYPE_2__* sg; } ;
struct TYPE_9__ {int flags; int error; int /*<<< orphan*/  arg; int /*<<< orphan*/  opcode; } ;
struct TYPE_8__ {int /*<<< orphan*/  length; } ;
struct TYPE_7__ {int /*<<< orphan*/  arg; void* block_size; void* cmd_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISCONNECTED ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MMC_DATA_READ ; 
 int MMC_RSP_136 ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data_callback ; 
 struct ushc_data* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_request_done (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ushc_data*) ; 
 int usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 
 int usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unlink_urb (TYPE_4__*) ; 

__attribute__((used)) static void ushc_request(struct mmc_host *mmc, struct mmc_request *req)
{
	struct ushc_data *ushc = mmc_priv(mmc);
	int ret;
	unsigned long flags;

	spin_lock_irqsave(&ushc->lock, flags);

	if (test_bit(DISCONNECTED, &ushc->flags)) {
		ret = -ENODEV;
		goto out;
	}

	/* Version 2 firmware doesn't support the R2 response format. */
	if (req->cmd->flags & MMC_RSP_136) {
		ret = -EINVAL;
		goto out;
	}

	/* The Astoria's data FIFOs don't work with clock speeds < 5MHz so
	   limit commands with data to 6MHz or more. */
	if (req->data && ushc->clock_freq < 6000000) {
		ret = -EINVAL;
		goto out;
	}

	ushc->current_req = req;

	/* Start cmd with CBW. */
	ushc->cbw->cmd_idx = cpu_to_le16(req->cmd->opcode);
	if (req->data)
		ushc->cbw->block_size = cpu_to_le16(req->data->blksz);
	else
		ushc->cbw->block_size = 0;
	ushc->cbw->arg = cpu_to_le32(req->cmd->arg);

	ret = usb_submit_urb(ushc->cbw_urb, GFP_ATOMIC);
	if (ret < 0)
		goto out;

	/* Submit data (if any). */
	if (req->data) {
		struct mmc_data *data = req->data;
		int pipe;

		if (data->flags & MMC_DATA_READ)
			pipe = usb_rcvbulkpipe(ushc->usb_dev, 6);
		else
			pipe = usb_sndbulkpipe(ushc->usb_dev, 2);

		usb_fill_bulk_urb(ushc->data_urb, ushc->usb_dev, pipe,
				  NULL, data->sg->length,
				  data_callback, ushc);
		ushc->data_urb->num_sgs = 1;
		ushc->data_urb->sg = data->sg;
		ret = usb_submit_urb(ushc->data_urb, GFP_ATOMIC);
		if (ret < 0)
			goto out;
	}

	/* Submit CSW. */
	ret = usb_submit_urb(ushc->csw_urb, GFP_ATOMIC);

out:
	spin_unlock_irqrestore(&ushc->lock, flags);
	if (ret < 0) {
		usb_unlink_urb(ushc->cbw_urb);
		usb_unlink_urb(ushc->data_urb);
		req->cmd->error = ret;
		mmc_request_done(mmc, req);
	}
}