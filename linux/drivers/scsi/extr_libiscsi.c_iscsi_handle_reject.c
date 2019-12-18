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
struct iscsi_task {int dummy; } ;
struct iscsi_reject {int reason; int /*<<< orphan*/  dlength; int /*<<< orphan*/  statsn; } ;
struct iscsi_nopin {int dummy; } ;
struct iscsi_hdr {int opcode; int /*<<< orphan*/  itt; } ;
struct iscsi_conn {TYPE_1__* session; scalar_t__ exp_statsn; } ;
struct TYPE_2__ {int /*<<< orphan*/  back_lock; int /*<<< orphan*/  frwd_lock; } ;

/* Variables and functions */
 int ISCSI_ERR_BAD_ITT ; 
 int ISCSI_ERR_PROTO ; 
 int ISCSI_OPCODE_MASK ; 
 int ISCSI_OP_NOOP_OUT ; 
#define  ISCSI_REASON_DATA_DIGEST_ERROR 129 
#define  ISCSI_REASON_IMM_CMD_REJECT 128 
 int /*<<< orphan*/  ISCSI_RESERVED_TAG ; 
 int /*<<< orphan*/  KERN_ERR ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_conn_printk (int /*<<< orphan*/ ,struct iscsi_conn*,char*,...) ; 
 struct iscsi_task* iscsi_itt_to_task (struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 int iscsi_nop_out_rsp (struct iscsi_task*,struct iscsi_nopin*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_send_nopout (struct iscsi_conn*,struct iscsi_nopin*) ; 
 int /*<<< orphan*/  memcpy (struct iscsi_hdr*,char*,int) ; 
 int ntoh24 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iscsi_handle_reject(struct iscsi_conn *conn, struct iscsi_hdr *hdr,
			       char *data, int datalen)
{
	struct iscsi_reject *reject = (struct iscsi_reject *)hdr;
	struct iscsi_hdr rejected_pdu;
	int opcode, rc = 0;

	conn->exp_statsn = be32_to_cpu(reject->statsn) + 1;

	if (ntoh24(reject->dlength) > datalen ||
	    ntoh24(reject->dlength) < sizeof(struct iscsi_hdr)) {
		iscsi_conn_printk(KERN_ERR, conn, "Cannot handle rejected "
				  "pdu. Invalid data length (pdu dlength "
				  "%u, datalen %d\n", ntoh24(reject->dlength),
				  datalen);
		return ISCSI_ERR_PROTO;
	}
	memcpy(&rejected_pdu, data, sizeof(struct iscsi_hdr));
	opcode = rejected_pdu.opcode & ISCSI_OPCODE_MASK;

	switch (reject->reason) {
	case ISCSI_REASON_DATA_DIGEST_ERROR:
		iscsi_conn_printk(KERN_ERR, conn,
				  "pdu (op 0x%x itt 0x%x) rejected "
				  "due to DataDigest error.\n",
				  opcode, rejected_pdu.itt);
		break;
	case ISCSI_REASON_IMM_CMD_REJECT:
		iscsi_conn_printk(KERN_ERR, conn,
				  "pdu (op 0x%x itt 0x%x) rejected. Too many "
				  "immediate commands.\n",
				  opcode, rejected_pdu.itt);
		/*
		 * We only send one TMF at a time so if the target could not
		 * handle it, then it should get fixed (RFC mandates that
		 * a target can handle one immediate TMF per conn).
		 *
		 * For nops-outs, we could have sent more than one if
		 * the target is sending us lots of nop-ins
		 */
		if (opcode != ISCSI_OP_NOOP_OUT)
			return 0;

		if (rejected_pdu.itt == cpu_to_be32(ISCSI_RESERVED_TAG)) {
			/*
			 * nop-out in response to target's nop-out rejected.
			 * Just resend.
			 */
			/* In RX path we are under back lock */
			spin_unlock(&conn->session->back_lock);
			spin_lock(&conn->session->frwd_lock);
			iscsi_send_nopout(conn,
					  (struct iscsi_nopin*)&rejected_pdu);
			spin_unlock(&conn->session->frwd_lock);
			spin_lock(&conn->session->back_lock);
		} else {
			struct iscsi_task *task;
			/*
			 * Our nop as ping got dropped. We know the target
			 * and transport are ok so just clean up
			 */
			task = iscsi_itt_to_task(conn, rejected_pdu.itt);
			if (!task) {
				iscsi_conn_printk(KERN_ERR, conn,
						 "Invalid pdu reject. Could "
						 "not lookup rejected task.\n");
				rc = ISCSI_ERR_BAD_ITT;
			} else
				rc = iscsi_nop_out_rsp(task,
					(struct iscsi_nopin*)&rejected_pdu,
					NULL, 0);
		}
		break;
	default:
		iscsi_conn_printk(KERN_ERR, conn,
				  "pdu (op 0x%x itt 0x%x) rejected. Reason "
				  "code 0x%x\n", rejected_pdu.opcode,
				  rejected_pdu.itt, reject->reason);
		break;
	}
	return rc;
}