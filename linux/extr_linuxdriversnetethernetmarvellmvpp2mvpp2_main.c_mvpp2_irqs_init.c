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
struct mvpp2_queue_vector {scalar_t__ type; int /*<<< orphan*/  irq; int /*<<< orphan*/  sw_thread_id; } ;
struct mvpp2_port {int nqvecs; struct mvpp2_queue_vector* qvecs; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NO_BALANCING ; 
 scalar_t__ MVPP2_QUEUE_VECTOR_PRIVATE ; 
 int /*<<< orphan*/ * cpumask_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mvpp2_queue_vector*) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_status_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_isr ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mvpp2_queue_vector*) ; 

__attribute__((used)) static int mvpp2_irqs_init(struct mvpp2_port *port)
{
	int err, i;

	for (i = 0; i < port->nqvecs; i++) {
		struct mvpp2_queue_vector *qv = port->qvecs + i;

		if (qv->type == MVPP2_QUEUE_VECTOR_PRIVATE)
			irq_set_status_flags(qv->irq, IRQ_NO_BALANCING);

		err = request_irq(qv->irq, mvpp2_isr, 0, port->dev->name, qv);
		if (err)
			goto err;

		if (qv->type == MVPP2_QUEUE_VECTOR_PRIVATE)
			irq_set_affinity_hint(qv->irq,
					      cpumask_of(qv->sw_thread_id));
	}

	return 0;
err:
	for (i = 0; i < port->nqvecs; i++) {
		struct mvpp2_queue_vector *qv = port->qvecs + i;

		irq_set_affinity_hint(qv->irq, NULL);
		free_irq(qv->irq, qv);
	}

	return err;
}