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
typedef  scalar_t__ u32 ;
struct iscsi_seq {int pdu_count; scalar_t__ xfer_len; void* type; scalar_t__ orig_offset; scalar_t__ offset; scalar_t__ seq_no; scalar_t__ pdu_start; } ;
struct iscsi_pdu {scalar_t__ length; void* type; scalar_t__ seq_no; scalar_t__ offset; } ;
struct iscsi_conn {TYPE_3__* sess; TYPE_1__* conn_ops; } ;
struct TYPE_8__ {scalar_t__ data_direction; scalar_t__ data_length; } ;
struct iscsi_cmd {TYPE_4__ se_cmd; struct iscsi_conn* conn; struct iscsi_seq* seq_list; struct iscsi_pdu* pdu_list; } ;
struct iscsi_build_list {scalar_t__ type; scalar_t__ immediate_data_length; int data_direction; int randomize; } ;
struct TYPE_7__ {TYPE_2__* sess_ops; } ;
struct TYPE_6__ {int DataPDUInOrder; int DataSequenceInOrder; scalar_t__ FirstBurstLength; scalar_t__ MaxBurstLength; } ;
struct TYPE_5__ {scalar_t__ MaxXmitDataSegmentLength; scalar_t__ MaxRecvDataSegmentLength; } ;

