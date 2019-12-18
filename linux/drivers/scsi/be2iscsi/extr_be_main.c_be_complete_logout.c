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
struct iscsi_task {scalar_t__ hdr; struct beiscsi_io_task* dd_data; } ;
struct iscsi_logout_rsp {int t2wait; int /*<<< orphan*/  itt; scalar_t__ hlength; scalar_t__* dlength; void* max_cmdsn; void* exp_cmdsn; int /*<<< orphan*/  response; int /*<<< orphan*/  flags; scalar_t__ t2retain; int /*<<< orphan*/  opcode; } ;
struct iscsi_hdr {int dummy; } ;
struct iscsi_conn {int dummy; } ;
struct common_sol_cqe {scalar_t__ cmd_wnd; scalar_t__ exp_cmdsn; int /*<<< orphan*/  i_resp; int /*<<< orphan*/  i_flags; } ;
struct beiscsi_io_task {int /*<<< orphan*/  libiscsi_itt; } ;
struct beiscsi_conn {struct iscsi_conn* conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_OP_LOGOUT_RSP ; 
 int /*<<< orphan*/  __iscsi_complete_pdu (struct iscsi_conn*,struct iscsi_hdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (scalar_t__) ; 

__attribute__((used)) static void
be_complete_logout(struct beiscsi_conn *beiscsi_conn,
		    struct iscsi_task *task,
		    struct common_sol_cqe *csol_cqe)
{
	struct iscsi_logout_rsp *hdr;
	struct beiscsi_io_task *io_task = task->dd_data;
	struct iscsi_conn *conn = beiscsi_conn->conn;

	hdr = (struct iscsi_logout_rsp *)task->hdr;
	hdr->opcode = ISCSI_OP_LOGOUT_RSP;
	hdr->t2wait = 5;
	hdr->t2retain = 0;
	hdr->flags = csol_cqe->i_flags;
	hdr->response = csol_cqe->i_resp;
	hdr->exp_cmdsn = cpu_to_be32(csol_cqe->exp_cmdsn);
	hdr->max_cmdsn = cpu_to_be32(csol_cqe->exp_cmdsn +
				     csol_cqe->cmd_wnd - 1);

	hdr->dlength[0] = 0;
	hdr->dlength[1] = 0;
	hdr->dlength[2] = 0;
	hdr->hlength = 0;
	hdr->itt = io_task->libiscsi_itt;
	__iscsi_complete_pdu(conn, (struct iscsi_hdr *)hdr, NULL, 0);
}