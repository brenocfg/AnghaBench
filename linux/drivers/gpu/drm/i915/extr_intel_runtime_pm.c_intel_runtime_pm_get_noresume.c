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
struct intel_runtime_pm {int /*<<< orphan*/  kdev; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert_rpm_wakelock_held (struct intel_runtime_pm*) ; 
 int /*<<< orphan*/  intel_runtime_pm_acquire (struct intel_runtime_pm*,int) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  track_intel_runtime_pm_wakeref (struct intel_runtime_pm*) ; 

intel_wakeref_t intel_runtime_pm_get_noresume(struct intel_runtime_pm *rpm)
{
	assert_rpm_wakelock_held(rpm);
	pm_runtime_get_noresume(rpm->kdev);

	intel_runtime_pm_acquire(rpm, true);

	return track_intel_runtime_pm_wakeref(rpm);
}