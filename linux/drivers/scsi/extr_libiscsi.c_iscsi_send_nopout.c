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
struct iscsi_task {int dummy; } ;
struct iscsi_nopout {int opcode; void* ttt; void* itt; int /*<<< orphan*/  lun; int /*<<< orphan*/  flags; } ;
struct iscsi_nopin {void* ttt; int /*<<< orphan*/  lun; } ;
struct iscsi_hdr {int dummy; } ;
struct iscsi_conn {int /*<<< orphan*/  last_ping; struct iscsi_task* ping_task; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  ISCSI_FLAG_CMD_FINAL ; 
 int ISCSI_OP_IMMEDIATE ; 
 int ISCSI_OP_NOOP_OUT ; 
 int /*<<< orphan*/  KERN_ERR ; 
 void* RESERVED_ITT ; 
 struct iscsi_task* __iscsi_conn_send_pdu (struct iscsi_conn*,struct iscsi_hdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_conn_printk (int /*<<< orphan*/ ,struct iscsi_conn*,char*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memset (struct iscsi_nopout*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int iscsi_send_nopout(struct iscsi_conn *conn, struct iscsi_nopin *rhdr)
{
        struct iscsi_nopout hdr;
	struct iscsi_task *task;

	if (!rhdr && conn->ping_task)
		return -EINVAL;

	memset(&hdr, 0, sizeof(struct iscsi_nopout));
	hdr.opcode = ISCSI_OP_NOOP_OUT | ISCSI_OP_IMMEDIATE;
	hdr.flags = ISCSI_FLAG_CMD_FINAL;

	if (rhdr) {
		hdr.lun = rhdr->lun;
		hdr.ttt = rhdr->ttt;
		hdr.itt = RESERVED_ITT;
	} else
		hdr.ttt = RESERVED_ITT;

	task = __iscsi_conn_send_pdu(conn, (struct iscsi_hdr *)&hdr, NULL, 0);
	if (!task) {
		iscsi_conn_printk(KERN_ERR, conn, "Could not send nopout\n");
		return -EIO;
	} else if (!rhdr) {
		/* only track our nops */
		conn->ping_task = task;
		conn->last_ping = jiffies;
	}

	return 0;
}