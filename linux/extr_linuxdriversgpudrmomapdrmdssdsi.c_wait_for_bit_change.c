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
struct dsi_reg {int dummy; } ;
struct dsi_data {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int REG_GET (struct dsi_data*,struct dsi_reg const,int,int) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  ns_to_ktime (int) ; 
 int /*<<< orphan*/  schedule_hrtimeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static inline bool wait_for_bit_change(struct dsi_data *dsi,
				       const struct dsi_reg idx,
				       int bitnum, int value)
{
	unsigned long timeout;
	ktime_t wait;
	int t;

	/* first busyloop to see if the bit changes right away */
	t = 100;
	while (t-- > 0) {
		if (REG_GET(dsi, idx, bitnum, bitnum) == value)
			return true;
	}

	/* then loop for 500ms, sleeping for 1ms in between */
	timeout = jiffies + msecs_to_jiffies(500);
	while (time_before(jiffies, timeout)) {
		if (REG_GET(dsi, idx, bitnum, bitnum) == value)
			return true;

		wait = ns_to_ktime(1000 * 1000);
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_hrtimeout(&wait, HRTIMER_MODE_REL);
	}

	return false;
}