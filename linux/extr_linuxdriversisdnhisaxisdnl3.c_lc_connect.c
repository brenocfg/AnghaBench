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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  l3m; scalar_t__ debug; int /*<<< orphan*/  proc; int /*<<< orphan*/  (* l3l2 ) (struct PStack*,int,struct sk_buff*) ;int /*<<< orphan*/  squeue; } ;
struct PStack {TYPE_1__ l3; } ;
struct FsmInst {struct PStack* userdata; } ;

/* Variables and functions */
 int DL_DATA ; 
 int DL_ESTABLISH ; 
 int /*<<< orphan*/  EV_RELEASE_REQ ; 
 int /*<<< orphan*/  FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsmEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int INDICATION ; 
 int REQUEST ; 
 int /*<<< orphan*/  ST_L3_LC_ESTAB ; 
 int /*<<< orphan*/  l3_debug (struct PStack*,char*) ; 
 int /*<<< orphan*/  l3ml3p (struct PStack*,int) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct PStack*,int,struct sk_buff*) ; 

__attribute__((used)) static void
lc_connect(struct FsmInst *fi, int event, void *arg)
{
	struct PStack *st = fi->userdata;
	struct sk_buff *skb = arg;
	int dequeued = 0;

	FsmChangeState(fi, ST_L3_LC_ESTAB);
	while ((skb = skb_dequeue(&st->l3.squeue))) {
		st->l3.l3l2(st, DL_DATA | REQUEST, skb);
		dequeued++;
	}
	if ((!st->l3.proc) &&  dequeued) {
		if (st->l3.debug)
			l3_debug(st, "lc_connect: release link");
		FsmEvent(&st->l3.l3m, EV_RELEASE_REQ, NULL);
	} else
		l3ml3p(st, DL_ESTABLISH | INDICATION);
}