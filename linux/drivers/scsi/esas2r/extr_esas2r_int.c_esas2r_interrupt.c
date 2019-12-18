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
struct esas2r_adapter {int /*<<< orphan*/  flags2; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF2_INT_PENDING ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  esas2r_adapter_interrupt_pending (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_schedule_tasklet (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

irqreturn_t esas2r_interrupt(int irq, void *dev_id)
{
	struct esas2r_adapter *a = (struct esas2r_adapter *)dev_id;

	if (!esas2r_adapter_interrupt_pending(a))
		return IRQ_NONE;

	set_bit(AF2_INT_PENDING, &a->flags2);
	esas2r_schedule_tasklet(a);

	return IRQ_HANDLED;
}