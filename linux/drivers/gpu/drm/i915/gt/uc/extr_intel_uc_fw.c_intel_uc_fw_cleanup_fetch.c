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
struct intel_uc_fw {int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_UC_FIRMWARE_SELECTED ; 
 int /*<<< orphan*/  fetch_and_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uc_fw_change_status (struct intel_uc_fw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uc_fw_is_available (struct intel_uc_fw*) ; 

void intel_uc_fw_cleanup_fetch(struct intel_uc_fw *uc_fw)
{
	if (!intel_uc_fw_is_available(uc_fw))
		return;

	i915_gem_object_put(fetch_and_zero(&uc_fw->obj));

	intel_uc_fw_change_status(uc_fw, INTEL_UC_FIRMWARE_SELECTED);
}