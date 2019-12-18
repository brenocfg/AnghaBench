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
struct brcmf_pub {int dummy; } ;
struct brcmf_p2p_info {int /*<<< orphan*/  status; TYPE_2__* bss_idx; TYPE_1__* cfg; } ;
struct brcmf_cfg80211_vif {int /*<<< orphan*/  ifp; } ;
typedef  int s32 ;
struct TYPE_4__ {struct brcmf_cfg80211_vif* vif; } ;
struct TYPE_3__ {struct brcmf_pub* pub; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_ENABLED ; 
 int /*<<< orphan*/  BRCMF_P2P_STATUS_ENABLED ; 
 int EPERM ; 
 int /*<<< orphan*/  INFO ; 
 size_t P2PAPI_BSSCFG_DEVICE ; 
 size_t P2PAPI_BSSCFG_PRIMARY ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  WL_P2P_DISC_ST_SCAN ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,...) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int brcmf_fil_bsscfg_int_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int brcmf_fil_iovar_int_set (int /*<<< orphan*/ ,char*,int) ; 
 int brcmf_p2p_set_discover_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int brcmf_p2p_enable_discovery(struct brcmf_p2p_info *p2p)
{
	struct brcmf_pub *drvr = p2p->cfg->pub;
	struct brcmf_cfg80211_vif *vif;
	s32 ret = 0;

	brcmf_dbg(TRACE, "enter\n");
	vif = p2p->bss_idx[P2PAPI_BSSCFG_DEVICE].vif;
	if (!vif) {
		bphy_err(drvr, "P2P config device not available\n");
		ret = -EPERM;
		goto exit;
	}

	if (test_bit(BRCMF_P2P_STATUS_ENABLED, &p2p->status)) {
		brcmf_dbg(INFO, "P2P config device already configured\n");
		goto exit;
	}

	/* Re-initialize P2P Discovery in the firmware */
	vif = p2p->bss_idx[P2PAPI_BSSCFG_PRIMARY].vif;
	ret = brcmf_fil_iovar_int_set(vif->ifp, "p2p_disc", 1);
	if (ret < 0) {
		bphy_err(drvr, "set p2p_disc error\n");
		goto exit;
	}
	vif = p2p->bss_idx[P2PAPI_BSSCFG_DEVICE].vif;
	ret = brcmf_p2p_set_discover_state(vif->ifp, WL_P2P_DISC_ST_SCAN, 0, 0);
	if (ret < 0) {
		bphy_err(drvr, "unable to set WL_P2P_DISC_ST_SCAN\n");
		goto exit;
	}

	/*
	 * Set wsec to any non-zero value in the discovery bsscfg
	 * to ensure our P2P probe responses have the privacy bit
	 * set in the 802.11 WPA IE. Some peer devices may not
	 * initiate WPS with us if this bit is not set.
	 */
	ret = brcmf_fil_bsscfg_int_set(vif->ifp, "wsec", AES_ENABLED);
	if (ret < 0) {
		bphy_err(drvr, "wsec error %d\n", ret);
		goto exit;
	}

	set_bit(BRCMF_P2P_STATUS_ENABLED, &p2p->status);
exit:
	return ret;
}