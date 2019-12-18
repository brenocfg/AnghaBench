#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_14__ {int* rates; int num_rates; } ;
struct wmi_peer_assoc_complete_arg {int peer_max_mpdu; int peer_ht_caps; int peer_rate_caps; int /*<<< orphan*/  peer_num_spatial_streams; TYPE_7__ peer_ht_rates; int /*<<< orphan*/  addr; int /*<<< orphan*/  peer_flags; int /*<<< orphan*/  peer_mpdu_density; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct TYPE_13__ {int* rx_mask; } ;
struct ieee80211_sta_ht_cap {int ampdu_factor; int cap; TYPE_6__ mcs; int /*<<< orphan*/  ampdu_density; int /*<<< orphan*/  ht_supported; } ;
struct ieee80211_sta {scalar_t__ bandwidth; int /*<<< orphan*/  rx_nss; struct ieee80211_sta_ht_cap ht_cap; } ;
struct cfg80211_chan_def {TYPE_1__* chan; } ;
struct TYPE_10__ {TYPE_2__* control; } ;
struct ath10k_vif {TYPE_3__ bitrate_mask; } ;
struct TYPE_12__ {TYPE_4__* peer_flags; } ;
struct ath10k {TYPE_5__ wmi; int /*<<< orphan*/  conf_mutex; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_11__ {int /*<<< orphan*/  stbc; int /*<<< orphan*/  bw40; int /*<<< orphan*/  ldbc; int /*<<< orphan*/  ht; } ;
struct TYPE_9__ {int* ht_mcs; scalar_t__ gi; int /*<<< orphan*/ * vht_mcs; } ;
struct TYPE_8__ {int band; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_MAC ; 
 int const BIT (int) ; 
 int IEEE80211_HT_CAP_LDPC_CODING ; 
 int IEEE80211_HT_CAP_RX_STBC ; 
 int IEEE80211_HT_CAP_RX_STBC_SHIFT ; 
 int IEEE80211_HT_CAP_SGI_20 ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
 int IEEE80211_HT_CAP_TX_STBC ; 
 int IEEE80211_HT_MAX_AMPDU_FACTOR ; 
 int IEEE80211_HT_MCS_MASK_LEN ; 
 scalar_t__ IEEE80211_STA_RX_BW_40 ; 
 scalar_t__ NL80211_TXRATE_FORCE_LGI ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int WMI_RC_CW40_FLAG ; 
 int WMI_RC_DS_FLAG ; 
 int WMI_RC_HT_FLAG ; 
 int WMI_RC_RX_STBC_FLAG_S ; 
 int WMI_RC_SGI_FLAG ; 
 int WMI_RC_TS_FLAG ; 
 int WMI_RC_TX_STBC_FLAG ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_mac_vif_chan (struct ieee80211_vif*,struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  ath10k_parse_mpdudensity (int /*<<< orphan*/ ) ; 
 scalar_t__ ath10k_peer_assoc_h_ht_masked (int const*) ; 
 scalar_t__ ath10k_peer_assoc_h_vht_masked (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ath10k_peer_assoc_h_ht(struct ath10k *ar,
				   struct ieee80211_vif *vif,
				   struct ieee80211_sta *sta,
				   struct wmi_peer_assoc_complete_arg *arg)
{
	const struct ieee80211_sta_ht_cap *ht_cap = &sta->ht_cap;
	struct ath10k_vif *arvif = (void *)vif->drv_priv;
	struct cfg80211_chan_def def;
	enum nl80211_band band;
	const u8 *ht_mcs_mask;
	const u16 *vht_mcs_mask;
	int i, n;
	u8 max_nss;
	u32 stbc;

	lockdep_assert_held(&ar->conf_mutex);

	if (WARN_ON(ath10k_mac_vif_chan(vif, &def)))
		return;

	if (!ht_cap->ht_supported)
		return;

	band = def.chan->band;
	ht_mcs_mask = arvif->bitrate_mask.control[band].ht_mcs;
	vht_mcs_mask = arvif->bitrate_mask.control[band].vht_mcs;

	if (ath10k_peer_assoc_h_ht_masked(ht_mcs_mask) &&
	    ath10k_peer_assoc_h_vht_masked(vht_mcs_mask))
		return;

	arg->peer_flags |= ar->wmi.peer_flags->ht;
	arg->peer_max_mpdu = (1 << (IEEE80211_HT_MAX_AMPDU_FACTOR +
				    ht_cap->ampdu_factor)) - 1;

	arg->peer_mpdu_density =
		ath10k_parse_mpdudensity(ht_cap->ampdu_density);

	arg->peer_ht_caps = ht_cap->cap;
	arg->peer_rate_caps |= WMI_RC_HT_FLAG;

	if (ht_cap->cap & IEEE80211_HT_CAP_LDPC_CODING)
		arg->peer_flags |= ar->wmi.peer_flags->ldbc;

	if (sta->bandwidth >= IEEE80211_STA_RX_BW_40) {
		arg->peer_flags |= ar->wmi.peer_flags->bw40;
		arg->peer_rate_caps |= WMI_RC_CW40_FLAG;
	}

	if (arvif->bitrate_mask.control[band].gi != NL80211_TXRATE_FORCE_LGI) {
		if (ht_cap->cap & IEEE80211_HT_CAP_SGI_20)
			arg->peer_rate_caps |= WMI_RC_SGI_FLAG;

		if (ht_cap->cap & IEEE80211_HT_CAP_SGI_40)
			arg->peer_rate_caps |= WMI_RC_SGI_FLAG;
	}

	if (ht_cap->cap & IEEE80211_HT_CAP_TX_STBC) {
		arg->peer_rate_caps |= WMI_RC_TX_STBC_FLAG;
		arg->peer_flags |= ar->wmi.peer_flags->stbc;
	}

	if (ht_cap->cap & IEEE80211_HT_CAP_RX_STBC) {
		stbc = ht_cap->cap & IEEE80211_HT_CAP_RX_STBC;
		stbc = stbc >> IEEE80211_HT_CAP_RX_STBC_SHIFT;
		stbc = stbc << WMI_RC_RX_STBC_FLAG_S;
		arg->peer_rate_caps |= stbc;
		arg->peer_flags |= ar->wmi.peer_flags->stbc;
	}

	if (ht_cap->mcs.rx_mask[1] && ht_cap->mcs.rx_mask[2])
		arg->peer_rate_caps |= WMI_RC_TS_FLAG;
	else if (ht_cap->mcs.rx_mask[1])
		arg->peer_rate_caps |= WMI_RC_DS_FLAG;

	for (i = 0, n = 0, max_nss = 0; i < IEEE80211_HT_MCS_MASK_LEN * 8; i++)
		if ((ht_cap->mcs.rx_mask[i / 8] & BIT(i % 8)) &&
		    (ht_mcs_mask[i / 8] & BIT(i % 8))) {
			max_nss = (i / 8) + 1;
			arg->peer_ht_rates.rates[n++] = i;
		}

	/*
	 * This is a workaround for HT-enabled STAs which break the spec
	 * and have no HT capabilities RX mask (no HT RX MCS map).
	 *
	 * As per spec, in section 20.3.5 Modulation and coding scheme (MCS),
	 * MCS 0 through 7 are mandatory in 20MHz with 800 ns GI at all STAs.
	 *
	 * Firmware asserts if such situation occurs.
	 */
	if (n == 0) {
		arg->peer_ht_rates.num_rates = 8;
		for (i = 0; i < arg->peer_ht_rates.num_rates; i++)
			arg->peer_ht_rates.rates[i] = i;
	} else {
		arg->peer_ht_rates.num_rates = n;
		arg->peer_num_spatial_streams = min(sta->rx_nss, max_nss);
	}

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac ht peer %pM mcs cnt %d nss %d\n",
		   arg->addr,
		   arg->peer_ht_rates.num_rates,
		   arg->peer_num_spatial_streams);
}