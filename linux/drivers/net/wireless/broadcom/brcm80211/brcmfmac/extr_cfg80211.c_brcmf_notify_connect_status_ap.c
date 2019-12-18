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
typedef  scalar_t__ u32 ;
struct station_info {int generation; int /*<<< orphan*/  assoc_req_ies_len; void* assoc_req_ies; } ;
struct net_device {int dummy; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_event_msg {scalar_t__ event_code; scalar_t__ reason; int /*<<< orphan*/  addr; int /*<<< orphan*/  datalen; } ;
struct brcmf_cfg80211_info {int /*<<< orphan*/  vif_disabled; struct brcmf_pub* pub; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 scalar_t__ BRCMF_E_ASSOC_IND ; 
 scalar_t__ BRCMF_E_DEAUTH ; 
 scalar_t__ BRCMF_E_DEAUTH_IND ; 
 scalar_t__ BRCMF_E_DISASSOC_IND ; 
 scalar_t__ BRCMF_E_LINK ; 
 scalar_t__ BRCMF_E_REASON_LINK_BSSCFG_DIS ; 
 scalar_t__ BRCMF_E_REASSOC_IND ; 
 scalar_t__ BRCMF_E_STATUS_SUCCESS ; 
 int /*<<< orphan*/  CONN ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  brcmf_fweh_event_name (scalar_t__) ; 
 int /*<<< orphan*/  cfg80211_del_sta (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_new_sta (struct net_device*,int /*<<< orphan*/ ,struct station_info*,int /*<<< orphan*/ ) ; 
 struct net_device* cfg_to_ndev (struct brcmf_cfg80211_info*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct station_info*) ; 
 struct station_info* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32
brcmf_notify_connect_status_ap(struct brcmf_cfg80211_info *cfg,
			       struct net_device *ndev,
			       const struct brcmf_event_msg *e, void *data)
{
	struct brcmf_pub *drvr = cfg->pub;
	static int generation;
	u32 event = e->event_code;
	u32 reason = e->reason;
	struct station_info *sinfo;

	brcmf_dbg(CONN, "event %s (%u), reason %d\n",
		  brcmf_fweh_event_name(event), event, reason);
	if (event == BRCMF_E_LINK && reason == BRCMF_E_REASON_LINK_BSSCFG_DIS &&
	    ndev != cfg_to_ndev(cfg)) {
		brcmf_dbg(CONN, "AP mode link down\n");
		complete(&cfg->vif_disabled);
		return 0;
	}

	if (((event == BRCMF_E_ASSOC_IND) || (event == BRCMF_E_REASSOC_IND)) &&
	    (reason == BRCMF_E_STATUS_SUCCESS)) {
		if (!data) {
			bphy_err(drvr, "No IEs present in ASSOC/REASSOC_IND\n");
			return -EINVAL;
		}

		sinfo = kzalloc(sizeof(*sinfo), GFP_KERNEL);
		if (!sinfo)
			return -ENOMEM;

		sinfo->assoc_req_ies = data;
		sinfo->assoc_req_ies_len = e->datalen;
		generation++;
		sinfo->generation = generation;
		cfg80211_new_sta(ndev, e->addr, sinfo, GFP_KERNEL);

		kfree(sinfo);
	} else if ((event == BRCMF_E_DISASSOC_IND) ||
		   (event == BRCMF_E_DEAUTH_IND) ||
		   (event == BRCMF_E_DEAUTH)) {
		cfg80211_del_sta(ndev, e->addr, GFP_KERNEL);
	}
	return 0;
}