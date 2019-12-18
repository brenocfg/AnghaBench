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
typedef  int u32 ;
typedef  size_t u16 ;
struct iwl_mvm_vif {int ap_ibss_active; int csa_bcn_pending; int ps_disabled; int monitor_active; struct iwl_mvm_phy_ctxt* phy_ctxt; } ;
struct iwl_mvm_phy_ctxt {int dummy; } ;
struct iwl_mvm {TYPE_1__* fw; int /*<<< orphan*/  mutex; struct iwl_mvm_phy_ctxt* phy_ctxts; } ;
struct TYPE_4__ {int beacon_int; } ;
struct ieee80211_vif {int type; TYPE_2__ bss_conf; } ;
struct ieee80211_chanctx_conf {scalar_t__ drv_priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_CHANNEL_SWITCH_CMD ; 
#define  NL80211_IFTYPE_ADHOC 131 
#define  NL80211_IFTYPE_AP 130 
#define  NL80211_IFTYPE_MONITOR 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int iwl_mvm_add_snif_sta (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int iwl_mvm_binding_add_vif (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_binding_remove_vif (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_mac_ctxt_changed (struct iwl_mvm*,struct ieee80211_vif*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_mvm_power_update_mac (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_protect_session (struct iwl_mvm*,struct ieee80211_vif*,int,int,int,int) ; 
 int iwl_mvm_update_quotas (struct iwl_mvm*,int,int /*<<< orphan*/ *) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __iwl_mvm_assign_vif_chanctx(struct iwl_mvm *mvm,
					struct ieee80211_vif *vif,
					struct ieee80211_chanctx_conf *ctx,
					bool switching_chanctx)
{
	u16 *phy_ctxt_id = (u16 *)ctx->drv_priv;
	struct iwl_mvm_phy_ctxt *phy_ctxt = &mvm->phy_ctxts[*phy_ctxt_id];
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	int ret;

	lockdep_assert_held(&mvm->mutex);

	mvmvif->phy_ctxt = phy_ctxt;

	switch (vif->type) {
	case NL80211_IFTYPE_AP:
		/* only needed if we're switching chanctx (i.e. during CSA) */
		if (switching_chanctx) {
			mvmvif->ap_ibss_active = true;
			break;
		}
		/* fall through */
	case NL80211_IFTYPE_ADHOC:
		/*
		 * The AP binding flow is handled as part of the start_ap flow
		 * (in bss_info_changed), similarly for IBSS.
		 */
		ret = 0;
		goto out;
	case NL80211_IFTYPE_STATION:
		mvmvif->csa_bcn_pending = false;
		break;
	case NL80211_IFTYPE_MONITOR:
		/* always disable PS when a monitor interface is active */
		mvmvif->ps_disabled = true;
		break;
	default:
		ret = -EINVAL;
		goto out;
	}

	ret = iwl_mvm_binding_add_vif(mvm, vif);
	if (ret)
		goto out;

	/*
	 * Power state must be updated before quotas,
	 * otherwise fw will complain.
	 */
	iwl_mvm_power_update_mac(mvm);

	/* Setting the quota at this stage is only required for monitor
	 * interfaces. For the other types, the bss_info changed flow
	 * will handle quota settings.
	 */
	if (vif->type == NL80211_IFTYPE_MONITOR) {
		mvmvif->monitor_active = true;
		ret = iwl_mvm_update_quotas(mvm, false, NULL);
		if (ret)
			goto out_remove_binding;

		ret = iwl_mvm_add_snif_sta(mvm, vif);
		if (ret)
			goto out_remove_binding;

	}

	/* Handle binding during CSA */
	if (vif->type == NL80211_IFTYPE_AP) {
		iwl_mvm_update_quotas(mvm, false, NULL);
		iwl_mvm_mac_ctxt_changed(mvm, vif, false, NULL);
	}

	if (switching_chanctx && vif->type == NL80211_IFTYPE_STATION) {
		mvmvif->csa_bcn_pending = true;

		if (!fw_has_capa(&mvm->fw->ucode_capa,
				 IWL_UCODE_TLV_CAPA_CHANNEL_SWITCH_CMD)) {
			u32 duration = 3 * vif->bss_conf.beacon_int;

			/* Protect the session to make sure we hear the first
			 * beacon on the new channel.
			 */
			iwl_mvm_protect_session(mvm, vif, duration, duration,
						vif->bss_conf.beacon_int / 2,
						true);
		}

		iwl_mvm_update_quotas(mvm, false, NULL);
	}

	goto out;

out_remove_binding:
	iwl_mvm_binding_remove_vif(mvm, vif);
	iwl_mvm_power_update_mac(mvm);
out:
	if (ret)
		mvmvif->phy_ctxt = NULL;
	return ret;
}