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
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct srp_target_port {size_t ch_count; TYPE_2__* rport; int /*<<< orphan*/  scsi_host; struct srp_rdma_ch* ch; } ;
struct srp_request {int dummy; } ;
struct srp_rdma_ch {int dummy; } ;
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;TYPE_1__* device; int /*<<< orphan*/  request; scalar_t__ host_scribble; } ;
struct TYPE_4__ {scalar_t__ state; } ;
struct TYPE_3__ {int /*<<< orphan*/  lun; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int DID_ABORT ; 
 int FAILED ; 
 int FAST_IO_FAIL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 scalar_t__ SRP_RPORT_LOST ; 
 int /*<<< orphan*/  SRP_TSK_ABORT_TASK ; 
 int SUCCESS ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  blk_mq_unique_tag (int /*<<< orphan*/ ) ; 
 size_t blk_mq_unique_tag_to_hwq (int /*<<< orphan*/ ) ; 
 struct srp_target_port* host_to_target (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  srp_claim_req (struct srp_rdma_ch*,struct srp_request*,int /*<<< orphan*/ *,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  srp_free_req (struct srp_rdma_ch*,struct srp_request*,struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 scalar_t__ srp_send_tsk_mgmt (struct srp_rdma_ch*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static int srp_abort(struct scsi_cmnd *scmnd)
{
	struct srp_target_port *target = host_to_target(scmnd->device->host);
	struct srp_request *req = (struct srp_request *) scmnd->host_scribble;
	u32 tag;
	u16 ch_idx;
	struct srp_rdma_ch *ch;
	int ret;

	shost_printk(KERN_ERR, target->scsi_host, "SRP abort called\n");

	if (!req)
		return SUCCESS;
	tag = blk_mq_unique_tag(scmnd->request);
	ch_idx = blk_mq_unique_tag_to_hwq(tag);
	if (WARN_ON_ONCE(ch_idx >= target->ch_count))
		return SUCCESS;
	ch = &target->ch[ch_idx];
	if (!srp_claim_req(ch, req, NULL, scmnd))
		return SUCCESS;
	shost_printk(KERN_ERR, target->scsi_host,
		     "Sending SRP abort for tag %#x\n", tag);
	if (srp_send_tsk_mgmt(ch, tag, scmnd->device->lun,
			      SRP_TSK_ABORT_TASK, NULL) == 0)
		ret = SUCCESS;
	else if (target->rport->state == SRP_RPORT_LOST)
		ret = FAST_IO_FAIL;
	else
		ret = FAILED;
	if (ret == SUCCESS) {
		srp_free_req(ch, req, scmnd, 0);
		scmnd->result = DID_ABORT << 16;
		scmnd->scsi_done(scmnd);
	}

	return ret;
}