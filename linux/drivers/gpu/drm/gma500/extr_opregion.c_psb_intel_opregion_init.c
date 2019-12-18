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
struct psb_intel_opregion {TYPE_1__* acpi; int /*<<< orphan*/  header; } ;
struct drm_psb_private {struct psb_intel_opregion opregion; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;
struct TYPE_2__ {int drdy; scalar_t__ csts; } ;

/* Variables and functions */
 int /*<<< orphan*/  psb_intel_opregion_notifier ; 
 int /*<<< orphan*/  register_acpi_notifier (int /*<<< orphan*/ *) ; 
 struct psb_intel_opregion* system_opregion ; 

void psb_intel_opregion_init(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct psb_intel_opregion *opregion = &dev_priv->opregion;

	if (!opregion->header)
		return;

	if (opregion->acpi) {
		/* Notify BIOS we are ready to handle ACPI video ext notifs.
		 * Right now, all the events are handled by the ACPI video
		 * module. We don't actually need to do anything with them. */
		opregion->acpi->csts = 0;
		opregion->acpi->drdy = 1;

		system_opregion = opregion;
		register_acpi_notifier(&psb_intel_opregion_notifier);
	}
}