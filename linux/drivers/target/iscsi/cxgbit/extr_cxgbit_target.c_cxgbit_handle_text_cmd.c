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
typedef  int u32 ;
struct iscsi_text {int /*<<< orphan*/  cmdsn; } ;
struct iscsi_conn {TYPE_2__* sess; } ;
struct iscsi_cmd {unsigned char* text_in_ptr; } ;
struct cxgbit_sock {int /*<<< orphan*/  skb; struct iscsi_conn* conn; } ;
struct cxgbit_lro_pdu_cb {int dlen; int flags; scalar_t__ hdr; int /*<<< orphan*/  doffset; } ;
struct TYPE_4__ {TYPE_1__* sess_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  ErrorRecoveryLevel; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ISCSI_REASON_PROTOCOL_ERROR ; 
 int PDUCBF_RX_DCRC_ERR ; 
 struct cxgbit_lro_pdu_cb* cxgbit_rx_pdu_cb (int /*<<< orphan*/ ) ; 
 int iscsit_process_text_cmd (struct iscsi_conn*,struct iscsi_cmd*,struct iscsi_text*) ; 
 int iscsit_reject_cmd (struct iscsi_cmd*,int /*<<< orphan*/ ,scalar_t__) ; 
 int iscsit_setup_text_cmd (struct iscsi_conn*,struct iscsi_cmd*,struct iscsi_text*) ; 
 unsigned char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int
cxgbit_handle_text_cmd(struct cxgbit_sock *csk, struct iscsi_cmd *cmd)
{
	struct iscsi_conn *conn = csk->conn;
	struct cxgbit_lro_pdu_cb *pdu_cb = cxgbit_rx_pdu_cb(csk->skb);
	struct iscsi_text *hdr = (struct iscsi_text *)pdu_cb->hdr;
	u32 payload_length = pdu_cb->dlen;
	int rc;
	unsigned char *text_in = NULL;

	rc = iscsit_setup_text_cmd(conn, cmd, hdr);
	if (rc < 0)
		return rc;

	if (pdu_cb->flags & PDUCBF_RX_DCRC_ERR) {
		if (!conn->sess->sess_ops->ErrorRecoveryLevel) {
			pr_err("Unable to recover from"
			       " Text Data digest failure while in"
			       " ERL=0.\n");
			goto reject;
		} else {
			/*
			 * drop this PDU and let the
			 * initiator plug the CmdSN gap.
			 */
			pr_info("Dropping Text"
				" Command CmdSN: 0x%08x due to"
				" DataCRC error.\n", hdr->cmdsn);
			return 0;
		}
	}

	if (payload_length) {
		text_in = kzalloc(payload_length, GFP_KERNEL);
		if (!text_in) {
			pr_err("Unable to allocate text_in of payload_length: %u\n",
			       payload_length);
			return -ENOMEM;
		}
		skb_copy_bits(csk->skb, pdu_cb->doffset,
			      text_in, payload_length);

		text_in[payload_length - 1] = '\0';

		cmd->text_in_ptr = text_in;
	}

	return iscsit_process_text_cmd(conn, cmd, hdr);

reject:
	return iscsit_reject_cmd(cmd, ISCSI_REASON_PROTOCOL_ERROR,
				 pdu_cb->hdr);
}