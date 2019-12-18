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
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_rpm_raw_wakeref_count (int) ; 
 int /*<<< orphan*/  intel_rpm_wakelock_count (int) ; 
 int /*<<< orphan*/  untrack_all_intel_runtime_pm_wakerefs (struct intel_runtime_pm*) ; 

void intel_runtime_pm_driver_release(struct intel_runtime_pm *rpm)
{
	int count = atomic_read(&rpm->wakeref_count);

	WARN(count,
	     "i915 raw-wakerefs=%d wakelocks=%d on cleanup\n",
	     intel_rpm_raw_wakeref_count(count),
	     intel_rpm_wakelock_count(count));

	untrack_all_intel_runtime_pm_wakerefs(rpm);
}