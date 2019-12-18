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
typedef  int u32 ;
struct kvec {unsigned char* iov_base; int iov_len; } ;
struct iscsi_nopout {scalar_t__ ttt; unsigned char* cmdsn; int /*<<< orphan*/  dlength; } ;
struct iscsi_conn {TYPE_3__* sess; int /*<<< orphan*/  conn_rx_hash; TYPE_1__* conn_ops; } ;
struct iscsi_cmd {unsigned char pad_bytes; unsigned char* buf_ptr; int buf_ptr_size; struct kvec* iov_misc; } ;
struct TYPE_6__ {TYPE_2__* sess_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  ErrorRecoveryLevel; } ;
struct TYPE_4__ {scalar_t__ DataDigest; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct kvec*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ISCSI_CRC_LEN ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ cpu_to_be32 (int) ; 
 int /*<<< orphan*/  iscsit_do_crypto_hash_buf (int /*<<< orphan*/ ,unsigned char*,int,int,unsigned char,int*) ; 
 int /*<<< orphan*/  iscsit_free_cmd (struct iscsi_cmd*,int) ; 
 int iscsit_process_nop_out (struct iscsi_conn*,struct iscsi_cmd*,struct iscsi_nopout*) ; 
 int iscsit_setup_nop_out (struct iscsi_conn*,struct iscsi_cmd*,struct iscsi_nopout*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ntoh24 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int rx_data (struct iscsi_conn*,struct kvec*,int,int) ; 

__attribute__((used)) static int iscsit_handle_nop_out(struct iscsi_conn *conn, struct iscsi_cmd *cmd,
				 unsigned char *buf)
{
	unsigned char *ping_data = NULL;
	struct iscsi_nopout *hdr = (struct iscsi_nopout *)buf;
	struct kvec *iov = NULL;
	u32 payload_length = ntoh24(hdr->dlength);
	int ret;

	ret = iscsit_setup_nop_out(conn, cmd, hdr);
	if (ret < 0)
		return 0;
	/*
	 * Handle NOP-OUT payload for traditional iSCSI sockets
	 */
	if (payload_length && hdr->ttt == cpu_to_be32(0xFFFFFFFF)) {
		u32 checksum, data_crc, padding = 0;
		int niov = 0, rx_got, rx_size = payload_length;

		ping_data = kzalloc(payload_length + 1, GFP_KERNEL);
		if (!ping_data) {
			ret = -1;
			goto out;
		}

		iov = &cmd->iov_misc[0];
		iov[niov].iov_base	= ping_data;
		iov[niov++].iov_len	= payload_length;

		padding = ((-payload_length) & 3);
		if (padding != 0) {
			pr_debug("Receiving %u additional bytes"
				" for padding.\n", padding);
			iov[niov].iov_base	= &cmd->pad_bytes;
			iov[niov++].iov_len	= padding;
			rx_size += padding;
		}
		if (conn->conn_ops->DataDigest) {
			iov[niov].iov_base	= &checksum;
			iov[niov++].iov_len	= ISCSI_CRC_LEN;
			rx_size += ISCSI_CRC_LEN;
		}

		WARN_ON_ONCE(niov > ARRAY_SIZE(cmd->iov_misc));
		rx_got = rx_data(conn, &cmd->iov_misc[0], niov, rx_size);
		if (rx_got != rx_size) {
			ret = -1;
			goto out;
		}

		if (conn->conn_ops->DataDigest) {
			iscsit_do_crypto_hash_buf(conn->conn_rx_hash, ping_data,
						  payload_length, padding,
						  cmd->pad_bytes, &data_crc);

			if (checksum != data_crc) {
				pr_err("Ping data CRC32C DataDigest"
				" 0x%08x does not match computed 0x%08x\n",
					checksum, data_crc);
				if (!conn->sess->sess_ops->ErrorRecoveryLevel) {
					pr_err("Unable to recover from"
					" NOPOUT Ping DataCRC failure while in"
						" ERL=0.\n");
					ret = -1;
					goto out;
				} else {
					/*
					 * Silently drop this PDU and let the
					 * initiator plug the CmdSN gap.
					 */
					pr_debug("Dropping NOPOUT"
					" Command CmdSN: 0x%08x due to"
					" DataCRC error.\n", hdr->cmdsn);
					ret = 0;
					goto out;
				}
			} else {
				pr_debug("Got CRC32C DataDigest"
				" 0x%08x for %u bytes of ping data.\n",
					checksum, payload_length);
			}
		}

		ping_data[payload_length] = '\0';
		/*
		 * Attach ping data to struct iscsi_cmd->buf_ptr.
		 */
		cmd->buf_ptr = ping_data;
		cmd->buf_ptr_size = payload_length;

		pr_debug("Got %u bytes of NOPOUT ping"
			" data.\n", payload_length);
		pr_debug("Ping Data: \"%s\"\n", ping_data);
	}

	return iscsit_process_nop_out(conn, cmd, hdr);
out:
	if (cmd)
		iscsit_free_cmd(cmd, false);

	kfree(ping_data);
	return ret;
}