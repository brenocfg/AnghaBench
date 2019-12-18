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
typedef  int uint8_t ;
typedef  size_t uint16_t ;
struct wrb_handle {struct iscsi_task* pio_handle; } ;
struct sol_cqe {int dummy; } ;
struct iscsi_task {TYPE_1__* hdr; scalar_t__ dd_data; } ;
struct iscsi_session {int /*<<< orphan*/  back_lock; } ;
struct iscsi_conn {struct iscsi_session* session; } ;
struct hwi_wrb_context {struct wrb_handle** pwrb_handle_basestd; } ;
struct hwi_controller {struct hwi_wrb_context* wrb_context; } ;
struct common_sol_cqe {size_t wrb_index; int /*<<< orphan*/  cid; int /*<<< orphan*/  member_0; } ;
struct beiscsi_io_task {int wrb_type; } ;
struct beiscsi_hba {struct hwi_controller* phwi_ctrlr; } ;
struct beiscsi_conn {struct iscsi_conn* conn; } ;
struct TYPE_2__ {int opcode; } ;

/* Variables and functions */
 int BEISCSI_LOG_CONFIG ; 
 int BEISCSI_LOG_IO ; 
 size_t BE_GET_CRI_FROM_CID (int /*<<< orphan*/ ) ; 
#define  HWH_TYPE_IO 132 
#define  HWH_TYPE_IO_RD 131 
#define  HWH_TYPE_LOGIN 130 
#define  HWH_TYPE_LOGOUT 129 
#define  HWH_TYPE_NOP 128 
 int ISCSI_OPCODE_MASK ; 
 int ISCSI_OP_LOGOUT ; 
 int ISCSI_OP_NOOP_OUT ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  adapter_get_sol_cqe (struct beiscsi_hba*,struct sol_cqe*,struct common_sol_cqe*) ; 
 int /*<<< orphan*/  be_complete_io (struct beiscsi_conn*,struct iscsi_task*,struct common_sol_cqe*) ; 
 int /*<<< orphan*/  be_complete_logout (struct beiscsi_conn*,struct iscsi_task*,struct common_sol_cqe*) ; 
 int /*<<< orphan*/  be_complete_nopin_resp (struct beiscsi_conn*,struct iscsi_task*,struct common_sol_cqe*) ; 
 int /*<<< orphan*/  be_complete_tmf (struct beiscsi_conn*,struct iscsi_task*,struct common_sol_cqe*) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hwi_complete_cmd(struct beiscsi_conn *beiscsi_conn,
			     struct beiscsi_hba *phba, struct sol_cqe *psol)
{
	struct iscsi_conn *conn = beiscsi_conn->conn;
	struct iscsi_session *session = conn->session;
	struct common_sol_cqe csol_cqe = {0};
	struct hwi_wrb_context *pwrb_context;
	struct hwi_controller *phwi_ctrlr;
	struct wrb_handle *pwrb_handle;
	struct iscsi_task *task;
	uint16_t cri_index = 0;
	uint8_t type;

	phwi_ctrlr = phba->phwi_ctrlr;

	/* Copy the elements to a common structure */
	adapter_get_sol_cqe(phba, psol, &csol_cqe);

	cri_index = BE_GET_CRI_FROM_CID(csol_cqe.cid);
	pwrb_context = &phwi_ctrlr->wrb_context[cri_index];

	pwrb_handle = pwrb_context->pwrb_handle_basestd[
		      csol_cqe.wrb_index];

	spin_lock_bh(&session->back_lock);
	task = pwrb_handle->pio_handle;
	if (!task) {
		spin_unlock_bh(&session->back_lock);
		return;
	}
	type = ((struct beiscsi_io_task *)task->dd_data)->wrb_type;

	switch (type) {
	case HWH_TYPE_IO:
	case HWH_TYPE_IO_RD:
		if ((task->hdr->opcode & ISCSI_OPCODE_MASK) ==
		     ISCSI_OP_NOOP_OUT)
			be_complete_nopin_resp(beiscsi_conn, task, &csol_cqe);
		else
			be_complete_io(beiscsi_conn, task, &csol_cqe);
		break;

	case HWH_TYPE_LOGOUT:
		if ((task->hdr->opcode & ISCSI_OPCODE_MASK) == ISCSI_OP_LOGOUT)
			be_complete_logout(beiscsi_conn, task, &csol_cqe);
		else
			be_complete_tmf(beiscsi_conn, task, &csol_cqe);
		break;

	case HWH_TYPE_LOGIN:
		beiscsi_log(phba, KERN_ERR,
			    BEISCSI_LOG_CONFIG | BEISCSI_LOG_IO,
			    "BM_%d :\t\t No HWH_TYPE_LOGIN Expected in"
			    " hwi_complete_cmd- Solicited path\n");
		break;

	case HWH_TYPE_NOP:
		be_complete_nopin_resp(beiscsi_conn, task, &csol_cqe);
		break;

	default:
		beiscsi_log(phba, KERN_WARNING,
			    BEISCSI_LOG_CONFIG | BEISCSI_LOG_IO,
			    "BM_%d : In hwi_complete_cmd, unknown type = %d"
			    "wrb_index 0x%x CID 0x%x\n", type,
			    csol_cqe.wrb_index,
			    csol_cqe.cid);
		break;
	}

	spin_unlock_bh(&session->back_lock);
}