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
struct sl {TYPE_3__* element; } ;
struct TYPE_5__ {int /*<<< orphan*/ * val; } ;
struct qdio_q {scalar_t__* sbal; struct sl* sl; TYPE_2__ slsb; TYPE_1__* slib; scalar_t__ is_input_q; } ;
struct qdio_irq {struct qdio_q** output_qs; struct qdio_q** input_qs; } ;
struct qdio_buffer {int dummy; } ;
struct TYPE_6__ {unsigned long sbal; } ;
struct TYPE_4__ {unsigned long nsliba; unsigned long sla; unsigned long slsba; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_HEX (struct qdio_q**,int) ; 
 int PAGE_SIZE ; 
 int QDIO_MAX_BUFFERS_PER_Q ; 

__attribute__((used)) static void setup_storage_lists(struct qdio_q *q, struct qdio_irq *irq_ptr,
				struct qdio_buffer **sbals_array, int i)
{
	struct qdio_q *prev;
	int j;

	DBF_HEX(&q, sizeof(void *));
	q->sl = (struct sl *)((char *)q->slib + PAGE_SIZE / 2);

	/* fill in sbal */
	for (j = 0; j < QDIO_MAX_BUFFERS_PER_Q; j++)
		q->sbal[j] = *sbals_array++;

	/* fill in slib */
	if (i > 0) {
		prev = (q->is_input_q) ? irq_ptr->input_qs[i - 1]
			: irq_ptr->output_qs[i - 1];
		prev->slib->nsliba = (unsigned long)q->slib;
	}

	q->slib->sla = (unsigned long)q->sl;
	q->slib->slsba = (unsigned long)&q->slsb.val[0];

	/* fill in sl */
	for (j = 0; j < QDIO_MAX_BUFFERS_PER_Q; j++)
		q->sl->element[j].sbal = (unsigned long)q->sbal[j];
}