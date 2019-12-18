#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wiphy {int dummy; } ;
struct qtnf_wmac {struct qtnf_vif* iflist; } ;
struct TYPE_2__ {size_t iftype; } ;
struct qtnf_vif {TYPE_1__ wdev; } ;
struct iface_combination_params {int num_different_channels; int /*<<< orphan*/ * iftype_num; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int EFAULT ; 
 size_t NL80211_IFTYPE_UNSPECIFIED ; 
 int QTNF_MAX_INTF ; 
 int cfg80211_check_combinations (struct wiphy*,struct iface_combination_params*) ; 
 struct qtnf_wmac* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int
qtnf_validate_iface_combinations(struct wiphy *wiphy,
				 struct qtnf_vif *change_vif,
				 enum nl80211_iftype new_type)
{
	struct qtnf_wmac *mac;
	struct qtnf_vif *vif;
	int i;
	int ret = 0;
	struct iface_combination_params params = {
		.num_different_channels = 1,
	};

	mac = wiphy_priv(wiphy);
	if (!mac)
		return -EFAULT;

	for (i = 0; i < QTNF_MAX_INTF; i++) {
		vif = &mac->iflist[i];
		if (vif->wdev.iftype != NL80211_IFTYPE_UNSPECIFIED)
			params.iftype_num[vif->wdev.iftype]++;
	}

	if (change_vif) {
		params.iftype_num[new_type]++;
		params.iftype_num[change_vif->wdev.iftype]--;
	} else {
		params.iftype_num[new_type]++;
	}

	ret = cfg80211_check_combinations(wiphy, &params);

	return ret;
}