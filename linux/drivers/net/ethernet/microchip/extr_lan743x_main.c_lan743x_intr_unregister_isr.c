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
struct lan743x_vector {scalar_t__ flags; scalar_t__ int_mask; int /*<<< orphan*/ * context; int /*<<< orphan*/ * handler; int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {struct lan743x_vector* vector_list; } ;
struct lan743x_adapter {TYPE_1__ intr; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct lan743x_vector*) ; 

__attribute__((used)) static void lan743x_intr_unregister_isr(struct lan743x_adapter *adapter,
					int vector_index)
{
	struct lan743x_vector *vector = &adapter->intr.vector_list
					[vector_index];

	free_irq(vector->irq, vector);
	vector->handler = NULL;
	vector->context = NULL;
	vector->int_mask = 0;
	vector->flags = 0;
}