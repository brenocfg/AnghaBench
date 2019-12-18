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
struct ixgbe_adapter {scalar_t__ last_overflow_check; int /*<<< orphan*/  tmreg_lock; int /*<<< orphan*/  hw_tc; } ;

/* Variables and functions */
 scalar_t__ IXGBE_OVERFLOW_PERIOD ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int time_is_before_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  timecounter_read (int /*<<< orphan*/ *) ; 

void ixgbe_ptp_overflow_check(struct ixgbe_adapter *adapter)
{
	bool timeout = time_is_before_jiffies(adapter->last_overflow_check +
					     IXGBE_OVERFLOW_PERIOD);
	unsigned long flags;

	if (timeout) {
		/* Update the timecounter */
		spin_lock_irqsave(&adapter->tmreg_lock, flags);
		timecounter_read(&adapter->hw_tc);
		spin_unlock_irqrestore(&adapter->tmreg_lock, flags);

		adapter->last_overflow_check = jiffies;
	}
}