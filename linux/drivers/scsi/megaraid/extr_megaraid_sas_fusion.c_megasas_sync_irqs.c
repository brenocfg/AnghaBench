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
typedef  size_t u32 ;
struct megasas_irq_context {int irq_poll_scheduled; int /*<<< orphan*/  os_irq; int /*<<< orphan*/  irqpoll; } ;
struct megasas_instance {scalar_t__ msix_vectors; struct megasas_irq_context* irq_context; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_poll_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void megasas_sync_irqs(unsigned long instance_addr)
{
	u32 count, i;
	struct megasas_instance *instance =
		(struct megasas_instance *)instance_addr;
	struct megasas_irq_context *irq_ctx;

	count = instance->msix_vectors > 0 ? instance->msix_vectors : 1;

	for (i = 0; i < count; i++) {
		synchronize_irq(pci_irq_vector(instance->pdev, i));
		irq_ctx = &instance->irq_context[i];
		irq_poll_disable(&irq_ctx->irqpoll);
		if (irq_ctx->irq_poll_scheduled) {
			irq_ctx->irq_poll_scheduled = false;
			enable_irq(irq_ctx->os_irq);
		}
	}
}