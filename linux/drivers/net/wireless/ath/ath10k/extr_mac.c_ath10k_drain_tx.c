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
struct ath10k {int /*<<< orphan*/  wmi_mgmt_tx_work; int /*<<< orphan*/  offchan_tx_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_mgmt_over_wmi_tx_purge (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_offchan_tx_purge (struct ath10k*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_net () ; 

void ath10k_drain_tx(struct ath10k *ar)
{
	/* make sure rcu-protected mac80211 tx path itself is drained */
	synchronize_net();

	ath10k_offchan_tx_purge(ar);
	ath10k_mgmt_over_wmi_tx_purge(ar);

	cancel_work_sync(&ar->offchan_tx_work);
	cancel_work_sync(&ar->wmi_mgmt_tx_work);
}