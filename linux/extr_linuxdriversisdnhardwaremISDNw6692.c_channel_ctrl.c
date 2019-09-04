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
struct TYPE_2__ {int /*<<< orphan*/  l1; } ;
struct w6692_hw {int /*<<< orphan*/  name; TYPE_1__ dch; } ;
struct mISDN_ctrl_req {int op; int p1; } ;

/* Variables and functions */
 int EINVAL ; 
 int HW_TIMER3_VALUE ; 
#define  MISDN_CTRL_GETOP 129 
#define  MISDN_CTRL_L1_TIMER3 128 
 int l1_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
channel_ctrl(struct w6692_hw *card, struct mISDN_ctrl_req *cq)
{
	int	ret = 0;

	switch (cq->op) {
	case MISDN_CTRL_GETOP:
		cq->op = MISDN_CTRL_L1_TIMER3;
		break;
	case MISDN_CTRL_L1_TIMER3:
		ret = l1_event(card->dch.l1, HW_TIMER3_VALUE | (cq->p1 & 0xff));
		break;
	default:
		pr_info("%s: unknown CTRL OP %x\n", card->name, cq->op);
		ret = -EINVAL;
		break;
	}
	return ret;
}