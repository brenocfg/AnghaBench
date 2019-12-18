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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct ath10k_mac_tdls_iter_data {int num_tdls_stations; struct ieee80211_vif* curr_vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_mac_tdls_vif_stations_count_iter ; 
 int /*<<< orphan*/  ieee80211_iterate_stations_atomic (struct ieee80211_hw*,int /*<<< orphan*/ ,struct ath10k_mac_tdls_iter_data*) ; 

__attribute__((used)) static int ath10k_mac_tdls_vif_stations_count(struct ieee80211_hw *hw,
					      struct ieee80211_vif *vif)
{
	struct ath10k_mac_tdls_iter_data data = {};

	data.curr_vif = vif;

	ieee80211_iterate_stations_atomic(hw,
					  ath10k_mac_tdls_vif_stations_count_iter,
					  &data);
	return data.num_tdls_stations;
}