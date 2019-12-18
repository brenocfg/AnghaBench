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
struct vif_counter_data {struct ieee80211_vif* cur_vif; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_RESUME_ALL ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vif_counter_data*) ; 
 int /*<<< orphan*/  memset (struct vif_counter_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wl12xx_vif_count_iter ; 

__attribute__((used)) static void wl12xx_get_vif_count(struct ieee80211_hw *hw,
			       struct ieee80211_vif *cur_vif,
			       struct vif_counter_data *data)
{
	memset(data, 0, sizeof(*data));
	data->cur_vif = cur_vif;

	ieee80211_iterate_active_interfaces(hw, IEEE80211_IFACE_ITER_RESUME_ALL,
					    wl12xx_vif_count_iter, data);
}