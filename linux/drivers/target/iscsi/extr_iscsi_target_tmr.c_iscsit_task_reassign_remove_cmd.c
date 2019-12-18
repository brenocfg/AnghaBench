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
struct iscsi_session {int /*<<< orphan*/  sid; } ;
struct iscsi_conn_recovery {int /*<<< orphan*/  cid; int /*<<< orphan*/  conn_recovery_cmd_lock; } ;
struct iscsi_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsit_remove_active_connection_recovery_entry (struct iscsi_conn_recovery*,struct iscsi_session*) ; 
 int iscsit_remove_cmd_from_connection_recovery (struct iscsi_cmd*,struct iscsi_session*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iscsit_task_reassign_remove_cmd(
	struct iscsi_cmd *cmd,
	struct iscsi_conn_recovery *cr,
	struct iscsi_session *sess)
{
	int ret;

	spin_lock(&cr->conn_recovery_cmd_lock);
	ret = iscsit_remove_cmd_from_connection_recovery(cmd, sess);
	spin_unlock(&cr->conn_recovery_cmd_lock);
	if (!ret) {
		pr_debug("iSCSI connection recovery successful for CID:"
			" %hu on SID: %u\n", cr->cid, sess->sid);
		iscsit_remove_active_connection_recovery_entry(cr, sess);
	}
}