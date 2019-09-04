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
struct layer1 {int /*<<< orphan*/  dch; int /*<<< orphan*/  (* dcb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  Flags; int /*<<< orphan*/  t3_value; int /*<<< orphan*/  timer3; } ;
struct FsmInst {struct layer1* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_TIMER3 ; 
 int /*<<< orphan*/  FLG_L1_T3RUN ; 
 int /*<<< orphan*/  HW_RESET_REQ ; 
 int /*<<< orphan*/  mISDN_FsmRestartTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l1_activate_s(struct FsmInst *fi, int event, void *arg)
{
	struct layer1 *l1 = fi->userdata;

	mISDN_FsmRestartTimer(&l1->timer3, l1->t3_value, EV_TIMER3, NULL, 2);
	test_and_set_bit(FLG_L1_T3RUN, &l1->Flags);
	/* Tell HW to send INFO 1 */
	l1->dcb(l1->dch, HW_RESET_REQ);
}