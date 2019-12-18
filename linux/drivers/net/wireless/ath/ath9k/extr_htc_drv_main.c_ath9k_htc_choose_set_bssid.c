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
struct ath9k_htc_priv {int num_sta_assoc_vif; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_RESUME_ALL ; 
 int /*<<< orphan*/  ath9k_htc_bss_iter ; 
 int /*<<< orphan*/  ath9k_htc_set_bssid (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ath9k_htc_priv*) ; 

__attribute__((used)) static void ath9k_htc_choose_set_bssid(struct ath9k_htc_priv *priv)
{
	if (priv->num_sta_assoc_vif == 1) {
		ieee80211_iterate_active_interfaces_atomic(
			priv->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
			ath9k_htc_bss_iter, priv);
		ath9k_htc_set_bssid(priv);
	}
}