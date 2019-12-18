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
struct FsmTimer {int /*<<< orphan*/  tl; struct FsmInst* fi; } ;
struct FsmInst {int /*<<< orphan*/  (* printdebug ) (struct FsmInst*,char*,long) ;scalar_t__ debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  FsmExpireTimer ; 
 int /*<<< orphan*/  stub1 (struct FsmInst*,char*,long) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mISDN_FsmInitTimer(struct FsmInst *fi, struct FsmTimer *ft)
{
	ft->fi = fi;
#if FSM_TIMER_DEBUG
	if (ft->fi->debug)
		ft->fi->printdebug(ft->fi, "mISDN_FsmInitTimer %lx", (long) ft);
#endif
	timer_setup(&ft->tl, FsmExpireTimer, 0);
}