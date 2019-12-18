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
struct pci_dev {int dummy; } ;
struct megasas_instance {int unload; int /*<<< orphan*/  pdev; scalar_t__ msix_vectors; TYPE_1__* instancet; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable_intr ) (struct megasas_instance*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MR_DCMD_CTRL_SHUTDOWN ; 
 int /*<<< orphan*/  megasas_destroy_irqs (struct megasas_instance*) ; 
 int /*<<< orphan*/  megasas_flush_cache (struct megasas_instance*) ; 
 int /*<<< orphan*/  megasas_shutdown_controller (struct megasas_instance*,int /*<<< orphan*/ ) ; 
 scalar_t__ megasas_wait_for_adapter_operational (struct megasas_instance*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (int /*<<< orphan*/ ) ; 
 struct megasas_instance* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  stub1 (struct megasas_instance*) ; 

__attribute__((used)) static void megasas_shutdown(struct pci_dev *pdev)
{
	struct megasas_instance *instance = pci_get_drvdata(pdev);

	if (!instance)
		return;

	instance->unload = 1;

	if (megasas_wait_for_adapter_operational(instance))
		goto skip_firing_dcmds;

	megasas_flush_cache(instance);
	megasas_shutdown_controller(instance, MR_DCMD_CTRL_SHUTDOWN);

skip_firing_dcmds:
	instance->instancet->disable_intr(instance);
	megasas_destroy_irqs(instance);

	if (instance->msix_vectors)
		pci_free_irq_vectors(instance->pdev);
}