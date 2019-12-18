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
typedef  int u8 ;
typedef  size_t u32 ;
struct l4_kcq {int op_code; size_t conn_id; size_t cid; int /*<<< orphan*/  status; } ;
struct kcqe {int dummy; } ;
struct iscsi_kcqe {int /*<<< orphan*/  completion_status; } ;
struct cnic_sock {int const state; int /*<<< orphan*/  flags; } ;
struct cnic_local {int /*<<< orphan*/  (* close_conn ) (struct cnic_sock*,int const) ;struct cnic_sock* csk_tbl; } ;
struct cnic_dev {int /*<<< orphan*/  flags; int /*<<< orphan*/  netdev; struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNIC_F_BNX2X_CLASS ; 
 int FCOE_RAMROD_CMD_ID_TERMINATE_CONN ; 
 int /*<<< orphan*/  L4_KCQE_COMPLETION_STATUS_PARITY_ERROR ; 
#define  L4_KCQE_OPCODE_VALUE_CLOSE_COMP 136 
#define  L4_KCQE_OPCODE_VALUE_CLOSE_RECEIVED 135 
#define  L4_KCQE_OPCODE_VALUE_CONNECT_COMPLETE 134 
 int L4_KCQE_OPCODE_VALUE_OFFLOAD_PG ; 
#define  L4_KCQE_OPCODE_VALUE_RESET_COMP 133 
#define  L4_KCQE_OPCODE_VALUE_RESET_RECEIVED 132 
 int L4_KCQE_OPCODE_VALUE_UPDATE_PG ; 
#define  L5CM_RAMROD_CMD_ID_CLOSE 131 
#define  L5CM_RAMROD_CMD_ID_SEARCHER_DELETE 130 
#define  L5CM_RAMROD_CMD_ID_TCP_CONNECT 129 
#define  L5CM_RAMROD_CMD_ID_TERMINATE_OFFLOAD 128 
 size_t MAX_CM_SK_TBL_SZ ; 
 int /*<<< orphan*/  SK_F_HW_ERR ; 
 int /*<<< orphan*/  SK_F_OFFLD_COMPLETE ; 
 int /*<<< orphan*/  SK_F_OFFLD_SCHED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cnic_cm_process_offld_pg (struct cnic_dev*,struct l4_kcq*) ; 
 int /*<<< orphan*/  cnic_cm_upcall (struct cnic_local*,struct cnic_sock*,int) ; 
 int /*<<< orphan*/  cnic_in_use (struct cnic_sock*) ; 
 int /*<<< orphan*/  cnic_process_fcoe_term_conn (struct cnic_dev*,struct kcqe*) ; 
 int /*<<< orphan*/  csk_hold (struct cnic_sock*) ; 
 int /*<<< orphan*/  csk_put (struct cnic_sock*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 
 int /*<<< orphan*/  stub1 (struct cnic_sock*,int) ; 
 int /*<<< orphan*/  stub2 (struct cnic_sock*,int const) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cnic_cm_process_kcqe(struct cnic_dev *dev, struct kcqe *kcqe)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct l4_kcq *l4kcqe = (struct l4_kcq *) kcqe;
	u8 opcode = l4kcqe->op_code;
	u32 l5_cid;
	struct cnic_sock *csk;

	if (opcode == FCOE_RAMROD_CMD_ID_TERMINATE_CONN) {
		cnic_process_fcoe_term_conn(dev, kcqe);
		return;
	}
	if (opcode == L4_KCQE_OPCODE_VALUE_OFFLOAD_PG ||
	    opcode == L4_KCQE_OPCODE_VALUE_UPDATE_PG) {
		cnic_cm_process_offld_pg(dev, l4kcqe);
		return;
	}

	l5_cid = l4kcqe->conn_id;
	if (opcode & 0x80)
		l5_cid = l4kcqe->cid;
	if (l5_cid >= MAX_CM_SK_TBL_SZ)
		return;

	csk = &cp->csk_tbl[l5_cid];
	csk_hold(csk);

	if (!cnic_in_use(csk)) {
		csk_put(csk);
		return;
	}

	switch (opcode) {
	case L5CM_RAMROD_CMD_ID_TCP_CONNECT:
		if (l4kcqe->status != 0) {
			clear_bit(SK_F_OFFLD_SCHED, &csk->flags);
			cnic_cm_upcall(cp, csk,
				       L4_KCQE_OPCODE_VALUE_CONNECT_COMPLETE);
		}
		break;
	case L4_KCQE_OPCODE_VALUE_CONNECT_COMPLETE:
		if (l4kcqe->status == 0)
			set_bit(SK_F_OFFLD_COMPLETE, &csk->flags);
		else if (l4kcqe->status ==
			 L4_KCQE_COMPLETION_STATUS_PARITY_ERROR)
			set_bit(SK_F_HW_ERR, &csk->flags);

		smp_mb__before_atomic();
		clear_bit(SK_F_OFFLD_SCHED, &csk->flags);
		cnic_cm_upcall(cp, csk, opcode);
		break;

	case L5CM_RAMROD_CMD_ID_CLOSE: {
		struct iscsi_kcqe *l5kcqe = (struct iscsi_kcqe *) kcqe;

		if (l4kcqe->status == 0 && l5kcqe->completion_status == 0)
			break;

		netdev_warn(dev->netdev, "RAMROD CLOSE compl with status 0x%x completion status 0x%x\n",
			    l4kcqe->status, l5kcqe->completion_status);
		opcode = L4_KCQE_OPCODE_VALUE_CLOSE_COMP;
	}
		/* Fall through */
	case L4_KCQE_OPCODE_VALUE_RESET_RECEIVED:
	case L4_KCQE_OPCODE_VALUE_CLOSE_COMP:
	case L4_KCQE_OPCODE_VALUE_RESET_COMP:
	case L5CM_RAMROD_CMD_ID_SEARCHER_DELETE:
	case L5CM_RAMROD_CMD_ID_TERMINATE_OFFLOAD:
		if (l4kcqe->status == L4_KCQE_COMPLETION_STATUS_PARITY_ERROR)
			set_bit(SK_F_HW_ERR, &csk->flags);

		cp->close_conn(csk, opcode);
		break;

	case L4_KCQE_OPCODE_VALUE_CLOSE_RECEIVED:
		/* after we already sent CLOSE_REQ */
		if (test_bit(CNIC_F_BNX2X_CLASS, &dev->flags) &&
		    !test_bit(SK_F_OFFLD_COMPLETE, &csk->flags) &&
		    csk->state == L4_KCQE_OPCODE_VALUE_CLOSE_COMP)
			cp->close_conn(csk, L4_KCQE_OPCODE_VALUE_RESET_COMP);
		else
			cnic_cm_upcall(cp, csk, opcode);
		break;
	}
	csk_put(csk);
}