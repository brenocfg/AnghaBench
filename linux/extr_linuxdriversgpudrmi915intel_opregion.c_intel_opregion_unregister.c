#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * notifier_call; } ;
struct intel_opregion {int /*<<< orphan*/ * lid_state; int /*<<< orphan*/ * vbt; TYPE_2__* asle; int /*<<< orphan*/ * swsci; TYPE_1__* acpi; int /*<<< orphan*/ * header; int /*<<< orphan*/ * vbt_firmware; int /*<<< orphan*/ * rvda; TYPE_3__ acpi_notifier; int /*<<< orphan*/  asle_work; } ;
struct drm_i915_private {struct intel_opregion opregion; } ;
struct TYPE_5__ {int /*<<< orphan*/  ardy; } ;
struct TYPE_4__ {scalar_t__ drdy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASLE_ARDY_NOT_READY ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memunmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_acpi_notifier (TYPE_3__*) ; 

void intel_opregion_unregister(struct drm_i915_private *dev_priv)
{
	struct intel_opregion *opregion = &dev_priv->opregion;

	if (!opregion->header)
		return;

	if (opregion->asle)
		opregion->asle->ardy = ASLE_ARDY_NOT_READY;

	cancel_work_sync(&dev_priv->opregion.asle_work);

	if (opregion->acpi) {
		opregion->acpi->drdy = 0;

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