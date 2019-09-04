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
struct mvpp2_queue_vector {int /*<<< orphan*/  napi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  mvpp2_qvec_interrupt_disable (struct mvpp2_queue_vector*) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mvpp2_isr(int irq, void *dev_id)
{
	struct mvpp2_queue_vector *qv = dev_id;

	mvpp2_qvec_interrupt_disable(qv);

	napi_schedule(&qv->napi);

	return IRQ_HANDLED;
}