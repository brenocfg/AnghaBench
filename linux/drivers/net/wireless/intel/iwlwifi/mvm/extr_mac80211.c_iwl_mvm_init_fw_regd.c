#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iwl_mvm {int mcc_src; TYPE_1__* hw; } ;
struct ieee80211_regdomain {int /*<<< orphan*/  alpha2; } ;
typedef  enum iwl_mcc_source { ____Placeholder_iwl_mcc_source } iwl_mcc_source ;
struct TYPE_5__ {int /*<<< orphan*/  regd; } ;
struct TYPE_4__ {TYPE_2__* wiphy; } ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 scalar_t__ IS_ERR_OR_NULL (struct ieee80211_regdomain*) ; 
 struct ieee80211_regdomain* iwl_mvm_get_current_regdomain (struct iwl_mvm*,int /*<<< orphan*/ *) ; 
 struct ieee80211_regdomain* iwl_mvm_get_regdomain (TYPE_2__*,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ iwl_mvm_is_wifi_mcc_supported (struct iwl_mvm*) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_regdomain*) ; 
 int regulatory_set_wiphy_regd_sync_rtnl (TYPE_2__*,struct ieee80211_regdomain*) ; 
 struct ieee80211_regdomain* rtnl_dereference (int /*<<< orphan*/ ) ; 

int iwl_mvm_init_fw_regd(struct iwl_mvm *mvm)
{
	enum iwl_mcc_source used_src;
	struct ieee80211_regdomain *regd;
	int ret;
	bool changed;
	const struct ieee80211_regdomain *r =
			rtnl_dereference(mvm->hw->wiphy->regd);

	if (!r)
		return -ENOENT;

	/* save the last source in case we overwrite it below */
	used_src = mvm->mcc_src;
	if (iwl_mvm_is_wifi_mcc_supported(mvm)) {
		/* Notify the firmware we support wifi location updates */
		regd = iwl_mvm_get_current_regdomain(mvm, NULL);
		if (!IS_ERR_OR_NULL(regd))
			kfree(regd);
	}

	/* Now set our last stored MCC and source */
	regd = iwl_mvm_get_regdomain(mvm->hw->wiphy, r->alpha2, used_src,
				     &changed);
	if (IS_ERR_OR_NULL(regd))
		return -EIO;

	/* update cfg80211 if the regdomain was changed */
	if (changed)
		ret = regulatory_set_wiphy_regd_sync_rtnl(mvm->hw->wiphy, regd);
	else
		ret = 0;

	kfree(regd);
	return ret;
}