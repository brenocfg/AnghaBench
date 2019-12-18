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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct wiphy {struct ieee80211_supported_band** bands; } ;
struct net_device {int dummy; } ;
struct ieee80211_supported_band {int /*<<< orphan*/  band; } ;
struct ieee80211_channel {int dummy; } ;
struct cfg80211_roam_info {int /*<<< orphan*/  resp_ie_len; int /*<<< orphan*/  resp_ie; int /*<<< orphan*/  req_ie_len; int /*<<< orphan*/  req_ie; int /*<<< orphan*/  bssid; struct ieee80211_channel* channel; } ;
struct brcmu_chan {scalar_t__ band; int /*<<< orphan*/  control_ch_num; int /*<<< orphan*/  chspec; } ;
struct brcmf_if {TYPE_2__* vif; } ;
struct brcmf_event_msg {int /*<<< orphan*/  addr; } ;
struct brcmf_cfg80211_profile {int /*<<< orphan*/  bssid; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* decchspec ) (struct brcmu_chan*) ;} ;
struct brcmf_cfg80211_info {TYPE_1__ d11inf; } ;
struct brcmf_cfg80211_connect_info {int /*<<< orphan*/  resp_ie_len; int /*<<< orphan*/  resp_ie; int /*<<< orphan*/  req_ie_len; int /*<<< orphan*/  req_ie; } ;
struct brcmf_bss_info_le {int /*<<< orphan*/  chanspec; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_4__ {int /*<<< orphan*/  sme_state; struct brcmf_cfg80211_profile profile; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_C_GET_BSS_INFO ; 
 int /*<<< orphan*/  BRCMF_VIF_STATUS_CONNECTED ; 
 scalar_t__ BRCMU_CHAN_BAND_2G ; 
 int /*<<< orphan*/  CONN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  WL_BSS_INFO_MAX ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int brcmf_fil_cmd_data_get (struct brcmf_if*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_get_assoc_ies (struct brcmf_cfg80211_info*,struct brcmf_if*) ; 
 int /*<<< orphan*/  brcmf_update_bss_info (struct brcmf_cfg80211_info*,struct brcmf_if*) ; 
 int /*<<< orphan*/  cfg80211_roamed (struct net_device*,struct cfg80211_roam_info*,int /*<<< orphan*/ ) ; 
 struct brcmf_cfg80211_connect_info* cfg_to_conn (struct brcmf_cfg80211_info*) ; 
 struct wiphy* cfg_to_wiphy (struct brcmf_cfg80211_info*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_channel_to_frequency (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee80211_channel* ieee80211_get_channel (struct wiphy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct brcmf_if* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct brcmu_chan*) ; 

__attribute__((used)) static s32
brcmf_bss_roaming_done(struct brcmf_cfg80211_info *cfg,
		       struct net_device *ndev,
		       const struct brcmf_event_msg *e)
{
	struct brcmf_if *ifp = netdev_priv(ndev);
	struct brcmf_cfg80211_profile *profile = &ifp->vif->profile;
	struct brcmf_cfg80211_connect_info *conn_info = cfg_to_conn(cfg);
	struct wiphy *wiphy = cfg_to_wiphy(cfg);
	struct ieee80211_channel *notify_channel = NULL;
	struct ieee80211_supported_band *band;
	struct brcmf_bss_info_le *bi;
	struct brcmu_chan ch;
	struct cfg80211_roam_info roam_info = {};
	u32 freq;
	s32 err = 0;
	u8 *buf;

	brcmf_dbg(TRACE, "Enter\n");

	brcmf_get_assoc_ies(cfg, ifp);
	memcpy(profile->bssid, e->addr, ETH_ALEN);
	brcmf_update_bss_info(cfg, ifp);

	buf = kzalloc(WL_BSS_INFO_MAX, GFP_KERNEL);
	if (buf == NULL) {
		err = -ENOMEM;
		goto done;
	}

	/* data sent to dongle has to be little endian */
	*(__le32 *)buf = cpu_to_le32(WL_BSS_INFO_MAX);
	err = brcmf_fil_cmd_data_get(ifp, BRCMF_C_GET_BSS_INFO,
				     buf, WL_BSS_INFO_MAX);

	if (err)
		goto done;

	bi = (struct brcmf_bss_info_le *)(buf + 4);
	ch.chspec = le16_to_cpu(bi->chanspec);
	cfg->d11inf.decchspec(&ch);

	if (ch.band == BRCMU_CHAN_BAND_2G)
		band = wiphy->bands[NL80211_BAND_2GHZ];
	else
		band = wiphy->bands[NL80211_BAND_5GHZ];

	freq = ieee80211_channel_to_frequency(ch.control_ch_num, band->band);
	notify_channel = ieee80211_get_channel(wiphy, freq);

done:
	kfree(buf);

	roam_info.channel = notify_channel;
	roam_info.bssid = profile->bssid;
	roam_info.req_ie = conn_info->req_ie;
	roam_info.req_ie_len = conn_info->req_ie_len;
	roam_info.resp_ie = conn_info->resp_ie;
	roam_info.resp_ie_len = conn_info->resp_ie_len;

	cfg80211_roamed(ndev, &roam_info, GFP_KERNEL);
	brcmf_dbg(CONN, "Report roaming result\n");

	set_bit(BRCMF_VIF_STATUS_CONNECTED, &ifp->vif->sme_state);
	brcmf_dbg(TRACE, "Exit\n");
	return err;
}