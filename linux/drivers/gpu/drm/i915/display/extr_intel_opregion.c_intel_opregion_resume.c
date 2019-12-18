#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intel_opregion {TYPE_1__* asle; TYPE_2__* acpi; int /*<<< orphan*/  header; } ;
struct drm_i915_private {struct intel_opregion opregion; } ;
struct TYPE_4__ {int drdy; scalar_t__ csts; } ;
struct TYPE_3__ {int /*<<< orphan*/  ardy; int /*<<< orphan*/  tche; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASLE_ARDY_READY ; 
 int /*<<< orphan*/  ASLE_TCHE_BLC_EN ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  intel_didl_outputs (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_opregion_notify_adapter (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_setup_cadls (struct drm_i915_private*) ; 

void intel_opregion_resume(struct drm_i915_private *i915)
{
	struct intel_opregion *opregion = &i915->opregion;

	if (!opregion->header)
		return;

	if (opregion->acpi) {
		intel_didl_outputs(i915);
		intel_setup_cadls(i915);

		/*
		 * Notify BIOS we are ready to handle ACPI video ext notifs.
		 * Right now, all the events are handled by the ACPI video
		 * module. We don't actually need to do anything with them.
		 */
		opregion->acpi->csts = 0;
		opregion->acpi->drdy = 1;
	}

	if (opregion->asle) {
		opregion->asle->tche = ASLE_TCHE_BLC_EN;
		opregion->asle->ardy = ASLE_ARDY_READY;
	}

	intel_opregion_notify_adapter(i915, PCI_D0);
}