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
struct gasket_interrupt_data {int num_configured; TYPE_1__* msix_entries; scalar_t__ msix_configured; int /*<<< orphan*/  pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct gasket_interrupt_data*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_disable_msix (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gasket_interrupt_msix_cleanup(struct gasket_interrupt_data *interrupt_data)
{
	int i;

	for (i = 0; i < interrupt_data->num_configured; i++)
		free_irq(interrupt_data->msix_entries[i].vector,
			 interrupt_data);
	interrupt_data->num_configured = 0;

	if (interrupt_data->msix_configured)
		pci_disable_msix(interrupt_data->pci_dev);
	interrupt_data->msix_configured = 0;
	kfree(interrupt_data->msix_entries);
}