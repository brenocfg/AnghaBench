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
 int /*<<< orphan*/  INTEL_RPM_WAKELOCK_BIAS ; 
 int /*<<< orphan*/  __intel_wakeref_dec_and_check_tracking (struct intel_runtime_pm*) ; 
 int /*<<< orphan*/  assert_rpm_raw_wakeref_held (struct intel_runtime_pm*) ; 
 int /*<<< orphan*/  assert_rpm_wakelock_held (struct intel_runtime_pm*) ; 
 int /*<<< orphan*/  atomic_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
intel_runtime_pm_release(struct intel_runtime_pm *rpm, int wakelock)
{
	if (wakelock) {
		assert_rpm_wakelock_held(rpm);
		atomic_sub(INTEL_RPM_WAKELOCK_BIAS, &rpm->wakeref_count);
	} else {
		assert_rpm_raw_wakeref_held(rpm);
	}

	__intel_wakeref_dec_and_check_tracking(rpm);
}