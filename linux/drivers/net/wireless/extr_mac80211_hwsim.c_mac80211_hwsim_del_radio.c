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
struct mac80211_hwsim_data {int /*<<< orphan*/  hw; int /*<<< orphan*/  dev; int /*<<< orphan*/  debugfs; int /*<<< orphan*/  idx; } ;
struct genl_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_release_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwsim_mcast_del_radio (int /*<<< orphan*/ ,char const*,struct genl_info*) ; 
 int /*<<< orphan*/  ieee80211_free_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mac80211_hwsim_del_radio(struct mac80211_hwsim_data *data,
				     const char *hwname,
				     struct genl_info *info)
{
	hwsim_mcast_del_radio(data->idx, hwname, info);
	debugfs_remove_recursive(data->debugfs);
	ieee80211_unregister_hw(data->hw);
	device_release_driver(data->dev);
	device_unregister(data->dev);
	ieee80211_free_hw(data->hw);
}