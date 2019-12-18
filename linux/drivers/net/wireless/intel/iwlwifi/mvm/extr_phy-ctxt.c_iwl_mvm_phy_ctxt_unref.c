#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iwl_mvm_phy_ctxt {scalar_t__ ref; } ;
struct iwl_mvm {TYPE_2__* hw; int /*<<< orphan*/  mutex; } ;
struct ieee80211_supported_band {struct ieee80211_channel* channels; } ;
struct ieee80211_channel {int dummy; } ;
struct cfg80211_chan_def {int dummy; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_4__ {TYPE_1__* wiphy; } ;
struct TYPE_3__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  NL80211_CHAN_NO_HT ; 
 int NUM_NL80211_BANDS ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cfg80211_chandef_create (struct cfg80211_chan_def*,struct ieee80211_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_phy_ctxt_changed (struct iwl_mvm*,struct iwl_mvm_phy_ctxt*,struct cfg80211_chan_def*,int,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void iwl_mvm_phy_ctxt_unref(struct iwl_mvm *mvm, struct iwl_mvm_phy_ctxt *ctxt)
{
	lockdep_assert_held(&mvm->mutex);

	if (WARN_ON_ONCE(!ctxt))
		return;

	ctxt->ref--;

	/*
	 * Move unused phy's to a default channel. When the phy is moved the,
	 * fw will cleanup immediate quiet bit if it was previously set,
	 * otherwise we might not be able to reuse this phy.
	 */
	if (ctxt->ref == 0) {
		struct ieee80211_channel *chan;
		struct cfg80211_chan_def chandef;
		struct ieee80211_supported_band *sband = NULL;
		enum nl80211_band band = NL80211_BAND_2GHZ;

		while (!sband && band < NUM_NL80211_BANDS)
			sband = mvm->hw->wiphy->bands[band++];

		if (WARN_ON(!sband))
			return;

		chan = &sband->channels[0];

		cfg80211_chandef_create(&chandef, chan, NL80211_CHAN_NO_HT);
		iwl_mvm_phy_ctxt_changed(mvm, ctxt, &chandef, 1, 1);
	}
}