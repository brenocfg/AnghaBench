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
struct TYPE_2__ {int /*<<< orphan*/ * notifier_call; } ;
struct intel_opregion {int /*<<< orphan*/ * lid_state; int /*<<< orphan*/ * vbt; int /*<<< orphan*/ * asle; int /*<<< orphan*/ * swsci; int /*<<< orphan*/ * acpi; int /*<<< orphan*/ * header; int /*<<< orphan*/ * vbt_firmware; int /*<<< orphan*/ * rvda; TYPE_1__ acpi_notifier; } ;
struct drm_i915_private {struct intel_opregion opregion; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D1 ; 
 int /*<<< orphan*/  intel_opregion_suspend (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memunmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_acpi_notifier (TYPE_1__*) ; 

void intel_opregion_unregister(struct drm_i915_private *i915)
{
	struct intel_opregion *opregion = &i915->opregion;

	intel_opregion_suspend(i915, PCI_D1);

	if (!opregion->header)
		return;

	if (opregion->acpi_notifier.notifier_call) {
		unregister_acpi_notifier(&opregion->acpi_notifier);
		opregion->acpi_notifier.notifier_call = NULL;
	}

	/* just clear all opregion memory pointers now */
	memunmap(opregion->header);
	if (opregion->rvda) {
		memunmap(opregion->rvda);
		opregion->rvda = NULL;
	}
	if (opregion->vbt_firmware) {
		kfree(opregion->vbt_firmware);
		opregion->vbt_firmware = NULL;
	}
	opregion->header = NULL;
	opregion->acpi = NULL;
	opregion->swsci = NULL;
	opregion->asle = NULL;
	opregion->vbt = NULL;
	opregion->lid_state = NULL;
}