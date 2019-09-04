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
struct timer_list {int dummy; } ;
struct FsmTimer {int /*<<< orphan*/  arg; int /*<<< orphan*/  event; int /*<<< orphan*/  fi; } ;

/* Variables and functions */
 int /*<<< orphan*/  FsmEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct FsmTimer* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct FsmTimer* ft ; 
 int /*<<< orphan*/  tl ; 

__attribute__((used)) static void
FsmExpireTimer(struct timer_list *t)
{
	struct FsmTimer *ft = from_timer(ft, t, tl);
#if FSM_TIMER_DEBUG
	if (ft->fi->debug)
		ft->fi->printdebug(ft->fi, "FsmExpireTimer %lx", (long) ft);
#endif
	FsmEvent(ft->fi, ft->event, ft->arg);
}