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
struct mvpp2_queue_vector {int /*<<< orphan*/  irq; int /*<<< orphan*/ * mask; } ;
struct mvpp2_port {int nqvecs; struct mvpp2_queue_vector* qvecs; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NO_BALANCING ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mvpp2_queue_vector*) ; 
 int /*<<< orphan*/  irq_clear_status_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mvpp2_irqs_deinit(struct mvpp2_port *port)
{
	int i;

	for (i = 0; i < port->nqvecs; i++) {
		struct mvpp2_queue_vector *qv = port->qvecs + i;

		irq_set_affinity_hint(qv->irq, NULL);
		kfree(qv->mask);
		qv->mask = NULL;
		irq_clear_status_flags(qv->irq, IRQ_NO_BALANCING);
		free_irq(qv->irq, qv);
	}
}