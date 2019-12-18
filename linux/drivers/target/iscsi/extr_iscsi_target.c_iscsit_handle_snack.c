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
struct iscsi_snack {int flags; int /*<<< orphan*/  runlength; int /*<<< orphan*/  begrun; int /*<<< orphan*/  ttt; int /*<<< orphan*/  itt; int /*<<< orphan*/  exp_statsn; } ;
struct iscsi_conn {TYPE_2__* sess; int /*<<< orphan*/  cid; } ;
struct TYPE_4__ {TYPE_1__* sess_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  ErrorRecoveryLevel; } ;

/* Variables and functions */
 int ISCSI_FLAG_CMD_FINAL ; 
#define  ISCSI_FLAG_SNACK_TYPE_DATA_ACK 130 
 int ISCSI_FLAG_SNACK_TYPE_MASK ; 
#define  ISCSI_FLAG_SNACK_TYPE_RDATA 129 
#define  ISCSI_FLAG_SNACK_TYPE_STATUS 128 
 int /*<<< orphan*/  ISCSI_REASON_PROTOCOL_ERROR ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int iscsit_add_reject (struct iscsi_conn*,int /*<<< orphan*/ ,unsigned char*) ; 
 int iscsit_handle_data_ack (struct iscsi_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iscsit_handle_recovery_datain_or_r2t (struct iscsi_conn*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iscsit_handle_status_snack (struct iscsi_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

int iscsit_handle_snack(
	struct iscsi_conn *conn,
	unsigned char *buf)
{
	struct iscsi_snack *hdr;

	hdr			= (struct iscsi_snack *) buf;
	hdr->flags		&= ~ISCSI_FLAG_CMD_FINAL;

	pr_debug("Got ISCSI_INIT_SNACK, ITT: 0x%08x, ExpStatSN:"
		" 0x%08x, Type: 0x%02x, BegRun: 0x%08x, RunLength: 0x%08x,"
		" CID: %hu\n", hdr->itt, hdr->exp_statsn, hdr->flags,
			hdr->begrun, hdr->runlength, conn->cid);

	if (!conn->sess->sess_ops->ErrorRecoveryLevel) {
		pr_err("Initiator sent SNACK request while in"
			" ErrorRecoveryLevel=0.\n");
		return iscsit_add_reject(conn, ISCSI_REASON_PROTOCOL_ERROR,
					 buf);
	}
	/*
	 * SNACK_DATA and SNACK_R2T are both 0,  so check which function to
	 * call from inside iscsi_send_recovery_datain_or_r2t().
	 */
	switch (hdr->flags & ISCSI_FLAG_SNACK_TYPE_MASK) {
	case 0:
		return iscsit_handle_recovery_datain_or_r2t(conn, buf,
			hdr->itt,
			be32_to_cpu(hdr->ttt),
			be32_to_cpu(hdr->begrun),
			be32_to_cpu(hdr->runlength));
	case ISCSI_FLAG_SNACK_TYPE_STATUS:
		return iscsit_handle_status_snack(conn, hdr->itt,
			be32_to_cpu(hdr->ttt),
			be32_to_cpu(hdr->begrun), be32_to_cpu(hdr->runlength));
	case ISCSI_FLAG_SNACK_TYPE_DATA_ACK:
		return iscsit_handle_data_ack(conn, be32_to_cpu(hdr->ttt),
			be32_to_cpu(hdr->begrun),
			be32_to_cpu(hdr->runlength));
	case ISCSI_FLAG_SNACK_TYPE_RDATA:
		/* FIXME: Support R-Data SNACK */
		pr_err("R-Data SNACK Not Supported.\n");
		return iscsit_add_reject(conn, ISCSI_REASON_PROTOCOL_ERROR,
					 buf);
	default:
		pr_err("Unknown SNACK type 0x%02x, protocol"
			" error.\n", hdr->flags & 0x0f);
		return iscsit_add_reject(conn, ISCSI_REASON_PROTOCOL_ERROR,
					 buf);
	}

	return 0;
}