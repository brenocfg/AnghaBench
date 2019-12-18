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
struct TYPE_2__ {int /*<<< orphan*/  notifier_call; } ;
struct intel_opregion {TYPE_1__ acpi_notifier; scalar_t__ acpi; int /*<<< orphan*/  header; } ;
struct drm_i915_private {struct intel_opregion opregion; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_opregion_resume (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_opregion_video_event ; 
 int /*<<< orphan*/  register_acpi_notifier (TYPE_1__*) ; 

void intel_opregion_register(struct drm_i915_private *i915)
{
	struct intel_opregion *opregion = &i915->opregion;

	if (!opregion->header)
		return;

	if (opregion->acpi) {
		opregion->acpi_notifier.notifier_call =
			intel_opregion_video_event;
		register_acpi_notifier(&opregion->acpi_notifier);
	}

	intel_opregion_resume(i915);
}