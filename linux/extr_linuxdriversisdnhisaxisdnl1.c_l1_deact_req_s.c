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
struct TYPE_2__ {int /*<<< orphan*/  Flags; int /*<<< orphan*/  timer; } ;
struct PStack {TYPE_1__ l1; } ;
struct FsmInst {struct PStack* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_TIMER_DEACT ; 
 int /*<<< orphan*/  FLG_L1_DEACTTIMER ; 
 int /*<<< orphan*/  FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsmRestartTimer (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST_L1_F3 ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l1_deact_req_s(struct FsmInst *fi, int event, void *arg)
{
	struct PStack *st = fi->userdata;

	FsmChangeState(fi, ST_L1_F3);
	FsmRestartTimer(&st->l1.timer, 550, EV_TIMER_DEACT, NULL, 2);
	test_and_set_bit(FLG_L1_DEACTTIMER, &st->l1.Flags);
}