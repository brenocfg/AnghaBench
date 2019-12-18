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
struct intel_uncore {int /*<<< orphan*/  pmic_bus_access_nb; int /*<<< orphan*/  fw_domains_saved; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 unsigned int fetch_and_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  forcewake_early_sanitize (struct intel_uncore*,unsigned int) ; 
 int /*<<< orphan*/  intel_uncore_has_forcewake (struct intel_uncore*) ; 
 scalar_t__ intel_uncore_unclaimed_mmio (struct intel_uncore*) ; 
 int /*<<< orphan*/  iosf_mbi_register_pmic_bus_access_notifier (int /*<<< orphan*/ *) ; 

void intel_uncore_resume_early(struct intel_uncore *uncore)
{
	unsigned int restore_forcewake;

	if (intel_uncore_unclaimed_mmio(uncore))
		DRM_DEBUG("unclaimed mmio detected on resume, clearing\n");

	if (!intel_uncore_has_forcewake(uncore))
		return;

	restore_forcewake = fetch_and_zero(&uncore->fw_domains_saved);
	forcewake_early_sanitize(uncore, restore_forcewake);

	iosf_mbi_register_pmic_bus_access_notifier(&uncore->pmic_bus_access_nb);
}