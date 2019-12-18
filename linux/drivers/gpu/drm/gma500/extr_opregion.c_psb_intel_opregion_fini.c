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
struct psb_intel_opregion {int /*<<< orphan*/ * vbt; int /*<<< orphan*/ * asle; int /*<<< orphan*/ * swsci; TYPE_1__* acpi; int /*<<< orphan*/ * header; int /*<<< orphan*/  asle_work; } ;
struct drm_psb_private {struct psb_intel_opregion opregion; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;
struct TYPE_2__ {scalar_t__ drdy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psb_intel_opregion_notifier ; 
 int /*<<< orphan*/ * system_opregion ; 
 int /*<<< orphan*/  unregister_acpi_notifier (int /*<<< orphan*/ *) ; 

void psb_intel_opregion_fini(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct psb_intel_opregion *opregion = &dev_priv->opregion;

	if (!opregion->header)
		return;

	if (opregion->acpi) {
		opregion->acpi->drdy = 0;

		system_opregion = NULL;
		unregister_acpi_notifier(&psb_intel_opregion_notifier);
	}

	cancel_work_sync(&opregion->asle_work);

	/* just clear all opregion memory pointers now */
	iounmap(opregion->header);
	opregion->header = NULL;
	opregion->acpi = NULL;
	opregion->swsci = NULL;
	opregion->asle = NULL;
	opregion->vbt = NULL;
}