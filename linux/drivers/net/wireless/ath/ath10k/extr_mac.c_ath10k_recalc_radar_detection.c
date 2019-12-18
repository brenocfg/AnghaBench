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
struct ath10k {scalar_t__ num_started_vdevs; int /*<<< orphan*/  hw; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_mac_has_radar_enabled (struct ath10k*) ; 
 int ath10k_start_cac (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_stop_cac (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  ieee80211_radar_detected (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_recalc_radar_detection(struct ath10k *ar)
{
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	ath10k_stop_cac(ar);

	if (!ath10k_mac_has_radar_enabled(ar))
		return;

	if (ar->num_started_vdevs > 0)
		return;

	ret = ath10k_start_cac(ar);
	if (ret) {
		/*
		 * Not possible to start CAC on current channel so starting
		 * radiation is not allowed, make this channel DFS_UNAVAILABLE
		 * by indicating that radar was detected.
		 */
		ath10k_warn(ar, "failed to start CAC: %d\n", ret);
		ieee80211_radar_detected(ar->hw);
	}
}