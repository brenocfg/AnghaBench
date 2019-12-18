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
struct ath6kl_vif {int /*<<< orphan*/  fw_vif_idx; int /*<<< orphan*/  sched_scan_timer; int /*<<< orphan*/  flags; struct ath6kl* ar; } ;
struct ath6kl {scalar_t__ state; int /*<<< orphan*/  wmi; } ;

/* Variables and functions */
 scalar_t__ ATH6KL_STATE_RECOVERY ; 
 int /*<<< orphan*/  SCHED_SCANNING ; 
 int /*<<< orphan*/  ath6kl_wmi_enable_sched_scan_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool __ath6kl_cfg80211_sscan_stop(struct ath6kl_vif *vif)
{
	struct ath6kl *ar = vif->ar;

	if (!test_and_clear_bit(SCHED_SCANNING, &vif->flags))
		return false;

	del_timer_sync(&vif->sched_scan_timer);

	if (ar->state == ATH6KL_STATE_RECOVERY)
		return true;

	ath6kl_wmi_enable_sched_scan_cmd(ar->wmi, vif->fw_vif_idx, false);

	return true;
}