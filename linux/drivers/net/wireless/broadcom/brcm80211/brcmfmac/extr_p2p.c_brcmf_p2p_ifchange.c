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
typedef  int /*<<< orphan*/  u16 ;
struct brcmf_pub {int dummy; } ;
struct brcmf_p2p_info {int /*<<< orphan*/  int_addr; TYPE_1__* bss_idx; } ;
struct brcmf_fil_p2p_if_le {int /*<<< orphan*/  addr; void* chspec; void* type; } ;
struct brcmf_cfg80211_vif {int /*<<< orphan*/  ifp; } ;
struct brcmf_cfg80211_info {struct brcmf_pub* pub; struct brcmf_p2p_info p2p; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  if_request ;
typedef  enum brcmf_fil_p2p_if_types { ____Placeholder_brcmf_fil_p2p_if_types } brcmf_fil_p2p_if_types ;
struct TYPE_2__ {struct brcmf_cfg80211_vif* vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_C_SET_SCB_TIMEOUT ; 
 int /*<<< orphan*/  BRCMF_E_IF_CHANGE ; 
 int /*<<< orphan*/  BRCMF_SCB_TIMEOUT_VALUE ; 
 int /*<<< orphan*/  BRCMF_VIF_EVENT_TIMEOUT ; 
 int EIO ; 
 int EPERM ; 
 size_t P2PAPI_BSSCFG_CONNECTION ; 
 size_t P2PAPI_BSSCFG_PRIMARY ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,...) ; 
 int /*<<< orphan*/  brcmf_cfg80211_arm_vif_event (struct brcmf_cfg80211_info*,struct brcmf_cfg80211_vif*) ; 
 int brcmf_cfg80211_wait_vif_event (struct brcmf_cfg80211_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int brcmf_fil_cmd_int_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int brcmf_fil_iovar_data_set (int /*<<< orphan*/ ,char*,struct brcmf_fil_p2p_if_le*,int) ; 
 int /*<<< orphan*/  brcmf_notify_escan_complete (struct brcmf_cfg80211_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  brcmf_p2p_get_current_chanspec (struct brcmf_p2p_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcmf_set_mpc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int brcmf_p2p_ifchange(struct brcmf_cfg80211_info *cfg,
		       enum brcmf_fil_p2p_if_types if_type)
{
	struct brcmf_p2p_info *p2p = &cfg->p2p;
	struct brcmf_pub *drvr = cfg->pub;
	struct brcmf_cfg80211_vif *vif;
	struct brcmf_fil_p2p_if_le if_request;
	s32 err;
	u16 chanspec;

	brcmf_dbg(TRACE, "Enter\n");

	vif = p2p->bss_idx[P2PAPI_BSSCFG_PRIMARY].vif;
	if (!vif) {
		bphy_err(drvr, "vif for P2PAPI_BSSCFG_PRIMARY does not exist\n");
		return -EPERM;
	}
	brcmf_notify_escan_complete(cfg, vif->ifp, true, true);
	vif = p2p->bss_idx[P2PAPI_BSSCFG_CONNECTION].vif;
	if (!vif) {
		bphy_err(drvr, "vif for P2PAPI_BSSCFG_CONNECTION does not exist\n");
		return -EPERM;
	}
	brcmf_set_mpc(vif->ifp, 0);

	/* In concurrency case, STA may be already associated in a particular */
	/* channel. so retrieve the current channel of primary interface and  */
	/* then start the virtual interface on that.                          */
	brcmf_p2p_get_current_chanspec(p2p, &chanspec);

	if_request.type = cpu_to_le16((u16)if_type);
	if_request.chspec = cpu_to_le16(chanspec);
	memcpy(if_request.addr, p2p->int_addr, sizeof(if_request.addr));

	brcmf_cfg80211_arm_vif_event(cfg, vif);
	err = brcmf_fil_iovar_data_set(vif->ifp, "p2p_ifupd", &if_request,
				       sizeof(if_request));
	if (err) {
		bphy_err(drvr, "p2p_ifupd FAILED, err=%d\n", err);
		brcmf_cfg80211_arm_vif_event(cfg, NULL);
		return err;
	}
	err = brcmf_cfg80211_wait_vif_event(cfg, BRCMF_E_IF_CHANGE,
					    BRCMF_VIF_EVENT_TIMEOUT);
	brcmf_cfg80211_arm_vif_event(cfg, NULL);
	if (!err)  {
		bphy_err(drvr, "No BRCMF_E_IF_CHANGE event received\n");
		return -EIO;
	}

	err = brcmf_fil_cmd_int_set(vif->ifp, BRCMF_C_SET_SCB_TIMEOUT,
				    BRCMF_SCB_TIMEOUT_VALUE);

	return err;
}