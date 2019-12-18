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
struct layer1 {int /*<<< orphan*/  Flags; int /*<<< orphan*/  timerX; int /*<<< orphan*/  timer3; int /*<<< orphan*/  dch; int /*<<< orphan*/  (* dcb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct FsmInst {struct layer1* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_TIMER_ACT ; 
 int /*<<< orphan*/  FLG_L1_ACTIVATED ; 
 int /*<<< orphan*/  FLG_L1_ACTTIMER ; 
 int /*<<< orphan*/  FLG_L1_DEACTTIMER ; 
 int /*<<< orphan*/  FLG_L1_T3RUN ; 
 int /*<<< orphan*/  INFO3_P8 ; 
 int /*<<< orphan*/  ST_L1_F7 ; 
 int /*<<< orphan*/  mISDN_FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mISDN_FsmDelTimer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mISDN_FsmRestartTimer (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l1_info4_ind(struct FsmInst *fi, int event, void *arg)
{
	struct layer1 *l1 = fi->userdata;

	mISDN_FsmChangeState(fi, ST_L1_F7);
	l1->dcb(l1->dch, INFO3_P8);
	if (test_and_clear_bit(FLG_L1_DEACTTIMER, &l1->Flags))
		mISDN_FsmDelTimer(&l1->timerX, 4);
	if (!test_bit(FLG_L1_ACTIVATED, &l1->Flags)) {
		if (test_and_clear_bit(FLG_L1_T3RUN, &l1->Flags))
			mISDN_FsmDelTimer(&l1->timer3, 3);
		mISDN_FsmRestartTimer(&l1->timerX, 110, EV_TIMER_ACT, NULL, 2);
		test_and_set_bit(FLG_L1_ACTTIMER, &l1->Flags);
	}
}