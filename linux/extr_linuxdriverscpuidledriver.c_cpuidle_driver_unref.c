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
struct cpuidle_driver {scalar_t__ refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cpuidle_driver_lock ; 
 struct cpuidle_driver* cpuidle_get_driver () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void cpuidle_driver_unref(void)
{
	struct cpuidle_driver *drv;

	spin_lock(&cpuidle_driver_lock);

	drv = cpuidle_get_driver();
	if (drv && !WARN_ON(drv->refcnt <= 0))
		drv->refcnt--;

	spin_unlock(&cpuidle_driver_lock);
}