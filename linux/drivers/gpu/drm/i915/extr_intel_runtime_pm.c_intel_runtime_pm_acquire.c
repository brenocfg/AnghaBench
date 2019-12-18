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
struct intel_runtime_pm {int /*<<< orphan*/  wakeref_count; } ;

/* Variables and functions */
 scalar_t__ INTEL_RPM_WAKELOCK_BIAS ; 
 int /*<<< orphan*/  assert_rpm_raw_wakeref_held (struct intel_runtime_pm*) ; 
 int /*<<< orphan*/  assert_rpm_wakelock_held (struct intel_runtime_pm*) ; 
 int /*<<< orphan*/  atomic_add (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
intel_runtime_pm_acquire(struct intel_runtime_pm *rpm, bool wakelock)
{
	if (wakelock) {
		atomic_add(1 + INTEL_RPM_WAKELOCK_BIAS, &rpm->wakeref_count);
		assert_rpm_wakelock_held(rpm);
	} else {
		atomic_inc(&rpm->wakeref_count);
		assert_rpm_raw_wakeref_held(rpm);
	}
}