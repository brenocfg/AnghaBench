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
struct il_priv {int /*<<< orphan*/  status; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_SCAN (char*) ; 
 int /*<<< orphan*/  S_SCAN_HW ; 
 int /*<<< orphan*/  il_do_scan_abort (struct il_priv*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 unsigned long msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_before_eq (unsigned long,unsigned long) ; 

int
il_scan_cancel_timeout(struct il_priv *il, unsigned long ms)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(ms);

	lockdep_assert_held(&il->mutex);

	D_SCAN("Scan cancel timeout\n");

	il_do_scan_abort(il);

	while (time_before_eq(jiffies, timeout)) {
		if (!test_bit(S_SCAN_HW, &il->status))
			break;
		msleep(20);
	}

	return test_bit(S_SCAN_HW, &il->status);
}