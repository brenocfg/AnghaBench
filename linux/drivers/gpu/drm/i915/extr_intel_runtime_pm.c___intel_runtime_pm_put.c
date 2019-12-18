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
struct intel_runtime_pm {struct device* kdev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;

/* Variables and functions */
 int /*<<< orphan*/  intel_runtime_pm_release (struct intel_runtime_pm*,int) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (struct device*) ; 
 int /*<<< orphan*/  untrack_intel_runtime_pm_wakeref (struct intel_runtime_pm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __intel_runtime_pm_put(struct intel_runtime_pm *rpm,
				   intel_wakeref_t wref,
				   bool wakelock)
{
	struct device *kdev = rpm->kdev;

	untrack_intel_runtime_pm_wakeref(rpm, wref);

	intel_runtime_pm_release(rpm, wakelock);

	pm_runtime_mark_last_busy(kdev);
	pm_runtime_put_autosuspend(kdev);
}