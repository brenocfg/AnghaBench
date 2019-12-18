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
struct intel_uncore {int /*<<< orphan*/  pmic_bus_access_nb; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_uncore_forcewake_reset (struct intel_uncore*) ; 
 int /*<<< orphan*/  intel_uncore_fw_domains_fini (struct intel_uncore*) ; 
 scalar_t__ intel_uncore_has_forcewake (struct intel_uncore*) ; 
 int /*<<< orphan*/  iosf_mbi_punit_acquire () ; 
 int /*<<< orphan*/  iosf_mbi_punit_release () ; 
 int /*<<< orphan*/  iosf_mbi_unregister_pmic_bus_access_notifier_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uncore_mmio_cleanup (struct intel_uncore*) ; 

void intel_uncore_fini_mmio(struct intel_uncore *uncore)
{
	if (intel_uncore_has_forcewake(uncore)) {
		iosf_mbi_punit_acquire();
		iosf_mbi_unregister_pmic_bus_access_notifier_unlocked(
			&uncore->pmic_bus_access_nb);
		intel_uncore_forcewake_reset(uncore);
		intel_uncore_fw_domains_fini(uncore);
		iosf_mbi_punit_release();
	}

	uncore_mmio_cleanup(uncore);
}