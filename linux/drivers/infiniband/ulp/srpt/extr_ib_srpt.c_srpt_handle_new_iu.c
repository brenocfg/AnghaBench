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
typedef  int u8 ;
struct srpt_send_ioctx {int /*<<< orphan*/  recv_ioctx; } ;
struct TYPE_4__ {int offset; struct srp_cmd* buf; int /*<<< orphan*/  dma; } ;
struct srpt_recv_ioctx {int /*<<< orphan*/  wait_list; TYPE_1__ ioctx; } ;
struct srpt_rdma_ch {scalar_t__ state; int processing_wait_list; int /*<<< orphan*/  cmd_wait_list; TYPE_2__* sport; } ;
struct srp_cmd {int opcode; } ;
struct TYPE_6__ {int /*<<< orphan*/  device; } ;
struct TYPE_5__ {TYPE_3__* sdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CH_CONNECTING ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
#define  SRP_AER_RSP 133 
#define  SRP_CMD 132 
#define  SRP_CRED_RSP 131 
#define  SRP_I_LOGOUT 130 
#define  SRP_RSP 129 
#define  SRP_TSK_MGMT 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int srp_max_req_size ; 
 struct srpt_send_ioctx* srpt_get_send_ioctx (struct srpt_rdma_ch*) ; 
 int /*<<< orphan*/  srpt_handle_cmd (struct srpt_rdma_ch*,struct srpt_recv_ioctx*,struct srpt_send_ioctx*) ; 
 int /*<<< orphan*/  srpt_handle_tsk_mgmt (struct srpt_rdma_ch*,struct srpt_recv_ioctx*,struct srpt_send_ioctx*) ; 
 int /*<<< orphan*/  srpt_post_recv (TYPE_3__*,struct srpt_rdma_ch*,struct srpt_recv_ioctx*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool
srpt_handle_new_iu(struct srpt_rdma_ch *ch, struct srpt_recv_ioctx *recv_ioctx)
{
	struct srpt_send_ioctx *send_ioctx = NULL;
	struct srp_cmd *srp_cmd;
	bool res = false;
	u8 opcode;

	BUG_ON(!ch);
	BUG_ON(!recv_ioctx);

	if (unlikely(ch->state == CH_CONNECTING))
		goto push;

	ib_dma_sync_single_for_cpu(ch->sport->sdev->device,
				   recv_ioctx->ioctx.dma,
				   recv_ioctx->ioctx.offset + srp_max_req_size,
				   DMA_FROM_DEVICE);

	srp_cmd = recv_ioctx->ioctx.buf + recv_ioctx->ioctx.offset;
	opcode = srp_cmd->opcode;
	if (opcode == SRP_CMD || opcode == SRP_TSK_MGMT) {
		send_ioctx = srpt_get_send_ioctx(ch);
		if (unlikely(!send_ioctx))
			goto push;
	}

	if (!list_empty(&recv_ioctx->wait_list)) {
		WARN_ON_ONCE(!ch->processing_wait_list);
		list_del_init(&recv_ioctx->wait_list);
	}

	switch (opcode) {
	case SRP_CMD:
		srpt_handle_cmd(ch, recv_ioctx, send_ioctx);
		break;
	case SRP_TSK_MGMT:
		srpt_handle_tsk_mgmt(ch, recv_ioctx, send_ioctx);
		break;
	case SRP_I_LOGOUT:
		pr_err("Not yet implemented: SRP_I_LOGOUT\n");
		break;
	case SRP_CRED_RSP:
		pr_debug("received SRP_CRED_RSP\n");
		break;
	case SRP_AER_RSP:
		pr_debug("received SRP_AER_RSP\n");
		break;
	case SRP_RSP:
		pr_err("Received SRP_RSP\n");
		break;
	default:
		pr_err("received IU with unknown opcode 0x%x\n", opcode);
		break;
	}

	if (!send_ioctx || !send_ioctx->recv_ioctx)
		srpt_post_recv(ch->sport->sdev, ch, recv_ioctx);
	res = true;

out:
	return res;

push:
	if (list_empty(&recv_ioctx->wait_list)) {
		WARN_ON_ONCE(ch->processing_wait_list);
		list_add_tail(&recv_ioctx->wait_list, &ch->cmd_wait_list);
	}
	goto out;
}