/* Variables and functions */
 scalar_t__ DMA_TO_DEVICE ; 
 int ISCSI_PDU_READ ; 
 int ISCSI_PDU_WRITE ; 
 scalar_t__ PDULIST_IMMEDIATE ; 
 scalar_t__ PDULIST_IMMEDIATE_AND_UNSOLICITED ; 
 scalar_t__ PDULIST_UNSOLICITED ; 
 void* PDUTYPE_IMMEDIATE ; 
 void* PDUTYPE_NORMAL ; 
 void* PDUTYPE_UNSOLICITED ; 
 int RANDOM_DATAIN_PDU_OFFSETS ; 
 int RANDOM_DATAIN_SEQ_OFFSETS ; 
 int RANDOM_DATAOUT_PDU_OFFSETS ; 
 int RANDOM_R2T_OFFSETS ; 
 void* SEQTYPE_IMMEDIATE ; 
 void* SEQTYPE_NORMAL ; 
 void* SEQTYPE_UNSOLICITED ; 
 int /*<<< orphan*/  iscsit_dump_pdu_list (struct iscsi_cmd*) ; 
 int /*<<< orphan*/  iscsit_dump_seq_list (struct iscsi_cmd*) ; 
 int /*<<< orphan*/  iscsit_ordered_pdu_lists (struct iscsi_cmd*,scalar_t__) ; 
 int /*<<< orphan*/  iscsit_ordered_seq_lists (struct iscsi_cmd*,scalar_t__) ; 
 scalar_t__ iscsit_randomize_pdu_lists (struct iscsi_cmd*,scalar_t__) ; 
 scalar_t__ iscsit_randomize_seq_lists (struct iscsi_cmd*,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int iscsit_do_build_pdu_and_seq_lists(
	struct iscsi_cmd *cmd,
	struct iscsi_build_list *bl)
{
	int check_immediate = 0, datapduinorder, datasequenceinorder;
	u32 burstlength = 0, offset = 0, i = 0, mdsl;
	u32 pdu_count = 0, seq_no = 0, unsolicited_data_length = 0;
	struct iscsi_conn *conn = cmd->conn;
	struct iscsi_pdu *pdu = cmd->pdu_list;
	struct iscsi_seq *seq = cmd->seq_list;

	if (cmd->se_cmd.data_direction == DMA_TO_DEVICE)
		mdsl = cmd->conn->conn_ops->MaxXmitDataSegmentLength;
	else
		mdsl = cmd->conn->conn_ops->MaxRecvDataSegmentLength;

	datapduinorder = conn->sess->sess_ops->DataPDUInOrder;
	datasequenceinorder = conn->sess->sess_ops->DataSequenceInOrder;

	if ((bl->type == PDULIST_IMMEDIATE) ||
	    (bl->type == PDULIST_IMMEDIATE_AND_UNSOLICITED))
		check_immediate = 1;

	if ((bl->type == PDULIST_UNSOLICITED) ||
	    (bl->type == PDULIST_IMMEDIATE_AND_UNSOLICITED))
		unsolicited_data_length = min(cmd->se_cmd.data_length,
			conn->sess->sess_ops->FirstBurstLength);

	while (offset < cmd->se_cmd.data_length) {
		pdu_count++;
		if (!datapduinorder) {
			pdu[i].offset = offset;
			pdu[i].seq_no = seq_no;
		}
		if (!datasequenceinorder && (pdu_count == 1)) {
			seq[seq_no].pdu_start = i;
			seq[seq_no].seq_no = seq_no;
			seq[seq_no].offset = offset;
			seq[seq_no].orig_offset = offset;
		}

		if (check_immediate) {
			check_immediate = 0;
			if (!datapduinorder) {
				pdu[i].type = PDUTYPE_IMMEDIATE;
				pdu[i++].length = bl->immediate_data_length;
			}
			if (!datasequenceinorder) {
				seq[seq_no].type = SEQTYPE_IMMEDIATE;
				seq[seq_no].pdu_count = 1;
				seq[seq_no].xfer_len =
					bl->immediate_data_length;
			}
			offset += bl->immediate_data_length;
			pdu_count = 0;
			seq_no++;
			if (unsolicited_data_length)
				unsolicited_data_length -=
					bl->immediate_data_length;
			continue;
		}
		if (unsolicited_data_length > 0) {
			if ((offset + mdsl) >= cmd->se_cmd.data_length) {
				if (!datapduinorder) {
					pdu[i].type = PDUTYPE_UNSOLICITED;
					pdu[i].length =
						(cmd->se_cmd.data_length - offset);
				}
				if (!datasequenceinorder) {
					seq[seq_no].type = SEQTYPE_UNSOLICITED;
					seq[seq_no].pdu_count = pdu_count;
					seq[seq_no].xfer_len = (burstlength +
						(cmd->se_cmd.data_length - offset));
				}
				unsolicited_data_length -=
						(cmd->se_cmd.data_length - offset);
				offset += (cmd->se_cmd.data_length - offset);
				continue;
			}
			if ((offset + mdsl) >=
					conn->sess->sess_ops->FirstBurstLength) {
				if (!datapduinorder) {
					pdu[i].type = PDUTYPE_UNSOLICITED;
					pdu[i++].length =
					   (conn->sess->sess_ops->FirstBurstLength -
						offset);
				}
				if (!datasequenceinorder) {
					seq[seq_no].type = SEQTYPE_UNSOLICITED;
					seq[seq_no].pdu_count = pdu_count;
					seq[seq_no].xfer_len = (burstlength +
					   (conn->sess->sess_ops->FirstBurstLength -
						offset));
				}
				unsolicited_data_length -=
					(conn->sess->sess_ops->FirstBurstLength -
						offset);
				offset += (conn->sess->sess_ops->FirstBurstLength -
						offset);
				burstlength = 0;
				pdu_count = 0;
				seq_no++;
				continue;
			}

			if (!datapduinorder) {
				pdu[i].type = PDUTYPE_UNSOLICITED;
				pdu[i++].length = mdsl;
			}
			burstlength += mdsl;
			offset += mdsl;
			unsolicited_data_length -= mdsl;
			continue;
		}
		if ((offset + mdsl) >= cmd->se_cmd.data_length) {
			if (!datapduinorder) {
				pdu[i].type = PDUTYPE_NORMAL;
				pdu[i].length = (cmd->se_cmd.data_length - offset);
			}
			if (!datasequenceinorder) {
				seq[seq_no].type = SEQTYPE_NORMAL;
				seq[seq_no].pdu_count = pdu_count;
				seq[seq_no].xfer_len = (burstlength +
					(cmd->se_cmd.data_length - offset));
			}
			offset += (cmd->se_cmd.data_length - offset);
			continue;
		}
		if ((burstlength + mdsl) >=
		     conn->sess->sess_ops->MaxBurstLength) {
			if (!datapduinorder) {
				pdu[i].type = PDUTYPE_NORMAL;
				pdu[i++].length =
					(conn->sess->sess_ops->MaxBurstLength -
						burstlength);
			}
			if (!datasequenceinorder) {
				seq[seq_no].type = SEQTYPE_NORMAL;
				seq[seq_no].pdu_count = pdu_count;
				seq[seq_no].xfer_len = (burstlength +
					(conn->sess->sess_ops->MaxBurstLength -
					burstlength));
			}
			offset += (conn->sess->sess_ops->MaxBurstLength -
					burstlength);
			burstlength = 0;
			pdu_count = 0;
			seq_no++;
			continue;
		}

		if (!datapduinorder) {
			pdu[i].type = PDUTYPE_NORMAL;
			pdu[i++].length = mdsl;
		}
		burstlength += mdsl;
		offset += mdsl;
	}

	if (!datasequenceinorder) {
		if (bl->data_direction & ISCSI_PDU_WRITE) {
			if (bl->randomize & RANDOM_R2T_OFFSETS) {
				if (iscsit_randomize_seq_lists(cmd, bl->type)
						< 0)
					return -1;
			} else
				iscsit_ordered_seq_lists(cmd, bl->type);
		} else if (bl->data_direction & ISCSI_PDU_READ) {
			if (bl->randomize & RANDOM_DATAIN_SEQ_OFFSETS) {
				if (iscsit_randomize_seq_lists(cmd, bl->type)
						< 0)
					return -1;
			} else
				iscsit_ordered_seq_lists(cmd, bl->type);
		}

		iscsit_dump_seq_list(cmd);
	}
	if (!datapduinorder) {
		if (bl->data_direction & ISCSI_PDU_WRITE) {
			if (bl->randomize & RANDOM_DATAOUT_PDU_OFFSETS) {
				if (iscsit_randomize_pdu_lists(cmd, bl->type)
						< 0)
					return -1;
			} else
				iscsit_ordered_pdu_lists(cmd, bl->type);
		} else if (bl->data_direction & ISCSI_PDU_READ) {
			if (bl->randomize & RANDOM_DATAIN_PDU_OFFSETS) {
				if (iscsit_randomize_pdu_lists(cmd, bl->type)
						< 0)
					return -1;
			} else
				iscsit_ordered_pdu_lists(cmd, bl->type);
		}

		iscsit_dump_pdu_list(cmd);
	}

	return 0;
}