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
struct wireless_dev {size_t iftype; } ;
struct wil6210_priv {int /*<<< orphan*/  wiphy; scalar_t__* vifs; } ;
struct iface_combination_params {int num_different_channels; int /*<<< orphan*/ * iftype_num; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int GET_MAX_VIFS (struct wil6210_priv*) ; 
 int cfg80211_check_combinations (int /*<<< orphan*/ ,struct iface_combination_params*) ; 
 struct wireless_dev* vif_to_wdev (scalar_t__) ; 

__attribute__((used)) static int wil_cfg80211_validate_add_iface(struct wil6210_priv *wil,
					   enum nl80211_iftype new_type)
{
	int i;
	struct wireless_dev *wdev;
	struct iface_combination_params params = {
		.num_different_channels = 1,
	};

	for (i = 0; i < GET_MAX_VIFS(wil); i++) {
		if (wil->vifs[i]) {
			wdev = vif_to_wdev(wil->vifs[i]);
			params.iftype_num[wdev->iftype]++;
		}
	}
	params.iftype_num[new_type]++;
	return cfg80211_check_combinations(wil->wiphy, &params);
}