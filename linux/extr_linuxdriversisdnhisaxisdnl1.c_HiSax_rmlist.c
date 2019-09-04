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
struct TYPE_2__ {int /*<<< orphan*/  timer; } ;
struct PStack {struct PStack* next; TYPE_1__ l1; } ;
struct IsdnCardState {struct PStack* stlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  FsmDelTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
HiSax_rmlist(struct IsdnCardState *cs,
	     struct PStack *st)
{
	struct PStack *p;

	FsmDelTimer(&st->l1.timer, 0);
	if (cs->stlist == st)
		cs->stlist = st->next;
	else {
		p = cs->stlist;
		while (p)
			if (p->next == st) {
				p->next = st->next;
				return;
			} else
				p = p->next;
	}
}