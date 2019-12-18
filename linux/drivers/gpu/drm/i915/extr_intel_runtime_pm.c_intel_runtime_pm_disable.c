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
struct intel_runtime_pm {int /*<<< orphan*/  available; struct device* kdev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (struct device*) ; 
 scalar_t__ pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 

void intel_runtime_pm_disable(struct intel_runtime_pm *rpm)
{
	struct device *kdev = rpm->kdev;

	/* Transfer rpm ownership back to core */
	WARN(pm_runtime_get_sync(kdev) < 0,
	     "Failed to pass rpm ownership back to core\n");

	pm_runtime_dont_use_autosuspend(kdev);

	if (!rpm->available)
		pm_runtime_put(kdev);
}