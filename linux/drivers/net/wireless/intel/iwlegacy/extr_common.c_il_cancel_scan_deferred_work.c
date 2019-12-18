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
struct il_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  scan_check; int /*<<< orphan*/  scan_completed; int /*<<< orphan*/  abort_scan; } ;

/* Variables and functions */
 scalar_t__ cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  il_force_scan_end (struct il_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void
il_cancel_scan_deferred_work(struct il_priv *il)
{
	cancel_work_sync(&il->abort_scan);
	cancel_work_sync(&il->scan_completed);

	if (cancel_delayed_work_sync(&il->scan_check)) {
		mutex_lock(&il->mutex);
		il_force_scan_end(il);
		mutex_unlock(&il->mutex);
	}
}