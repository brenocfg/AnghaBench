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
struct layer1 {int /*<<< orphan*/  Flags; int /*<<< orphan*/  timerX; } ;
struct FsmInst {struct layer1* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_TIMER_DEACT ; 
 int /*<<< orphan*/  FLG_L1_DEACTTIMER ; 
 int /*<<< orphan*/  ST_L1_F3 ; 
 int /*<<< orphan*/  mISDN_FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mISDN_FsmRestartTimer (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l1_deact_req_s(struct FsmInst *fi, int event, void *arg)
{
	struct layer1 *l1 = fi->userdata;

	mISDN_FsmChangeState(fi, ST_L1_F3);
	mISDN_FsmRestartTimer(&l1->timerX, 550, EV_TIMER_DEACT, NULL, 2);
	test_and_set_bit(FLG_L1_DEACTTIMER, &l1->Flags);
}