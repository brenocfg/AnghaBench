#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct iscsi_task {TYPE_3__* hdr; } ;
struct iscsi_session {int /*<<< orphan*/  back_lock; } ;
struct iscsi_logout_rsp {void* t2retain; void* t2wait; void* max_cmdsn; void* exp_cmdsn; int /*<<< orphan*/  statsn; int /*<<< orphan*/  itt; scalar_t__ hlength; int /*<<< orphan*/  flags; int /*<<< orphan*/  opcode; } ;
struct iscsi_hdr {int dummy; } ;
struct iscsi_conn {int dummy; } ;
struct cqe {int dummy; } ;
struct bnx2i_logout_response {int itt; int /*<<< orphan*/  time_to_retain; int /*<<< orphan*/  time_to_wait; int /*<<< orphan*/  max_cmd_sn; int /*<<< orphan*/  exp_cmd_sn; int /*<<< orphan*/  response; int /*<<< orphan*/  op_code; } ;
struct TYPE_6__ {int /*<<< orphan*/  resp_hdr; } ;
struct bnx2i_conn {TYPE_4__* ep; TYPE_2__ gen_pdu; TYPE_1__* cls_conn; } ;
struct TYPE_8__ {int /*<<< orphan*/  state; } ;
struct TYPE_7__ {int /*<<< orphan*/  exp_statsn; int /*<<< orphan*/  itt; } ;
struct TYPE_5__ {struct iscsi_conn* dd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP_STATE_LOGOUT_RESP_RCVD ; 
 int ISCSI_LOGOUT_RESPONSE_INDEX ; 
 int /*<<< orphan*/  __iscsi_complete_pdu (struct iscsi_conn*,struct iscsi_hdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct iscsi_task* iscsi_itt_to_task (struct iscsi_conn*,int) ; 
 int /*<<< orphan*/  memset (struct iscsi_logout_rsp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2i_process_logout_resp(struct iscsi_session *session,
				     struct bnx2i_conn *bnx2i_conn,
				     struct cqe *cqe)
{
	struct iscsi_conn *conn = bnx2i_conn->cls_conn->dd_data;
	struct iscsi_task *task;
	struct bnx2i_logout_response *logout;
	struct iscsi_logout_rsp *resp_hdr;

	logout = (struct bnx2i_logout_response *) cqe;
	spin_lock(&session->back_lock);
	task = iscsi_itt_to_task(conn,
				 logout->itt & ISCSI_LOGOUT_RESPONSE_INDEX);
	if (!task)
		goto done;

	resp_hdr = (struct iscsi_logout_rsp *) &bnx2i_conn->gen_pdu.resp_hdr;
	memset(resp_hdr, 0, sizeof(struct iscsi_hdr));
	resp_hdr->opcode = logout->op_code;
	resp_hdr->flags = logout->response;
	resp_hdr->hlength = 0;

	resp_hdr->itt = task->hdr->itt;
	resp_hdr->statsn = task->hdr->exp_statsn;
	resp_hdr->exp_cmdsn = cpu_to_be32(logout->exp_cmd_sn);
	resp_hdr->max_cmdsn = cpu_to_be32(logout->max_cmd_sn);

	resp_hdr->t2wait = cpu_to_be32(logout->time_to_wait);
	resp_hdr->t2retain = cpu_to_be32(logout->time_to_retain);

	__iscsi_complete_pdu(conn, (struct iscsi_hdr *)resp_hdr, NULL, 0);

	bnx2i_conn->ep->state = EP_STATE_LOGOUT_RESP_RCVD;
done:
	spin_unlock(&session->back_lock);
	return 0;
}