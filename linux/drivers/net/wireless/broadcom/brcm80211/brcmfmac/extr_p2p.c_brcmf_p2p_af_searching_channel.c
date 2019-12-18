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
struct afx_hdl {int is_active; scalar_t__ peer_chan; int is_listen; scalar_t__ my_listen_chan; int /*<<< orphan*/  act_frm_scan; int /*<<< orphan*/  afx_work; } ;
struct brcmf_p2p_info {int /*<<< orphan*/  status; TYPE_1__* bss_idx; struct afx_hdl afx_hdl; } ;
struct brcmf_cfg80211_vif {int /*<<< orphan*/  sme_state; } ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {struct brcmf_cfg80211_vif* vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_P2P_STATUS_FINDING_COMMON_CHANNEL ; 
 int /*<<< orphan*/  BRCMF_VIF_STATUS_CONNECTED ; 
 int /*<<< orphan*/  BRCMF_VIF_STATUS_CONNECTING ; 
 size_t P2PAPI_BSSCFG_PRIMARY ; 
 int /*<<< orphan*/  P2P_AF_FRM_SCAN_MAX_WAIT ; 
 scalar_t__ P2P_CHANNEL_SYNC_RETRY ; 
 int /*<<< orphan*/  P2P_DEFAULT_SLEEP_TIME_VSDB ; 
 scalar_t__ P2P_INVALID_CHANNEL ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 brcmf_p2p_af_searching_channel(struct brcmf_p2p_info *p2p)
{
	struct afx_hdl *afx_hdl = &p2p->afx_hdl;
	struct brcmf_cfg80211_vif *pri_vif;
	s32 retry;

	brcmf_dbg(TRACE, "Enter\n");

	pri_vif = p2p->bss_idx[P2PAPI_BSSCFG_PRIMARY].vif;

	reinit_completion(&afx_hdl->act_frm_scan);
	set_bit(BRCMF_P2P_STATUS_FINDING_COMMON_CHANNEL, &p2p->status);
	afx_hdl->is_active = true;
	afx_hdl->peer_chan = P2P_INVALID_CHANNEL;

	/* Loop to wait until we find a peer's channel or the
	 * pending action frame tx is cancelled.
	 */
	retry = 0;
	while ((retry < P2P_CHANNEL_SYNC_RETRY) &&
	       (afx_hdl->peer_chan == P2P_INVALID_CHANNEL)) {
		afx_hdl->is_listen = false;
		brcmf_dbg(TRACE, "Scheduling action frame for sending.. (%d)\n",
			  retry);
		/* search peer on peer's listen channel */
		schedule_work(&afx_hdl->afx_work);
		wait_for_completion_timeout(&afx_hdl->act_frm_scan,
					    P2P_AF_FRM_SCAN_MAX_WAIT);
		if ((afx_hdl->peer_chan != P2P_INVALID_CHANNEL) ||
		    (!test_bit(BRCMF_P2P_STATUS_FINDING_COMMON_CHANNEL,
			       &p2p->status)))
			break;

		if (afx_hdl->my_listen_chan) {
			brcmf_dbg(TRACE, "Scheduling listen peer, channel=%d\n",
				  afx_hdl->my_listen_chan);
			/* listen on my listen channel */
			afx_hdl->is_listen = true;
			schedule_work(&afx_hdl->afx_work);
			wait_for_completion_timeout(&afx_hdl->act_frm_scan,
						    P2P_AF_FRM_SCAN_MAX_WAIT);
		}
		if ((afx_hdl->peer_chan != P2P_INVALID_CHANNEL) ||
		    (!test_bit(BRCMF_P2P_STATUS_FINDING_COMMON_CHANNEL,
			       &p2p->status)))
			break;
		retry++;

		/* if sta is connected or connecting, sleep for a while before
		 * retry af tx or finding a peer
		 */
		if (test_bit(BRCMF_VIF_STATUS_CONNECTED, &pri_vif->sme_state) ||
		    test_bit(BRCMF_VIF_STATUS_CONNECTING, &pri_vif->sme_state))
			msleep(P2P_DEFAULT_SLEEP_TIME_VSDB);
	}

	brcmf_dbg(TRACE, "Completed search/listen peer_chan=%d\n",
		  afx_hdl->peer_chan);
	afx_hdl->is_active = false;

	clear_bit(BRCMF_P2P_STATUS_FINDING_COMMON_CHANNEL, &p2p->status);

	return afx_hdl->peer_chan;
}