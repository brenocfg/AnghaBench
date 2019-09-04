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
struct l3_process {struct l3_process* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* l3ml3 ) (struct PStack*,int,struct l3_process*) ;struct l3_process* proc; } ;
struct PStack {TYPE_1__ l3; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct PStack*,int,struct l3_process*) ; 

__attribute__((used)) static void
l3ml3p(struct PStack *st, int pr)
{
	struct l3_process *p = st->l3.proc;
	struct l3_process *np;

	while (p) {
		/* p might be kfreed under us, so we need to save where we want to go on */
		np = p->next;
		st->l3.l3ml3(st, pr, p);
		p = np;
	}
}