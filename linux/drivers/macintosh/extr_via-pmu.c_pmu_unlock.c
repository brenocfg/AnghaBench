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

/* Variables and functions */
 int adb_int_pending ; 
 scalar_t__ idle ; 
 scalar_t__ locked ; 
 int /*<<< orphan*/  pmu_lock ; 
 scalar_t__ pmu_state ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
pmu_unlock(void)
{
	unsigned long flags;

	spin_lock_irqsave(&pmu_lock, flags);
	if (pmu_state == locked)
		pmu_state = idle;
	adb_int_pending = 1;
	spin_unlock_irqrestore(&pmu_lock, flags);
}