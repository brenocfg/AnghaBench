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
struct iscsi_tmr_req {int dummy; } ;
struct iscsi_session {TYPE_2__* se_sess; } ;
struct iscsi_node_attrib {int /*<<< orphan*/  tmr_warm_reset; } ;
struct iscsi_conn {struct iscsi_session* sess; } ;
struct TYPE_4__ {TYPE_1__* se_node_acl; } ;
struct TYPE_3__ {int /*<<< orphan*/  initiatorname; } ;

/* Variables and functions */
 struct iscsi_node_attrib* iscsit_tpg_get_node_attrib (struct iscsi_session*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

int iscsit_tmr_task_warm_reset(
	struct iscsi_conn *conn,
	struct iscsi_tmr_req *tmr_req,
	unsigned char *buf)
{
	struct iscsi_session *sess = conn->sess;
	struct iscsi_node_attrib *na = iscsit_tpg_get_node_attrib(sess);

	if (!na->tmr_warm_reset) {
		pr_err("TMR Opcode TARGET_WARM_RESET authorization"
			" failed for Initiator Node: %s\n",
			sess->se_sess->se_node_acl->initiatorname);
		return -1;
	}
	/*
	 * Do the real work in transport_generic_do_tmr().
	 */
	return 0;
}