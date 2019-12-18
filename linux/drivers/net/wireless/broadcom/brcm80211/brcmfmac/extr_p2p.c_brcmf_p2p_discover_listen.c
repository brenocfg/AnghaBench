#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct brcmu_chan {int /*<<< orphan*/  chspec; int /*<<< orphan*/  bw; int /*<<< orphan*/  chnum; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_p2p_info {int /*<<< orphan*/  remain_on_channel_cookie; int /*<<< orphan*/  status; TYPE_3__* cfg; TYPE_1__* bss_idx; } ;
struct brcmf_cfg80211_vif {int /*<<< orphan*/  ifp; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_5__ {int /*<<< orphan*/  (* encchspec ) (struct brcmu_chan*) ;} ;
struct TYPE_6__ {TYPE_2__ d11inf; struct brcmf_pub* pub; } ;
struct TYPE_4__ {struct brcmf_cfg80211_vif* vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_P2P_STATUS_DISCOVER_LISTEN ; 
 int /*<<< orphan*/  BRCMU_CHAN_BW_20 ; 
 int /*<<< orphan*/  EPERM ; 
 size_t P2PAPI_BSSCFG_DEVICE ; 
 int /*<<< orphan*/  WL_P2P_DISC_ST_LISTEN ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*) ; 
 int /*<<< orphan*/  brcmf_p2p_set_discover_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct brcmu_chan*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32
brcmf_p2p_discover_listen(struct brcmf_p2p_info *p2p, u16 channel, u32 duration)
{
	struct brcmf_pub *drvr = p2p->cfg->pub;
	struct brcmf_cfg80211_vif *vif;
	struct brcmu_chan ch;
	s32 err = 0;

	vif = p2p->bss_idx[P2PAPI_BSSCFG_DEVICE].vif;
	if (!vif) {
		bphy_err(drvr, "Discovery is not set, so we have nothing to do\n");
		err = -EPERM;
		goto exit;
	}

	if (test_bit(BRCMF_P2P_STATUS_DISCOVER_LISTEN, &p2p->status)) {
		bphy_err(drvr, "Previous LISTEN is not completed yet\n");
		/* WAR: prevent cookie mismatch in wpa_supplicant return OK */
		goto exit;
	}

	ch.chnum = channel;
	ch.bw = BRCMU_CHAN_BW_20;
	p2p->cfg->d11inf.encchspec(&ch);
	err = brcmf_p2p_set_discover_state(vif->ifp, WL_P2P_DISC_ST_LISTEN,
					   ch.chspec, (u16)duration);
	if (!err) {
		set_bit(BRCMF_P2P_STATUS_DISCOVER_LISTEN, &p2p->status);
		p2p->remain_on_channel_cookie++;
	}
exit:
	return err;
}