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
struct iscsi_tm_rsp {int /*<<< orphan*/  itt; void* max_cmdsn; void* exp_cmdsn; int /*<<< orphan*/  response; int /*<<< orphan*/  flags; int /*<<< orphan*/  opcode; } ;
struct iscsi_task {scalar_t__ hdr; struct beiscsi_io_task* dd_data; } ;
struct iscsi_hdr {int dummy; } ;
struct iscsi_conn {int dummy; } ;
struct common_sol_cqe {scalar_t__ cmd_wnd; scalar_t__ exp_cmdsn; int /*<<< orphan*/  i_resp; int /*<<< orphan*/  i_flags; } ;
struct beiscsi_io_task {int /*<<< orphan*/  libiscsi_itt; } ;
struct beiscsi_conn {struct iscsi_conn* conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_OP_SCSI_TMFUNC_RSP ; 
 int /*<<< orphan*/  __iscsi_complete_pdu (struct iscsi_conn*,struct iscsi_hdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (scalar_t__) ; 

__attribute__((used)) static void
be_complete_tmf(struct beiscsi_conn *beiscsi_conn,
		 struct iscsi_task *task,
		 struct common_sol_cqe *csol_cqe)
{
	struct iscsi_tm_rsp *hdr;
	struct iscsi_conn *conn = beiscsi_conn->conn;
	struct beiscsi_io_task *io_task = task->dd_data;

	hdr = (struct iscsi_tm_rsp *)task->hdr;
	hdr->opcode = ISCSI_OP_SCSI_TMFUNC_RSP;
	hdr->flags = csol_cqe->i_flags;
	hdr->response = csol_cqe->i_resp;
	hdr->exp_cmdsn = cpu_to_be32(csol_cqe->exp_cmdsn);
	hdr->max_cmdsn = cpu_to_be32(csol_cqe->exp_cmdsn +
				     csol_cqe->cmd_wnd - 1);

	hdr->itt = io_task->libiscsi_itt;
	__iscsi_complete_pdu(conn, (struct iscsi_hdr *)hdr, NULL, 0);
}