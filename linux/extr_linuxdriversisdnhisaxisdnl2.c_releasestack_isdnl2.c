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
struct TYPE_2__ {int /*<<< orphan*/  ui_queue; int /*<<< orphan*/  i_queue; int /*<<< orphan*/  t203; int /*<<< orphan*/  t200; } ;
struct PStack {TYPE_1__ l2; } ;

/* Variables and functions */
 int /*<<< orphan*/  FsmDelTimer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ReleaseWin (TYPE_1__*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

void
releasestack_isdnl2(struct PStack *st)
{
	FsmDelTimer(&st->l2.t200, 21);
	FsmDelTimer(&st->l2.t203, 16);
	skb_queue_purge(&st->l2.i_queue);
	skb_queue_purge(&st->l2.ui_queue);
	ReleaseWin(&st->l2);
}