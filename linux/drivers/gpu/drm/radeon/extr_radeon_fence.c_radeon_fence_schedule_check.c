#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct radeon_device {TYPE_1__* fence_drv; } ;
struct TYPE_2__ {int /*<<< orphan*/  lockup_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_FENCE_JIFFIES_TIMEOUT ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

__attribute__((used)) static void radeon_fence_schedule_check(struct radeon_device *rdev, int ring)
{
	/*
	 * Do not reset the timer here with mod_delayed_work,
	 * this can livelock in an interaction with TTM delayed destroy.
	 */
	queue_delayed_work(system_power_efficient_wq,
			   &rdev->fence_drv[ring].lockup_work,
			   RADEON_FENCE_JIFFIES_TIMEOUT);
}