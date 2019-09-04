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
struct TYPE_2__ {int msg_id; } ;
struct bfi_mbmsg {TYPE_1__ mh; } ;
struct bfa_msgq {int /*<<< orphan*/  cmdq; int /*<<< orphan*/  rspq; } ;

/* Variables and functions */
#define  BFI_MSGQ_I2H_CMDQ_COPY_REQ 131 
#define  BFI_MSGQ_I2H_DOORBELL_CI 130 
#define  BFI_MSGQ_I2H_DOORBELL_PI 129 
#define  BFI_MSGQ_I2H_INIT_RSP 128 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  bfa_msgq_cmdq_ci_update (int /*<<< orphan*/ *,struct bfi_mbmsg*) ; 
 int /*<<< orphan*/  bfa_msgq_cmdq_copy_req (int /*<<< orphan*/ *,struct bfi_mbmsg*) ; 
 int /*<<< orphan*/  bfa_msgq_init_rsp (struct bfa_msgq*,struct bfi_mbmsg*) ; 
 int /*<<< orphan*/  bfa_msgq_rspq_pi_update (int /*<<< orphan*/ *,struct bfi_mbmsg*) ; 

__attribute__((used)) static void
bfa_msgq_isr(void *cbarg, struct bfi_mbmsg *msg)
{
	struct bfa_msgq *msgq = (struct bfa_msgq *)cbarg;

	switch (msg->mh.msg_id) {
	case BFI_MSGQ_I2H_INIT_RSP:
		bfa_msgq_init_rsp(msgq, msg);
		break;

	case BFI_MSGQ_I2H_DOORBELL_PI:
		bfa_msgq_rspq_pi_update(&msgq->rspq, msg);
		break;

	case BFI_MSGQ_I2H_DOORBELL_CI:
		bfa_msgq_cmdq_ci_update(&msgq->cmdq, msg);
		break;

	case BFI_MSGQ_I2H_CMDQ_COPY_REQ:
		bfa_msgq_cmdq_copy_req(&msgq->cmdq, msg);
		break;

	default:
		BUG_ON(1);
	}
}