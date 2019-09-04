#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int invoke_id; } ;
struct TYPE_6__ {TYPE_2__ ni1; } ;
struct l3_process {int callref; struct l3_process* next; TYPE_3__ prot; } ;
struct TYPE_4__ {struct l3_process* proc; } ;
struct PStack {TYPE_1__ l3; } ;

/* Variables and functions */

__attribute__((used)) static struct l3_process *
l3ni1_search_dummy_proc(struct PStack *st, int id)
{ struct l3_process *pc = st->l3.proc; /* start of processes */

	if (!id) return (NULL);

	while (pc)
	{ if ((pc->callref == -1) && (pc->prot.ni1.invoke_id == id))
			return (pc);
		pc = pc->next;
	}
	return (NULL);
}