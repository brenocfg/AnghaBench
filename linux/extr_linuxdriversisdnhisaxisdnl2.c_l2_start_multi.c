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
struct TYPE_2__ {int /*<<< orphan*/  (* l2l3 ) (struct PStack*,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  T203; int /*<<< orphan*/  t203; scalar_t__ sow; scalar_t__ vr; scalar_t__ va; scalar_t__ vs; } ;
struct PStack {TYPE_1__ l2; } ;
struct FsmInst {struct PStack* userdata; } ;

/* Variables and functions */
 int DL_ESTABLISH ; 
 int /*<<< orphan*/  EV_L2_T203 ; 
 int /*<<< orphan*/  FsmAddTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int INDICATION ; 
 int /*<<< orphan*/  RSP ; 
 int /*<<< orphan*/  ST_L2_7 ; 
 int UA ; 
 int /*<<< orphan*/  clear_exception (TYPE_1__*) ; 
 int get_PollFlagFree (struct PStack*,struct sk_buff*) ; 
 int /*<<< orphan*/  send_uframe (struct PStack*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct PStack*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l2_start_multi(struct FsmInst *fi, int event, void *arg)
{
	struct PStack *st = fi->userdata;
	struct sk_buff *skb = arg;

	send_uframe(st, UA | get_PollFlagFree(st, skb), RSP);

	clear_exception(&st->l2);
	st->l2.vs = 0;
	st->l2.va = 0;
	st->l2.vr = 0;
	st->l2.sow = 0;
	FsmChangeState(fi, ST_L2_7);
	FsmAddTimer(&st->l2.t203, st->l2.T203, EV_L2_T203, NULL, 3);

	st->l2.l2l3(st, DL_ESTABLISH | INDICATION, NULL);
}