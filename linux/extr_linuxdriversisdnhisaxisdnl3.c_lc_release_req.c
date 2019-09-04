#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* l3l2 ) (struct PStack*,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  l3m_timer; scalar_t__ debug; } ;
struct TYPE_3__ {int /*<<< orphan*/  flag; } ;
struct PStack {TYPE_2__ l3; TYPE_1__ l2; } ;
struct FsmInst {struct PStack* userdata; } ;

/* Variables and functions */
 int DL_RELEASE ; 
 int /*<<< orphan*/  DREL_TIMER_VALUE ; 
 int /*<<< orphan*/  EV_TIMEOUT ; 
 int /*<<< orphan*/  FLG_L2BLOCK ; 
 int /*<<< orphan*/  FsmAddTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int REQUEST ; 
 int /*<<< orphan*/  ST_L3_LC_REL_WAIT ; 
 int /*<<< orphan*/  l3_debug (struct PStack*,char*) ; 
 int /*<<< orphan*/  stub1 (struct PStack*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lc_release_req(struct FsmInst *fi, int event, void *arg)
{
	struct PStack *st = fi->userdata;

	if (test_bit(FLG_L2BLOCK, &st->l2.flag)) {
		if (st->l3.debug)
			l3_debug(st, "lc_release_req: l2 blocked");
		/* restart release timer */
		FsmAddTimer(&st->l3.l3m_timer, DREL_TIMER_VALUE, EV_TIMEOUT, NULL, 51);
	} else {
		FsmChangeState(fi, ST_L3_LC_REL_WAIT);
		st->l3.l3l2(st, DL_RELEASE | REQUEST, NULL);
	}
}