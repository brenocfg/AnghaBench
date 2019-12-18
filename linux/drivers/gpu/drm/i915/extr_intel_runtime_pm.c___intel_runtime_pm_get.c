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
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  intel_runtime_pm_acquire (struct intel_runtime_pm*,int) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  track_intel_runtime_pm_wakeref (struct intel_runtime_pm*) ; 

__attribute__((used)) static intel_wakeref_t __intel_runtime_pm_get(struct intel_runtime_pm *rpm,
					      bool wakelock)
{
	int ret;

	ret = pm_runtime_get_sync(rpm->kdev);
	WARN_ONCE(ret < 0, "pm_runtime_get_sync() failed: %d\n", ret);

	intel_runtime_pm_acquire(rpm, wakelock);

	return track_intel_runtime_pm_wakeref(rpm);
}