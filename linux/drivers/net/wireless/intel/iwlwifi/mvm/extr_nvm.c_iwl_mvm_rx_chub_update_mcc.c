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
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_mvm {TYPE_1__* hw; int /*<<< orphan*/  mutex; } ;
struct iwl_mcc_chub_notif {scalar_t__ source_id; int /*<<< orphan*/  mcc; } ;
struct ieee80211_regdomain {int dummy; } ;
typedef  enum iwl_mcc_source { ____Placeholder_iwl_mcc_source } iwl_mcc_source ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct ieee80211_regdomain*) ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  IWL_DEBUG_LAR (struct iwl_mvm*,char*,...) ; 
 scalar_t__ MCC_SOURCE_WIFI ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct ieee80211_regdomain* iwl_mvm_get_regdomain (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int iwl_mvm_get_sar_geo_profile (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_is_lar_supported (struct iwl_mvm*) ; 
 scalar_t__ iwl_mvm_is_vif_assoc (struct iwl_mvm*) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_regdomain*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulatory_set_wiphy_regd (int /*<<< orphan*/ ,struct ieee80211_regdomain*) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 

void iwl_mvm_rx_chub_update_mcc(struct iwl_mvm *mvm,
				struct iwl_rx_cmd_buffer *rxb)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_mcc_chub_notif *notif = (void *)pkt->data;
	enum iwl_mcc_source src;
	char mcc[3];
	struct ieee80211_regdomain *regd;
	int wgds_tbl_idx;

	lockdep_assert_held(&mvm->mutex);

	if (iwl_mvm_is_vif_assoc(mvm) && notif->source_id == MCC_SOURCE_WIFI) {
		IWL_DEBUG_LAR(mvm, "Ignore mcc update while associated\n");
		return;
	}

	if (WARN_ON_ONCE(!iwl_mvm_is_lar_supported(mvm)))
		return;

	mcc[0] = le16_to_cpu(notif->mcc) >> 8;
	mcc[1] = le16_to_cpu(notif->mcc) & 0xff;
	mcc[2] = '\0';
	src = notif->source_id;

	IWL_DEBUG_LAR(mvm,
		      "RX: received chub update mcc cmd (mcc '%s' src %d)\n",
		      mcc, src);
	regd = iwl_mvm_get_regdomain(mvm->hw->wiphy, mcc, src, NULL);
	if (IS_ERR_OR_NULL(regd))
		return;

	wgds_tbl_idx = iwl_mvm_get_sar_geo_profile(mvm);
	if (wgds_tbl_idx < 0)
		IWL_DEBUG_INFO(mvm, "SAR WGDS is disabled (%d)\n",
			       wgds_tbl_idx);
	else
		IWL_DEBUG_INFO(mvm, "SAR WGDS: geo profile %d is configured\n",
			       wgds_tbl_idx);

	regulatory_set_wiphy_regd(mvm->hw->wiphy, regd);
	kfree(regd);
}