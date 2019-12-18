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
 int /*<<< orphan*/  D_SCAN (char*,...) ; 
 int /*<<< orphan*/  S_SCANNING ; 
 int /*<<< orphan*/  S_SCAN_ABORTING ; 
 int /*<<< orphan*/  il_force_scan_end (struct il_priv*) ; 
 int il_send_scan_abort (struct il_priv*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
il_do_scan_abort(struct il_priv *il)
{
	int ret;

	lockdep_assert_held(&il->mutex);

	if (!test_bit(S_SCANNING, &il->status)) {
		D_SCAN("Not performing scan to abort\n");
		return;
	}

	if (test_and_set_bit(S_SCAN_ABORTING, &il->status)) {
		D_SCAN("Scan abort in progress\n");
		return;
	}

	ret = il_send_scan_abort(il);
	if (ret) {
		D_SCAN("Send scan abort failed %d\n", ret);
		il_force_scan_end(il);
	} else
		D_SCAN("Successfully send scan abort\n");
}