#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct megasas_instance {int msix_vectors; int msix_load_balance; struct pci_dev* pdev; TYPE_2__* irq_context; TYPE_1__* instancet; } ;
struct TYPE_5__ {int MSIxIndex; struct megasas_instance* instance; } ;
struct TYPE_4__ {int /*<<< orphan*/  service_isr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int megasas_setup_irqs_ioapic (struct megasas_instance*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_2__*) ; 

__attribute__((used)) static int
megasas_setup_irqs_msix(struct megasas_instance *instance, u8 is_probe)
{
	int i, j;
	struct pci_dev *pdev;

	pdev = instance->pdev;

	/* Try MSI-x */
	for (i = 0; i < instance->msix_vectors; i++) {
		instance->irq_context[i].instance = instance;
		instance->irq_context[i].MSIxIndex = i;
		if (request_irq(pci_irq_vector(pdev, i),
			instance->instancet->service_isr, 0, "megasas",
			&instance->irq_context[i])) {
			dev_err(&instance->pdev->dev,
				"Failed to register IRQ for vector %d.\n", i);
			for (j = 0; j < i; j++)
				free_irq(pci_irq_vector(pdev, j),
					 &instance->irq_context[j]);
			/* Retry irq register for IO_APIC*/
			instance->msix_vectors = 0;
			instance->msix_load_balance = false;
			if (is_probe) {
				pci_free_irq_vectors(instance->pdev);
				return megasas_setup_irqs_ioapic(instance);
			} else {
				return -1;
			}
		}
	}

	return 0;
}