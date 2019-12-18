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
struct ath10k {int /*<<< orphan*/  dev_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_CAC_RUNNING ; 
 int ath10k_mac_num_chanctxs (struct ath10k*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ath10k_mac_monitor_vdev_is_allowed(struct ath10k *ar)
{
	int num_ctx;

	num_ctx = ath10k_mac_num_chanctxs(ar);

	/* FIXME: Current interface combinations and cfg80211/mac80211 code
	 * shouldn't allow this but make sure to prevent handling the following
	 * case anyway since multi-channel DFS hasn't been tested at all.
	 */
	if (test_bit(ATH10K_CAC_RUNNING, &ar->dev_flags) && num_ctx > 1)
		return false;

	return true;
}