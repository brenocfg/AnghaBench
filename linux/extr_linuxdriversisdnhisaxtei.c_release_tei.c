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
struct TYPE_2__ {int /*<<< orphan*/  t202; } ;
struct PStack {struct PStack* next; TYPE_1__ ma; } ;
struct IsdnCardState {struct PStack* stlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  FsmDelTimer (int /*<<< orphan*/ *,int) ; 

void
release_tei(struct IsdnCardState *cs)
{
	struct PStack *st = cs->stlist;

	while (st) {
		FsmDelTimer(&st->ma.t202, 1);
		st = st->next;
	}
}