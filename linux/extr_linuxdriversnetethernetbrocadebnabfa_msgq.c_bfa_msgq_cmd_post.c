#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bfa_msgq_cmd_entry {int /*<<< orphan*/  qe; TYPE_1__* msg_hdr; } ;
struct TYPE_6__ {int /*<<< orphan*/  pending_q; } ;
struct bfa_msgq {TYPE_2__ cmdq; } ;
struct TYPE_5__ {int /*<<< orphan*/  num_entries; } ;

/* Variables and functions */
 scalar_t__ BFA_MSGQ_FREE_CNT (TYPE_2__*) ; 
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int /*<<< orphan*/  CMDQ_E_POST ; 
 int /*<<< orphan*/  __cmd_copy (TYPE_2__*,struct bfa_msgq_cmd_entry*) ; 
 int /*<<< orphan*/  bfa_fsm_send_event (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_cmdq_ent_cbfn (struct bfa_msgq_cmd_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

void
bfa_msgq_cmd_post(struct bfa_msgq *msgq,  struct bfa_msgq_cmd_entry *cmd)
{
	if (ntohs(cmd->msg_hdr->num_entries) <=
		BFA_MSGQ_FREE_CNT(&msgq->cmdq)) {
		__cmd_copy(&msgq->cmdq, cmd);
		call_cmdq_ent_cbfn(cmd, BFA_STATUS_OK);
		bfa_fsm_send_event(&msgq->cmdq, CMDQ_E_POST);
	} else {
		list_add_tail(&cmd->qe, &msgq->cmdq.pending_q);
	}
}