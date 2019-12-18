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
struct TYPE_4__ {int /*<<< orphan*/  (* printdebug ) (struct FsmInst*,char*,int /*<<< orphan*/ ) ;} ;
struct teimgr {int nval; int /*<<< orphan*/  tval; int /*<<< orphan*/  timer; TYPE_2__ tei_m; TYPE_1__* l2; int /*<<< orphan*/  mgr; } ;
struct FsmInst {struct teimgr* userdata; } ;
struct TYPE_3__ {int /*<<< orphan*/  tei; } ;

/* Variables and functions */
 int DEBUG_L2_TEI ; 
 int /*<<< orphan*/  EV_TIMER ; 
 int /*<<< orphan*/  ID_VERIFY ; 
 int /*<<< orphan*/  ST_TEI_IDVERIFY ; 
 int* debug ; 
 int /*<<< orphan*/  mISDN_FsmAddTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mISDN_FsmChangeState (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_tei_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct FsmInst*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tei_id_verify(struct FsmInst *fi, int event, void *arg)
{
	struct teimgr *tm = fi->userdata;

	if (*debug & DEBUG_L2_TEI)
		tm->tei_m.printdebug(fi, "id verify request for tei %d",
				     tm->l2->tei);
	put_tei_msg(tm->mgr, ID_VERIFY, 0, tm->l2->tei);
	mISDN_FsmChangeState(&tm->tei_m, ST_TEI_IDVERIFY);
	mISDN_FsmAddTimer(&tm->timer, tm->tval, EV_TIMER, NULL, 2);
	tm->nval = 2;
}