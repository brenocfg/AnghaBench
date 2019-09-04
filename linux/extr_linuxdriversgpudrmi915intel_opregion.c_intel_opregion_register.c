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
struct TYPE_6__ {int /*<<< orphan*/  notifier_call; } ;
struct intel_opregion {TYPE_1__* asle; TYPE_3__ acpi_notifier; TYPE_2__* acpi; int /*<<< orphan*/  header; } ;
struct drm_i915_private {struct intel_opregion opregion; } ;
struct TYPE_5__ {int drdy; scalar_t__ csts; } ;
struct TYPE_4__ {int /*<<< orphan*/  ardy; int /*<<< orphan*/  tche; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASLE_ARDY_READY ; 
 int /*<<< orphan*/  ASLE_TCHE_BLC_EN ; 
 int /*<<< orphan*/  intel_didl_outputs (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_opregion_video_event ; 
 int /*<<< orphan*/  intel_setup_cadls (struct drm_i915_private*) ; 
 int /*<<< orphan*/  register_acpi_notifier (TYPE_3__*) ; 

void intel_opregion_register(struct drm_i915_private *dev_priv)
{
	struct intel_opregion *opregion = &dev_priv->opregion;

	if (!opregion->header)
		return;

	if (opregion->acpi) {
		intel_didl_outputs(dev_priv);
		intel_setup_cadls(dev_priv);

		/* Notify BIOS we are ready to handle ACPI video ext notifs.
		 * Right now, all the events are handled by the ACPI video module.
		 * We don't actually need to do anything with them. */
		opregion->acpi->csts = 0;
		opregion->acpi->drdy = 1;

		opregion->acpi_notifier.notifier_call = intel_opregion_video_event;
		register_acpi_notifier(&opregion->acpi_notifier);
	}

	if (opregion->asle) {
		opregion->asle->tche = ASLE_TCHE_BLC_EN;
		opregion->asle->ardy = ASLE_ARDY_READY;
	}
}