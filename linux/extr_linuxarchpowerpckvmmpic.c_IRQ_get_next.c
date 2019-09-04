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
struct openpic {int dummy; } ;
struct irq_queue {int next; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_check (struct openpic*,struct irq_queue*) ; 

__attribute__((used)) static int IRQ_get_next(struct openpic *opp, struct irq_queue *q)
{
	/* XXX: optimize */
	IRQ_check(opp, q);

	return q->next;
}