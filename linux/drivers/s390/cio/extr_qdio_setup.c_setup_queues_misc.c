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
struct slib {int mask; int nr; int /*<<< orphan*/  entry; int /*<<< orphan*/ * handler; struct qdio_irq* irq_ptr; struct slib* slib; } ;
struct qdio_q {int mask; int nr; int /*<<< orphan*/  entry; int /*<<< orphan*/ * handler; struct qdio_irq* irq_ptr; struct qdio_q* slib; } ;
struct qdio_irq {int dummy; } ;
typedef  int /*<<< orphan*/  qdio_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  memset (struct slib*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void setup_queues_misc(struct qdio_q *q, struct qdio_irq *irq_ptr,
			      qdio_handler_t *handler, int i)
{
	struct slib *slib = q->slib;

	/* queue must be cleared for qdio_establish */
	memset(q, 0, sizeof(*q));
	memset(slib, 0, PAGE_SIZE);
	q->slib = slib;
	q->irq_ptr = irq_ptr;
	q->mask = 1 << (31 - i);
	q->nr = i;
	q->handler = handler;
	INIT_LIST_HEAD(&q->entry);
}