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
typedef  int u32 ;
struct lan743x_vector {int flags; int vector_index; int int_mask; int /*<<< orphan*/ * context; int /*<<< orphan*/ * handler; int /*<<< orphan*/  irq; struct lan743x_adapter* adapter; } ;
struct TYPE_2__ {struct lan743x_vector* vector_list; } ;
struct lan743x_adapter {TYPE_1__ intr; } ;
typedef  int /*<<< orphan*/ * lan743x_vector_handler ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int LAN743X_VECTOR_FLAG_IRQ_SHARED ; 
 int /*<<< orphan*/  lan743x_intr_entry_isr ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lan743x_vector*) ; 

__attribute__((used)) static int lan743x_intr_register_isr(struct lan743x_adapter *adapter,
				     int vector_index, u32 flags,
				     u32 int_mask,
				     lan743x_vector_handler handler,
				     void *context)
{
	struct lan743x_vector *vector = &adapter->intr.vector_list
					[vector_index];
	int ret;

	vector->adapter = adapter;
	vector->flags = flags;
	vector->vector_index = vector_index;
	vector->int_mask = int_mask;
	vector->handler = handler;
	vector->context = context;

	ret = request_irq(vector->irq,
			  lan743x_intr_entry_isr,
			  (flags & LAN743X_VECTOR_FLAG_IRQ_SHARED) ?
			  IRQF_SHARED : 0, DRIVER_NAME, vector);
	if (ret) {
		vector->handler = NULL;
		vector->context = NULL;
		vector->int_mask = 0;
		vector->flags = 0;
	}
	return ret;
}