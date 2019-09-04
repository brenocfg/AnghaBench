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
struct bfa_msgq_cmdq {struct bfa_msgq* msgq; int /*<<< orphan*/  pending_q; int /*<<< orphan*/  depth; } ;
struct bfa_msgq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_MSGQ_CMDQ_NUM_ENTRY ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bfa_msgq_cmdq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdq_sm_stopped ; 

__attribute__((used)) static void
bfa_msgq_cmdq_attach(struct bfa_msgq_cmdq *cmdq, struct bfa_msgq *msgq)
{
	cmdq->depth = BFA_MSGQ_CMDQ_NUM_ENTRY;
	INIT_LIST_HEAD(&cmdq->pending_q);
	cmdq->msgq = msgq;
	bfa_fsm_set_state(cmdq, cmdq_sm_stopped);
}