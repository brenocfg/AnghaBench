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
typedef  int /*<<< orphan*/  u32 ;
struct iscsi_pdu {int status; } ;
struct iscsi_data {int /*<<< orphan*/  offset; int /*<<< orphan*/  dlength; } ;
struct iscsi_cmd {int /*<<< orphan*/  conn; int /*<<< orphan*/  init_task_tag; struct iscsi_pdu* pdu_ptr; } ;

/* Variables and functions */
 int DATAOUT_CANNOT_RECOVER ; 
 int DATAOUT_NORMAL ; 
#define  ISCSI_PDU_CRC_FAILED 131 
#define  ISCSI_PDU_NOT_RECEIVED 130 
#define  ISCSI_PDU_RECEIVED_OK 129 
#define  ISCSI_PDU_TIMED_OUT 128 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int iscsit_dump_data_payload (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct iscsi_pdu* iscsit_get_pdu_holder (struct iscsi_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntoh24 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iscsit_dataout_pre_datapduinorder_no(
	struct iscsi_cmd *cmd,
	unsigned char *buf)
{
	struct iscsi_pdu *pdu;
	struct iscsi_data *hdr = (struct iscsi_data *) buf;
	u32 payload_length = ntoh24(hdr->dlength);

	pdu = iscsit_get_pdu_holder(cmd, be32_to_cpu(hdr->offset),
				    payload_length);
	if (!pdu)
		return DATAOUT_CANNOT_RECOVER;

	cmd->pdu_ptr = pdu;

	switch (pdu->status) {
	case ISCSI_PDU_NOT_RECEIVED:
	case ISCSI_PDU_CRC_FAILED:
	case ISCSI_PDU_TIMED_OUT:
		break;
	case ISCSI_PDU_RECEIVED_OK:
		pr_err("Command ITT: 0x%08x received already gotten"
			" Offset: %u, Length: %u\n", cmd->init_task_tag,
				be32_to_cpu(hdr->offset), payload_length);
		return iscsit_dump_data_payload(cmd->conn, payload_length, 1);
	default:
		return DATAOUT_CANNOT_RECOVER;
	}

	return DATAOUT_NORMAL;
}