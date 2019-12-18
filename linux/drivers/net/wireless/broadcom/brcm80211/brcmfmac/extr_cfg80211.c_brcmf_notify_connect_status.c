#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct ieee80211_channel {int dummy; } ;
struct brcmf_if {TYPE_2__* vif; int /*<<< orphan*/  ifidx; TYPE_1__* drvr; struct net_device* ndev; } ;
struct brcmf_event_msg {scalar_t__ event_code; scalar_t__ addr; int /*<<< orphan*/  flags; } ;
struct brcmf_cfg80211_profile {int /*<<< orphan*/  bssid; } ;
struct brcmf_cfg80211_info {int /*<<< orphan*/  vif_disabled; int /*<<< orphan*/  channel; int /*<<< orphan*/  wiphy; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_7__ {int /*<<< orphan*/  sme_state; struct brcmf_cfg80211_profile profile; } ;
struct TYPE_6__ {struct brcmf_cfg80211_info* config; } ;

/* Variables and functions */
 scalar_t__ BRCMF_E_DEAUTH ; 
 scalar_t__ BRCMF_E_DEAUTH_IND ; 
 scalar_t__ BRCMF_E_DISASSOC_IND ; 
 scalar_t__ BRCMF_E_LINK ; 
 int /*<<< orphan*/  BRCMF_VIF_STATUS_CONNECTED ; 
 int /*<<< orphan*/  BRCMF_VIF_STATUS_CONNECTING ; 
 int /*<<< orphan*/  CONN ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  brcmf_bss_connect_done (struct brcmf_cfg80211_info*,struct net_device*,struct brcmf_event_msg const*,int) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_inform_ibss (struct brcmf_cfg80211_info*,struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  brcmf_init_prof (int /*<<< orphan*/ ) ; 
 scalar_t__ brcmf_is_apmode (TYPE_2__*) ; 
 scalar_t__ brcmf_is_ibssmode (TYPE_2__*) ; 
 scalar_t__ brcmf_is_linkdown (struct brcmf_event_msg const*) ; 
 scalar_t__ brcmf_is_linkup (TYPE_2__*,struct brcmf_event_msg const*) ; 
 scalar_t__ brcmf_is_nonetwork (struct brcmf_cfg80211_info*,struct brcmf_event_msg const*) ; 
 int /*<<< orphan*/  brcmf_link_down (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_map_fw_linkdown_reason (struct brcmf_event_msg const*) ; 
 int /*<<< orphan*/  brcmf_net_setcarrier (struct brcmf_if*,int) ; 
 int /*<<< orphan*/  brcmf_notify_connect_status_ap (struct brcmf_cfg80211_info*,struct net_device*,struct brcmf_event_msg const*,void*) ; 
 int /*<<< orphan*/  brcmf_proto_delete_peer (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfg80211_ibss_joined (struct net_device*,scalar_t__,struct ieee80211_channel*,int /*<<< orphan*/ ) ; 
 struct net_device* cfg_to_ndev (struct brcmf_cfg80211_info*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct ieee80211_channel* ieee80211_get_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ndev_to_prof (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32
brcmf_notify_connect_status(struct brcmf_if *ifp,
			    const struct brcmf_event_msg *e, void *data)
{
	struct brcmf_cfg80211_info *cfg = ifp->drvr->config;
	struct net_device *ndev = ifp->ndev;
	struct brcmf_cfg80211_profile *profile = &ifp->vif->profile;
	struct ieee80211_channel *chan;
	s32 err = 0;

	if ((e->event_code == BRCMF_E_DEAUTH) ||
	    (e->event_code == BRCMF_E_DEAUTH_IND) ||
	    (e->event_code == BRCMF_E_DISASSOC_IND) ||
	    ((e->event_code == BRCMF_E_LINK) && (!e->flags))) {
		brcmf_proto_delete_peer(ifp->drvr, ifp->ifidx, (u8 *)e->addr);
	}

	if (brcmf_is_apmode(ifp->vif)) {
		err = brcmf_notify_connect_status_ap(cfg, ndev, e, data);
	} else if (brcmf_is_linkup(ifp->vif, e)) {
		brcmf_dbg(CONN, "Linkup\n");
		if (brcmf_is_ibssmode(ifp->vif)) {
			brcmf_inform_ibss(cfg, ndev, e->addr);
			chan = ieee80211_get_channel(cfg->wiphy, cfg->channel);
			memcpy(profile->bssid, e->addr, ETH_ALEN);
			cfg80211_ibss_joined(ndev, e->addr, chan, GFP_KERNEL);
			clear_bit(BRCMF_VIF_STATUS_CONNECTING,
				  &ifp->vif->sme_state);
			set_bit(BRCMF_VIF_STATUS_CONNECTED,
				&ifp->vif->sme_state);
		} else
			brcmf_bss_connect_done(cfg, ndev, e, true);
		brcmf_net_setcarrier(ifp, true);
	} else if (brcmf_is_linkdown(e)) {
		brcmf_dbg(CONN, "Linkdown\n");
		if (!brcmf_is_ibssmode(ifp->vif)) {
			brcmf_bss_connect_done(cfg, ndev, e, false);
			brcmf_link_down(ifp->vif,
					brcmf_map_fw_linkdown_reason(e));
			brcmf_init_prof(ndev_to_prof(ndev));
			if (ndev != cfg_to_ndev(cfg))
				complete(&cfg->vif_disabled);
			brcmf_net_setcarrier(ifp, false);
		}
	} else if (brcmf_is_nonetwork(cfg, e)) {
		if (brcmf_is_ibssmode(ifp->vif))
			clear_bit(BRCMF_VIF_STATUS_CONNECTING,
				  &ifp->vif->sme_state);
		else
			brcmf_bss_connect_done(cfg, ndev, e, false);
	}

	return err;
}