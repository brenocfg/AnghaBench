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
struct TYPE_2__ {int /*<<< orphan*/  squeue; int /*<<< orphan*/  l3m_timer; int /*<<< orphan*/ * global; scalar_t__ proc; } ;
struct PStack {TYPE_1__ l3; } ;

/* Variables and functions */
 int /*<<< orphan*/  FsmDelTimer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  StopAllL3Timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_l3_process (scalar_t__) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

void
releasestack_isdnl3(struct PStack *st)
{
	while (st->l3.proc)
		release_l3_process(st->l3.proc);
	if (st->l3.global) {
		StopAllL3Timer(st->l3.global);
		kfree(st->l3.global);
		st->l3.global = NULL;
	}
	FsmDelTimer(&st->l3.l3m_timer, 54);
	skb_queue_purge(&st->l3.squeue);
}