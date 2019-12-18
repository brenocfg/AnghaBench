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
struct gasket_interrupt_data {int num_interrupts; TYPE_1__* msix_entries; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int vector; int entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  gasket_handle_interrupt (struct gasket_interrupt_data*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static irqreturn_t gasket_msix_interrupt_handler(int irq, void *dev_id)
{
	struct gasket_interrupt_data *interrupt_data = dev_id;
	int interrupt = -1;
	int i;

	/* If this linear lookup is a problem, we can maintain a map/hash. */
	for (i = 0; i < interrupt_data->num_interrupts; i++) {
		if (interrupt_data->msix_entries[i].vector == irq) {
			interrupt = interrupt_data->msix_entries[i].entry;
			break;
		}
	}
	if (interrupt == -1) {
		pr_err("Received unknown irq %d\n", irq);
		return IRQ_HANDLED;
	}
	gasket_handle_interrupt(interrupt_data, interrupt);
	return IRQ_HANDLED;
}