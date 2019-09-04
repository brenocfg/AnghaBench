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
struct bfi_mbmsg {int dummy; } ;
struct bfa_msgq {int /*<<< orphan*/  rspq; int /*<<< orphan*/  cmdq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMDQ_E_INIT_RESP ; 
 int /*<<< orphan*/  RSPQ_E_INIT_RESP ; 
 int /*<<< orphan*/  bfa_fsm_send_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_msgq_init_rsp(struct bfa_msgq *msgq,
		 struct bfi_mbmsg *mb)
{
	bfa_fsm_send_event(&msgq->cmdq, CMDQ_E_INIT_RESP);
	bfa_fsm_send_event(&msgq->rspq, RSPQ_E_INIT_RESP);
}