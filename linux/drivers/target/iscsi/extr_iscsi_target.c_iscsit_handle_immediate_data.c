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
typedef  int u32 ;
struct kvec {int* iov_base; int iov_len; } ;
struct iscsi_scsi_req {int dummy; } ;
struct iscsi_conn {TYPE_3__* sess; int /*<<< orphan*/  conn_rx_hash; TYPE_1__* conn_ops; } ;
struct TYPE_8__ {scalar_t__ data_length; } ;
struct iscsi_cmd {scalar_t__ write_data_done; int orig_iov_data_count; int* pad_bytes; int /*<<< orphan*/  istate_lock; int /*<<< orphan*/  i_state; int /*<<< orphan*/  cmd_flags; TYPE_4__ se_cmd; struct kvec* iov_data; void* overflow_buf; struct iscsi_conn* conn; } ;
struct TYPE_7__ {TYPE_2__* sess_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  ErrorRecoveryLevel; } ;
struct TYPE_5__ {scalar_t__ DataDigest; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ICF_GOT_LAST_DATAOUT ; 
 int IMMEDIATE_DATA_CANNOT_RECOVER ; 
 int IMMEDIATE_DATA_ERL1_CRC_FAILURE ; 
 int IMMEDIATE_DATA_NORMAL_OPERATION ; 
 int ISCSI_CRC_LEN ; 
 int /*<<< orphan*/  ISCSI_REASON_DATA_DIGEST_ERROR ; 
 int /*<<< orphan*/  ISTATE_RECEIVED_LAST_DATAOUT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int iscsit_do_crypto_hash_sg (int /*<<< orphan*/ ,struct iscsi_cmd*,scalar_t__,int,int,int*) ; 
 int iscsit_map_iovec (struct iscsi_cmd*,struct kvec*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  iscsit_reject_cmd (struct iscsi_cmd*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  iscsit_rx_thread_wait_for_tcp (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsit_unmap_iovec (struct iscsi_cmd*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int min (scalar_t__,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int rx_data (struct iscsi_conn*,struct kvec*,int,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iscsit_handle_immediate_data(
	struct iscsi_cmd *cmd,
	struct iscsi_scsi_req *hdr,
	u32 length)
{
	int iov_ret, rx_got = 0, rx_size = 0;
	u32 checksum, iov_count = 0, padding = 0;
	struct iscsi_conn *conn = cmd->conn;
	struct kvec *iov;
	void *overflow_buf = NULL;

	BUG_ON(cmd->write_data_done > cmd->se_cmd.data_length);
	rx_size = min(cmd->se_cmd.data_length - cmd->write_data_done, length);
	iov_ret = iscsit_map_iovec(cmd, cmd->iov_data,
				   cmd->orig_iov_data_count - 2,
				   cmd->write_data_done, rx_size);
	if (iov_ret < 0)
		return IMMEDIATE_DATA_CANNOT_RECOVER;

	iov_count = iov_ret;
	iov = &cmd->iov_data[0];
	if (rx_size < length) {
		/*
		 * Special case: length of immediate data exceeds the data
		 * buffer size derived from the CDB.
		 */
		overflow_buf = kmalloc(length - rx_size, GFP_KERNEL);
		if (!overflow_buf) {
			iscsit_unmap_iovec(cmd);
			return IMMEDIATE_DATA_CANNOT_RECOVER;
		}
		cmd->overflow_buf = overflow_buf;
		iov[iov_count].iov_base = overflow_buf;
		iov[iov_count].iov_len = length - rx_size;
		iov_count++;
		rx_size = length;
	}

	padding = ((-length) & 3);
	if (padding != 0) {
		iov[iov_count].iov_base	= cmd->pad_bytes;
		iov[iov_count++].iov_len = padding;
		rx_size += padding;
	}

	if (conn->conn_ops->DataDigest) {
		iov[iov_count].iov_base		= &checksum;
		iov[iov_count++].iov_len	= ISCSI_CRC_LEN;
		rx_size += ISCSI_CRC_LEN;
	}

	WARN_ON_ONCE(iov_count > cmd->orig_iov_data_count);
	rx_got = rx_data(conn, &cmd->iov_data[0], iov_count, rx_size);

	iscsit_unmap_iovec(cmd);

	if (rx_got != rx_size) {
		iscsit_rx_thread_wait_for_tcp(conn);
		return IMMEDIATE_DATA_CANNOT_RECOVER;
	}

	if (conn->conn_ops->DataDigest) {
		u32 data_crc;

		data_crc = iscsit_do_crypto_hash_sg(conn->conn_rx_hash, cmd,
						    cmd->write_data_done, length, padding,
						    cmd->pad_bytes);

		if (checksum != data_crc) {
			pr_err("ImmediateData CRC32C DataDigest 0x%08x"
				" does not match computed 0x%08x\n", checksum,
				data_crc);

			if (!conn->sess->sess_ops->ErrorRecoveryLevel) {
				pr_err("Unable to recover from"
					" Immediate Data digest failure while"
					" in ERL=0.\n");
				iscsit_reject_cmd(cmd,
						ISCSI_REASON_DATA_DIGEST_ERROR,
						(unsigned char *)hdr);
				return IMMEDIATE_DATA_CANNOT_RECOVER;
			} else {
				iscsit_reject_cmd(cmd,
						ISCSI_REASON_DATA_DIGEST_ERROR,
						(unsigned char *)hdr);
				return IMMEDIATE_DATA_ERL1_CRC_FAILURE;
			}
		} else {
			pr_debug("Got CRC32C DataDigest 0x%08x for"
				" %u bytes of Immediate Data\n", checksum,
				length);
		}
	}

	cmd->write_data_done += length;

	if (cmd->write_data_done == cmd->se_cmd.data_length) {
		spin_lock_bh(&cmd->istate_lock);
		cmd->cmd_flags |= ICF_GOT_LAST_DATAOUT;
		cmd->i_state = ISTATE_RECEIVED_LAST_DATAOUT;
		spin_unlock_bh(&cmd->istate_lock);
	}

	return IMMEDIATE_DATA_NORMAL_OPERATION;
}