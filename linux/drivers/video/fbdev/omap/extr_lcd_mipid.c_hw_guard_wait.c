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
struct mipid_device {unsigned long hw_guard_end; int /*<<< orphan*/  hw_guard_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  schedule_timeout (unsigned long) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before_eq (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hw_guard_wait(struct mipid_device *md)
{
	unsigned long wait = md->hw_guard_end - jiffies;

	if ((long)wait > 0 && time_before_eq(wait,  md->hw_guard_wait)) {
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_timeout(wait);
	}
}