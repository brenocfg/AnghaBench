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
typedef  scalar_t__ u32 ;
struct isert_conn {struct iscsi_conn* conn; } ;
struct isert_cmd {int dummy; } ;
struct iser_rx_desc {int /*<<< orphan*/ * data; } ;
struct iscsi_text {int /*<<< orphan*/  dlength; } ;
struct iscsi_conn {int dummy; } ;
struct iscsi_cmd {unsigned char* text_in_ptr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int iscsit_process_text_cmd (struct iscsi_conn*,struct iscsi_cmd*,struct iscsi_text*) ; 
 int iscsit_setup_text_cmd (struct iscsi_conn*,struct iscsi_cmd*,struct iscsi_text*) ; 
 unsigned char* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ntoh24 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
isert_handle_text_cmd(struct isert_conn *isert_conn, struct isert_cmd *isert_cmd,
		      struct iscsi_cmd *cmd, struct iser_rx_desc *rx_desc,
		      struct iscsi_text *hdr)
{
	struct iscsi_conn *conn = isert_conn->conn;
	u32 payload_length = ntoh24(hdr->dlength);
	int rc;
	unsigned char *text_in = NULL;

	rc = iscsit_setup_text_cmd(conn, cmd, hdr);
	if (rc < 0)
		return rc;

	if (payload_length) {
		text_in = kzalloc(payload_length, GFP_KERNEL);
		if (!text_in)
			return -ENOMEM;
	}
	cmd->text_in_ptr = text_in;

	memcpy(cmd->text_in_ptr, &rx_desc->data[0], payload_length);

	return iscsit_process_text_cmd(conn, cmd, hdr);
}