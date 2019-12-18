#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct ibmvfc_host {int /*<<< orphan*/  dev; int /*<<< orphan*/  sent; } ;
struct TYPE_13__ {scalar_t__ expires; } ;
struct TYPE_10__ {scalar_t__ format; } ;
struct TYPE_11__ {int /*<<< orphan*/  status; void* tag; } ;
struct TYPE_9__ {void* tag; } ;
struct TYPE_12__ {TYPE_3__ mad_common; TYPE_1__ cmd; } ;
struct ibmvfc_event {int /*<<< orphan*/  (* done ) (struct ibmvfc_event*) ;TYPE_4__* xfer_iu; TYPE_6__* cmnd; TYPE_5__ timer; int /*<<< orphan*/  queue; TYPE_2__ crq; TYPE_4__ iu; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_14__ {int result; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int DID_ERROR ; 
 unsigned long HZ ; 
 int H_CLOSED ; 
 scalar_t__ IBMVFC_CMD_FORMAT ; 
 int /*<<< orphan*/  IBMVFC_MAD_CRQ_ERROR ; 
 scalar_t__ IBMVFC_MAD_FORMAT ; 
 int SCSI_MLQUEUE_HOST_BUSY ; 
 int /*<<< orphan*/  add_timer (TYPE_5__*) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (TYPE_5__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ibmvfc_free_event (struct ibmvfc_event*) ; 
 int /*<<< orphan*/  ibmvfc_scsi_eh_done (struct ibmvfc_event*) ; 
 int ibmvfc_send_crq (struct ibmvfc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_timeout ; 
 int /*<<< orphan*/  ibmvfc_trc_start (struct ibmvfc_event*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb () ; 
 scalar_t__ printk_ratelimit () ; 
 int /*<<< orphan*/  scsi_dma_unmap (TYPE_6__*) ; 
 int /*<<< orphan*/  stub1 (struct ibmvfc_event*) ; 
 int /*<<< orphan*/  timer_setup (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ibmvfc_send_event(struct ibmvfc_event *evt,
			     struct ibmvfc_host *vhost, unsigned long timeout)
{
	__be64 *crq_as_u64 = (__be64 *) &evt->crq;
	int rc;

	/* Copy the IU into the transfer area */
	*evt->xfer_iu = evt->iu;
	if (evt->crq.format == IBMVFC_CMD_FORMAT)
		evt->xfer_iu->cmd.tag = cpu_to_be64((u64)evt);
	else if (evt->crq.format == IBMVFC_MAD_FORMAT)
		evt->xfer_iu->mad_common.tag = cpu_to_be64((u64)evt);
	else
		BUG();

	list_add_tail(&evt->queue, &vhost->sent);
	timer_setup(&evt->timer, ibmvfc_timeout, 0);

	if (timeout) {
		evt->timer.expires = jiffies + (timeout * HZ);
		add_timer(&evt->timer);
	}

	mb();

	if ((rc = ibmvfc_send_crq(vhost, be64_to_cpu(crq_as_u64[0]),
				  be64_to_cpu(crq_as_u64[1])))) {
		list_del(&evt->queue);
		del_timer(&evt->timer);

		/* If send_crq returns H_CLOSED, return SCSI_MLQUEUE_HOST_BUSY.
		 * Firmware will send a CRQ with a transport event (0xFF) to
		 * tell this client what has happened to the transport. This
		 * will be handled in ibmvfc_handle_crq()
		 */
		if (rc == H_CLOSED) {
			if (printk_ratelimit())
				dev_warn(vhost->dev, "Send warning. Receive queue closed, will retry.\n");
			if (evt->cmnd)
				scsi_dma_unmap(evt->cmnd);
			ibmvfc_free_event(evt);
			return SCSI_MLQUEUE_HOST_BUSY;
		}

		dev_err(vhost->dev, "Send error (rc=%d)\n", rc);
		if (evt->cmnd) {
			evt->cmnd->result = DID_ERROR << 16;
			evt->done = ibmvfc_scsi_eh_done;
		} else
			evt->xfer_iu->mad_common.status = cpu_to_be16(IBMVFC_MAD_CRQ_ERROR);

		evt->done(evt);
	} else
		ibmvfc_trc_start(evt);

	return 0;
}