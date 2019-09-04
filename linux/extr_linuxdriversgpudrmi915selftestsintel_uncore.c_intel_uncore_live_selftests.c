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
struct TYPE_2__ {int /*<<< orphan*/  fw_domains_table_entries; int /*<<< orphan*/  fw_domains_table; } ;
struct drm_i915_private {TYPE_1__ uncore; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 int intel_fw_table_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int intel_uncore_check_forcewake_domains (struct drm_i915_private*) ; 

int intel_uncore_live_selftests(struct drm_i915_private *i915)
{
	int err;

	/* Confirm the table we load is still valid */
	err = intel_fw_table_check(i915->uncore.fw_domains_table,
				   i915->uncore.fw_domains_table_entries,
				   INTEL_GEN(i915) >= 9);
	if (err)
		return err;

	err = intel_uncore_check_forcewake_domains(i915);
	if (err)
		return err;

	return 0;
}