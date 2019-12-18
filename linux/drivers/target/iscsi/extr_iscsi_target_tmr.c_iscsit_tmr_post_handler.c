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
struct se_tmr_req {scalar_t__ response; } ;
struct iscsi_tmr_req {scalar_t__ task_reassign; } ;
struct iscsi_conn {int dummy; } ;
struct TYPE_2__ {struct se_tmr_req* se_tmr_req; } ;
struct iscsi_cmd {TYPE_1__ se_cmd; struct iscsi_tmr_req* tmr_req; } ;

/* Variables and functions */
 scalar_t__ ISCSI_TMF_RSP_COMPLETE ; 
 int iscsit_task_reassign_complete (struct iscsi_tmr_req*,struct iscsi_conn*) ; 

int iscsit_tmr_post_handler(struct iscsi_cmd *cmd, struct iscsi_conn *conn)
{
	struct iscsi_tmr_req *tmr_req = cmd->tmr_req;
	struct se_tmr_req *se_tmr = cmd->se_cmd.se_tmr_req;

	if (tmr_req->task_reassign &&
	   (se_tmr->response == ISCSI_TMF_RSP_COMPLETE))
		return iscsit_task_reassign_complete(tmr_req, conn);

	return 0;
}