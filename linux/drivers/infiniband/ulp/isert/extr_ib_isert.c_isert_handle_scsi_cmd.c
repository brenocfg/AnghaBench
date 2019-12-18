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
struct isert_conn {struct iscsi_conn* conn; } ;
struct isert_cmd {int /*<<< orphan*/  sg; } ;
struct iser_rx_desc {int /*<<< orphan*/ * data; } ;
struct iscsi_scsi_req {int /*<<< orphan*/  cmdsn; } ;
struct iscsi_conn {int dummy; } ;
struct TYPE_2__ {unsigned int data_length; int t_data_nents; int /*<<< orphan*/ * t_data_sg; int /*<<< orphan*/  se_cmd_flags; } ;
struct iscsi_cmd {int immediate_data; int first_burst_len; int unsolicited_data; unsigned int write_data_done; TYPE_1__ se_cmd; int /*<<< orphan*/  istate_lock; int /*<<< orphan*/  i_state; int /*<<< orphan*/  cmd_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICF_GOT_LAST_DATAOUT ; 
 int /*<<< orphan*/  ISTATE_RECEIVED_LAST_DATAOUT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SCF_PASSTHROUGH_SG_TO_MEM_NOALLOC ; 
 int iscsit_process_scsi_cmd (struct iscsi_conn*,struct iscsi_cmd*,struct iscsi_scsi_req*) ; 
 int iscsit_sequence_cmd (struct iscsi_conn*,struct iscsi_cmd*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_set_unsolicited_dataout (struct iscsi_cmd*) ; 
 int iscsit_setup_scsi_cmd (struct iscsi_conn*,struct iscsi_cmd*,unsigned char*) ; 
 int /*<<< orphan*/  isert_dbg (char*,int,...) ; 
 int max (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_copy_from_buffer (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sg_set_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_put_sess_cmd (TYPE_1__*) ; 

__attribute__((used)) static int
isert_handle_scsi_cmd(struct isert_conn *isert_conn,
		      struct isert_cmd *isert_cmd, struct iscsi_cmd *cmd,
		      struct iser_rx_desc *rx_desc, unsigned char *buf)
{
	struct iscsi_conn *conn = isert_conn->conn;
	struct iscsi_scsi_req *hdr = (struct iscsi_scsi_req *)buf;
	int imm_data, imm_data_len, unsol_data, sg_nents, rc;
	bool dump_payload = false;
	unsigned int data_len;

	rc = iscsit_setup_scsi_cmd(conn, cmd, buf);
	if (rc < 0)
		return rc;

	imm_data = cmd->immediate_data;
	imm_data_len = cmd->first_burst_len;
	unsol_data = cmd->unsolicited_data;
	data_len = cmd->se_cmd.data_length;

	if (imm_data && imm_data_len == data_len)
		cmd->se_cmd.se_cmd_flags |= SCF_PASSTHROUGH_SG_TO_MEM_NOALLOC;
	rc = iscsit_process_scsi_cmd(conn, cmd, hdr);
	if (rc < 0) {
		return 0;
	} else if (rc > 0) {
		dump_payload = true;
		goto sequence_cmd;
	}

	if (!imm_data)
		return 0;

	if (imm_data_len != data_len) {
		sg_nents = max(1UL, DIV_ROUND_UP(imm_data_len, PAGE_SIZE));
		sg_copy_from_buffer(cmd->se_cmd.t_data_sg, sg_nents,
				    &rx_desc->data[0], imm_data_len);
		isert_dbg("Copy Immediate sg_nents: %u imm_data_len: %d\n",
			  sg_nents, imm_data_len);
	} else {
		sg_init_table(&isert_cmd->sg, 1);
		cmd->se_cmd.t_data_sg = &isert_cmd->sg;
		cmd->se_cmd.t_data_nents = 1;
		sg_set_buf(&isert_cmd->sg, &rx_desc->data[0], imm_data_len);
		isert_dbg("Transfer Immediate imm_data_len: %d\n",
			  imm_data_len);
	}

	cmd->write_data_done += imm_data_len;

	if (cmd->write_data_done == cmd->se_cmd.data_length) {
		spin_lock_bh(&cmd->istate_lock);
		cmd->cmd_flags |= ICF_GOT_LAST_DATAOUT;
		cmd->i_state = ISTATE_RECEIVED_LAST_DATAOUT;
		spin_unlock_bh(&cmd->istate_lock);
	}

sequence_cmd:
	rc = iscsit_sequence_cmd(conn, cmd, buf, hdr->cmdsn);

	if (!rc && dump_payload == false && unsol_data)
		iscsit_set_unsolicited_dataout(cmd);
	else if (dump_payload && imm_data)
		target_put_sess_cmd(&cmd->se_cmd);

	return 0;
}