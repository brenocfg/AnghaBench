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
struct iwl_priv {int /*<<< orphan*/  status; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_SCAN (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  STATUS_SCAN_HW ; 
 int /*<<< orphan*/  iwl_do_scan_abort (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwl_process_scan_complete (struct iwl_priv*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 unsigned long msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_before_eq (unsigned long,unsigned long) ; 

void iwl_scan_cancel_timeout(struct iwl_priv *priv, unsigned long ms)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(ms);

	lockdep_assert_held(&priv->mutex);

	IWL_DEBUG_SCAN(priv, "Scan cancel timeout\n");

	iwl_do_scan_abort(priv);

	while (time_before_eq(jiffies, timeout)) {
		if (!test_bit(STATUS_SCAN_HW, &priv->status))
			goto finished;
		msleep(20);
	}

	return;

 finished:
	/*
	 * Now STATUS_SCAN_HW is clear. This means that the
	 * device finished, but the background work is going
	 * to execute at best as soon as we release the mutex.
	 * Since we need to be able to issue a new scan right
	 * after this function returns, run the complete here.
	 * The STATUS_SCAN_COMPLETE bit will then be cleared
	 * and prevent the background work from "completing"
	 * a possible new scan.
	 */
	iwl_process_scan_complete(priv);
}