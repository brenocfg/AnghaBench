#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct brcmf_pub {struct brcmf_cfg80211_info* config; } ;
struct brcmf_pno_scanresults_le {int /*<<< orphan*/  count; } ;
struct brcmf_pno_net_info_le {scalar_t__ SSID_len; scalar_t__ channel; int /*<<< orphan*/  SSID; } ;
struct brcmf_if {struct brcmf_pub* drvr; } ;
struct brcmf_event_msg {int datalen; scalar_t__ event_code; } ;
struct TYPE_8__ {int nd_data_completed; int /*<<< orphan*/  nd_data_wait; TYPE_3__* nd; TYPE_2__* nd_info; } ;
struct brcmf_cfg80211_info {TYPE_4__ wowl; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_5__ {scalar_t__ ssid_len; int /*<<< orphan*/  ssid; } ;
struct TYPE_7__ {int n_channels; int /*<<< orphan*/ * channels; TYPE_1__ ssid; } ;
struct TYPE_6__ {int n_matches; TYPE_3__** matches; } ;

/* Variables and functions */
 scalar_t__ BRCMF_E_PFN_NET_LOST ; 
 scalar_t__ CH_MAX_2G_CHANNEL ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ IEEE80211_MAX_SSID_LEN ; 
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  SCAN ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,int) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 struct brcmf_pno_net_info_le* brcmf_get_netinfo_array (struct brcmf_pno_scanresults_le*) ; 
 int /*<<< orphan*/  ieee80211_channel_to_frequency (scalar_t__,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32
brcmf_wowl_nd_results(struct brcmf_if *ifp, const struct brcmf_event_msg *e,
		      void *data)
{
	struct brcmf_pub *drvr = ifp->drvr;
	struct brcmf_cfg80211_info *cfg = drvr->config;
	struct brcmf_pno_scanresults_le *pfn_result;
	struct brcmf_pno_net_info_le *netinfo;

	brcmf_dbg(SCAN, "Enter\n");

	if (e->datalen < (sizeof(*pfn_result) + sizeof(*netinfo))) {
		brcmf_dbg(SCAN, "Event data to small. Ignore\n");
		return 0;
	}

	pfn_result = (struct brcmf_pno_scanresults_le *)data;

	if (e->event_code == BRCMF_E_PFN_NET_LOST) {
		brcmf_dbg(SCAN, "PFN NET LOST event. Ignore\n");
		return 0;
	}

	if (le32_to_cpu(pfn_result->count) < 1) {
		bphy_err(drvr, "Invalid result count, expected 1 (%d)\n",
			 le32_to_cpu(pfn_result->count));
		return -EINVAL;
	}

	netinfo = brcmf_get_netinfo_array(pfn_result);
	if (netinfo->SSID_len > IEEE80211_MAX_SSID_LEN)
		netinfo->SSID_len = IEEE80211_MAX_SSID_LEN;
	memcpy(cfg->wowl.nd->ssid.ssid, netinfo->SSID, netinfo->SSID_len);
	cfg->wowl.nd->ssid.ssid_len = netinfo->SSID_len;
	cfg->wowl.nd->n_channels = 1;
	cfg->wowl.nd->channels[0] =
		ieee80211_channel_to_frequency(netinfo->channel,
			netinfo->channel <= CH_MAX_2G_CHANNEL ?
					NL80211_BAND_2GHZ : NL80211_BAND_5GHZ);
	cfg->wowl.nd_info->n_matches = 1;
	cfg->wowl.nd_info->matches[0] = cfg->wowl.nd;

	/* Inform (the resume task) that the net detect information was recvd */
	cfg->wowl.nd_data_completed = true;
	wake_up(&cfg->wowl.nd_data_wait);

	return 0;
}