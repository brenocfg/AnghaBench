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
struct adb_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pmu_blink_lock ; 
 int /*<<< orphan*/  pmu_blink_req ; 
 int /*<<< orphan*/  pmu_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmu_sys_suspended ; 
 int requested_change ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void pmu_req_done(struct adb_request * req)
{
	unsigned long flags;

	spin_lock_irqsave(&pmu_blink_lock, flags);
	/* if someone requested a change in the meantime
	 * (we only see the last one which is fine)
	 * then apply it now */
	if (requested_change != -1 && !pmu_sys_suspended)
		pmu_request(&pmu_blink_req, NULL, 4, 0xee, 4, 0, requested_change);
	/* reset requested change */
	requested_change = -1;
	spin_unlock_irqrestore(&pmu_blink_lock, flags);
}