#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct iscsi_datain_req {scalar_t__ begrun; scalar_t__ next_burst_len; int /*<<< orphan*/  read_data_done; } ;
struct iscsi_conn {TYPE_3__* sess; TYPE_1__* conn_ops; } ;
struct iscsi_cmd {scalar_t__ pdu_send_order; scalar_t__ pdu_start; scalar_t__ seq_no; struct iscsi_conn* conn; } ;
struct TYPE_6__ {TYPE_2__* sess_ops; } ;
struct TYPE_5__ {scalar_t__ MaxBurstLength; int /*<<< orphan*/  DataPDUInOrder; } ;
struct TYPE_4__ {scalar_t__ MaxRecvDataSegmentLength; } ;

/* Variables and functions */

int iscsit_create_recovery_datain_values_datasequenceinorder_yes(
	struct iscsi_cmd *cmd,
	struct iscsi_datain_req *dr)
{
	u32 data_sn = 0, data_sn_count = 0;
	u32 pdu_start = 0, seq_no = 0;
	u32 begrun = dr->begrun;
	struct iscsi_conn *conn = cmd->conn;

	while (begrun > data_sn++) {
		data_sn_count++;
		if ((dr->next_burst_len +
		     conn->conn_ops->MaxRecvDataSegmentLength) <
		     conn->sess->sess_ops->MaxBurstLength) {
			dr->read_data_done +=
				conn->conn_ops->MaxRecvDataSegmentLength;
			dr->next_burst_len +=
				conn->conn_ops->MaxRecvDataSegmentLength;
		} else {
			dr->read_data_done +=
				(conn->sess->sess_ops->MaxBurstLength -
				 dr->next_burst_len);
			dr->next_burst_len = 0;
			pdu_start += data_sn_count;
			data_sn_count = 0;
			seq_no++;
		}
	}

	if (!conn->sess->sess_ops->DataPDUInOrder) {
		cmd->seq_no = seq_no;
		cmd->pdu_start = pdu_start;
		cmd->pdu_send_order = data_sn_count;
	}

	return 0;
}