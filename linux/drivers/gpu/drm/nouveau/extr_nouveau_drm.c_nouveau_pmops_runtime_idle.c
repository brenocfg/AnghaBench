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
struct device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  nouveau_pmops_runtime () ; 
 int /*<<< orphan*/  pm_runtime_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_forbid (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 

__attribute__((used)) static int
nouveau_pmops_runtime_idle(struct device *dev)
{
	if (!nouveau_pmops_runtime()) {
		pm_runtime_forbid(dev);
		return -EBUSY;
	}

	pm_runtime_mark_last_busy(dev);
	pm_runtime_autosuspend(dev);
	/* we don't want the main rpm_idle to call suspend - we want to autosuspend */
	return 1;
}