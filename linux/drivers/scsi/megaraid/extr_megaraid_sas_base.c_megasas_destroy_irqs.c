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
struct megasas_irq_context {int /*<<< orphan*/  irqpoll; } ;
struct megasas_instance {int msix_vectors; scalar_t__ adapter_type; struct megasas_irq_context* irq_context; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ MFI_SERIES ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct megasas_irq_context*) ; 
 int /*<<< orphan*/  irq_poll_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
megasas_destroy_irqs(struct megasas_instance *instance) {

	int i;
	int count;
	struct megasas_irq_context *irq_ctx;

	count = instance->msix_vectors > 0 ? instance->msix_vectors : 1;
	if (instance->adapter_type != MFI_SERIES) {
		for (i = 0; i < count; i++) {
			irq_ctx = &instance->irq_context[i];
			irq_poll_disable(&irq_ctx->irqpoll);
		}
	}

	if (instance->msix_vectors)
		for (i = 0; i < instance->msix_vectors; i++) {
			free_irq(pci_irq_vector(instance->pdev, i),
				 &instance->irq_context[i]);
		}
	else
		free_irq(pci_irq_vector(instance->pdev, 0),
			 &instance->irq_context[0]);
}