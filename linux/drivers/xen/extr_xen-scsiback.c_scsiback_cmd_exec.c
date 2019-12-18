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
struct se_cmd {int /*<<< orphan*/  tag; } ;
struct vscsibk_pend {int /*<<< orphan*/  n_sg; int /*<<< orphan*/  sgl; int /*<<< orphan*/  sc_data_direction; int /*<<< orphan*/  data_len; TYPE_3__* v2p; int /*<<< orphan*/  sense_buffer; int /*<<< orphan*/  cmnd; int /*<<< orphan*/  rqid; int /*<<< orphan*/  info; struct se_cmd se_cmd; } ;
struct se_session {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  lun; TYPE_2__* tpg; } ;
struct TYPE_5__ {TYPE_1__* tpg_nexus; } ;
struct TYPE_4__ {struct se_session* tvn_se_sess; } ;

/* Variables and functions */
 int /*<<< orphan*/  TARGET_SCF_ACK_KREF ; 
 int /*<<< orphan*/  TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE ; 
 int /*<<< orphan*/  scsiback_get (int /*<<< orphan*/ ) ; 
 int target_submit_cmd_map_sgls (struct se_cmd*,struct se_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transport_generic_free_cmd (struct se_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transport_send_check_condition_and_sense (struct se_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scsiback_cmd_exec(struct vscsibk_pend *pending_req)
{
	struct se_cmd *se_cmd = &pending_req->se_cmd;
	struct se_session *sess = pending_req->v2p->tpg->tpg_nexus->tvn_se_sess;
	int rc;

	scsiback_get(pending_req->info);
	se_cmd->tag = pending_req->rqid;
	rc = target_submit_cmd_map_sgls(se_cmd, sess, pending_req->cmnd,
			pending_req->sense_buffer, pending_req->v2p->lun,
			pending_req->data_len, 0,
			pending_req->sc_data_direction, TARGET_SCF_ACK_KREF,
			pending_req->sgl, pending_req->n_sg,
			NULL, 0, NULL, 0);
	if (rc < 0) {
		transport_send_check_condition_and_sense(se_cmd,
				TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE, 0);
		transport_generic_free_cmd(se_cmd, 0);
	}
}