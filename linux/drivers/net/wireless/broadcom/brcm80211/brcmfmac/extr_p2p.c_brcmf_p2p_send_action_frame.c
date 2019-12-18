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
typedef  scalar_t__ uint ;
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct brcmf_pub {int dummy; } ;
struct afx_hdl {scalar_t__ my_listen_chan; int /*<<< orphan*/  peer_chan; scalar_t__ peer_listen_chan; int /*<<< orphan*/  tx_dst_addr; } ;
struct brcmf_p2p_info {scalar_t__ next_af_subtype; int gon_req_action; scalar_t__ af_sent_channel; int block_gon_req_tx; int /*<<< orphan*/  status; int /*<<< orphan*/  wait_next_af; scalar_t__ af_tx_sent_jiffies; struct afx_hdl afx_hdl; TYPE_3__* bss_idx; } ;
struct brcmf_if {int dummy; } ;
struct brcmf_fil_action_frame_le {scalar_t__* data; int /*<<< orphan*/  da; int /*<<< orphan*/  len; } ;
struct brcmf_fil_af_params_le {void* dwell_time; void* channel; struct brcmf_fil_action_frame_le action_frame; } ;
struct brcmf_config_af_params {int mpc_onoff; int search_channel; int extra_listen; } ;
struct brcmf_cfg80211_info {int /*<<< orphan*/  scan_status; struct brcmf_pub* pub; struct brcmf_p2p_info p2p; } ;
typedef  scalar_t__ s32 ;
struct TYPE_6__ {TYPE_2__* vif; } ;
struct TYPE_4__ {scalar_t__ probe_req_ie_len; } ;
struct TYPE_5__ {TYPE_1__ saved_ie; int /*<<< orphan*/  sme_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_P2P_STATUS_GO_NEG_PHASE ; 
 int /*<<< orphan*/  BRCMF_P2P_STATUS_SENDING_ACT_FRAME ; 
 int /*<<< orphan*/  BRCMF_P2P_STATUS_WAITING_NEXT_ACT_FRAME ; 
 int /*<<< orphan*/  BRCMF_P2P_STATUS_WAITING_NEXT_AF_LISTEN ; 
 int /*<<< orphan*/  BRCMF_SCAN_STATUS_BUSY ; 
 int /*<<< orphan*/  BRCMF_VIF_STATUS_CONNECTING ; 
 size_t DOT11_ACTION_ACT_OFF ; 
 size_t DOT11_ACTION_CAT_OFF ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  INFO ; 
 scalar_t__ IS_P2P_SOCIAL_CHANNEL (scalar_t__) ; 
 size_t P2PAPI_BSSCFG_DEVICE ; 
 size_t P2PAPI_BSSCFG_PRIMARY ; 
 scalar_t__ P2PSD_ACTION_ID_GAS_CREQ ; 
 scalar_t__ P2PSD_ACTION_ID_GAS_CRESP ; 
 scalar_t__ P2PSD_ACTION_ID_GAS_IREQ ; 
 scalar_t__ P2PSD_ACTION_ID_GAS_IRESP ; 
 int /*<<< orphan*/  P2P_AF_DWELL_TIME ; 
 int /*<<< orphan*/  P2P_AF_MED_DWELL_TIME ; 
 int /*<<< orphan*/  P2P_AF_MIN_DWELL_TIME ; 
 scalar_t__ P2P_AF_TX_MAX_RETRY ; 
 scalar_t__ P2P_INVALID_CHANNEL ; 
 scalar_t__ P2P_PAF_SUBTYPE_INVALID ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,...) ; 
 int /*<<< orphan*/  brcmf_abort_scanning (struct brcmf_cfg80211_info*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  brcmf_notify_escan_complete (struct brcmf_cfg80211_info*,struct brcmf_if*,int,int) ; 
 scalar_t__ brcmf_p2p_af_searching_channel (struct brcmf_p2p_info*) ; 
 int /*<<< orphan*/  brcmf_p2p_discover_listen (struct brcmf_p2p_info*,scalar_t__,scalar_t__) ; 
 scalar_t__ brcmf_p2p_is_gas_action (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ brcmf_p2p_is_p2p_action (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ brcmf_p2p_is_pub_action (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_p2p_print_actframe (int,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ brcmf_p2p_pub_af_tx (struct brcmf_cfg80211_info*,struct brcmf_fil_af_params_le*,struct brcmf_config_af_params*) ; 
 int /*<<< orphan*/  brcmf_p2p_tx_action_frame (struct brcmf_p2p_info*,struct brcmf_fil_af_params_le*) ; 
 int /*<<< orphan*/  brcmf_set_mpc (struct brcmf_if*,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct brcmf_if* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

bool brcmf_p2p_send_action_frame(struct brcmf_cfg80211_info *cfg,
				 struct net_device *ndev,
				 struct brcmf_fil_af_params_le *af_params)
{
	struct brcmf_p2p_info *p2p = &cfg->p2p;
	struct brcmf_if *ifp = netdev_priv(ndev);
	struct brcmf_fil_action_frame_le *action_frame;
	struct brcmf_config_af_params config_af_params;
	struct afx_hdl *afx_hdl = &p2p->afx_hdl;
	struct brcmf_pub *drvr = cfg->pub;
	u16 action_frame_len;
	bool ack = false;
	u8 category;
	u8 action;
	s32 tx_retry;
	s32 extra_listen_time;
	uint delta_ms;

	action_frame = &af_params->action_frame;
	action_frame_len = le16_to_cpu(action_frame->len);

	brcmf_p2p_print_actframe(true, action_frame->data, action_frame_len);

	/* Add the default dwell time. Dwell time to stay off-channel */
	/* to wait for a response action frame after transmitting an  */
	/* GO Negotiation action frame                                */
	af_params->dwell_time = cpu_to_le32(P2P_AF_DWELL_TIME);

	category = action_frame->data[DOT11_ACTION_CAT_OFF];
	action = action_frame->data[DOT11_ACTION_ACT_OFF];

	/* initialize variables */
	p2p->next_af_subtype = P2P_PAF_SUBTYPE_INVALID;
	p2p->gon_req_action = false;

	/* config parameters */
	config_af_params.mpc_onoff = -1;
	config_af_params.search_channel = false;
	config_af_params.extra_listen = false;

	if (brcmf_p2p_is_pub_action(action_frame->data, action_frame_len)) {
		/* p2p public action frame process */
		if (brcmf_p2p_pub_af_tx(cfg, af_params, &config_af_params)) {
			/* Just send unknown subtype frame with */
			/* default parameters.                  */
			bphy_err(drvr, "P2P Public action frame, unknown subtype.\n");
		}
	} else if (brcmf_p2p_is_gas_action(action_frame->data,
					   action_frame_len)) {
		/* service discovery process */
		if (action == P2PSD_ACTION_ID_GAS_IREQ ||
		    action == P2PSD_ACTION_ID_GAS_CREQ) {
			/* configure service discovery query frame */
			config_af_params.search_channel = true;

			/* save next af suptype to cancel */
			/* remaining dwell time           */
			p2p->next_af_subtype = action + 1;

			af_params->dwell_time =
				cpu_to_le32(P2P_AF_MED_DWELL_TIME);
		} else if (action == P2PSD_ACTION_ID_GAS_IRESP ||
			   action == P2PSD_ACTION_ID_GAS_CRESP) {
			/* configure service discovery response frame */
			af_params->dwell_time =
				cpu_to_le32(P2P_AF_MIN_DWELL_TIME);
		} else {
			bphy_err(drvr, "Unknown action type: %d\n", action);
			goto exit;
		}
	} else if (brcmf_p2p_is_p2p_action(action_frame->data,
					   action_frame_len)) {
		/* do not configure anything. it will be */
		/* sent with a default configuration     */
	} else {
		bphy_err(drvr, "Unknown Frame: category 0x%x, action 0x%x\n",
			 category, action);
		return false;
	}

	/* if connecting on primary iface, sleep for a while before sending
	 * af tx for VSDB
	 */
	if (test_bit(BRCMF_VIF_STATUS_CONNECTING,
		     &p2p->bss_idx[P2PAPI_BSSCFG_PRIMARY].vif->sme_state))
		msleep(50);

	/* if scan is ongoing, abort current scan. */
	if (test_bit(BRCMF_SCAN_STATUS_BUSY, &cfg->scan_status))
		brcmf_abort_scanning(cfg);

	memcpy(afx_hdl->tx_dst_addr, action_frame->da, ETH_ALEN);

	/* To make sure to send successfully action frame, turn off mpc */
	if (config_af_params.mpc_onoff == 0)
		brcmf_set_mpc(ifp, 0);

	/* set status and destination address before sending af */
	if (p2p->next_af_subtype != P2P_PAF_SUBTYPE_INVALID) {
		/* set status to cancel the remained dwell time in rx process */
		set_bit(BRCMF_P2P_STATUS_WAITING_NEXT_ACT_FRAME, &p2p->status);
	}

	p2p->af_sent_channel = 0;
	set_bit(BRCMF_P2P_STATUS_SENDING_ACT_FRAME, &p2p->status);
	/* validate channel and p2p ies */
	if (config_af_params.search_channel &&
	    IS_P2P_SOCIAL_CHANNEL(le32_to_cpu(af_params->channel)) &&
	    p2p->bss_idx[P2PAPI_BSSCFG_DEVICE].vif->saved_ie.probe_req_ie_len) {
		afx_hdl = &p2p->afx_hdl;
		afx_hdl->peer_listen_chan = le32_to_cpu(af_params->channel);

		if (brcmf_p2p_af_searching_channel(p2p) ==
							P2P_INVALID_CHANNEL) {
			bphy_err(drvr, "Couldn't find peer's channel.\n");
			goto exit;
		}

		/* Abort scan even for VSDB scenarios. Scan gets aborted in
		 * firmware but after the check of piggyback algorithm. To take
		 * care of current piggback algo, lets abort the scan here
		 * itself.
		 */
		brcmf_notify_escan_complete(cfg, ifp, true, true);

		/* update channel */
		af_params->channel = cpu_to_le32(afx_hdl->peer_chan);
	}

	tx_retry = 0;
	while (!p2p->block_gon_req_tx &&
	       (ack == false) && (tx_retry < P2P_AF_TX_MAX_RETRY)) {
		ack = !brcmf_p2p_tx_action_frame(p2p, af_params);
		tx_retry++;
	}
	if (ack == false) {
		bphy_err(drvr, "Failed to send Action Frame(retry %d)\n",
			 tx_retry);
		clear_bit(BRCMF_P2P_STATUS_GO_NEG_PHASE, &p2p->status);
	}

exit:
	clear_bit(BRCMF_P2P_STATUS_SENDING_ACT_FRAME, &p2p->status);

	/* WAR: sometimes dongle does not keep the dwell time of 'actframe'.
	 * if we coundn't get the next action response frame and dongle does
	 * not keep the dwell time, go to listen state again to get next action
	 * response frame.
	 */
	if (ack && config_af_params.extra_listen && !p2p->block_gon_req_tx &&
	    test_bit(BRCMF_P2P_STATUS_WAITING_NEXT_ACT_FRAME, &p2p->status) &&
	    p2p->af_sent_channel == afx_hdl->my_listen_chan) {
		delta_ms = jiffies_to_msecs(jiffies - p2p->af_tx_sent_jiffies);
		if (le32_to_cpu(af_params->dwell_time) > delta_ms)
			extra_listen_time = le32_to_cpu(af_params->dwell_time) -
					    delta_ms;
		else
			extra_listen_time = 0;
		if (extra_listen_time > 50) {
			set_bit(BRCMF_P2P_STATUS_WAITING_NEXT_AF_LISTEN,
				&p2p->status);
			brcmf_dbg(INFO, "Wait more time! actual af time:%d, calculated extra listen:%d\n",
				  le32_to_cpu(af_params->dwell_time),
				  extra_listen_time);
			extra_listen_time += 100;
			if (!brcmf_p2p_discover_listen(p2p,
						       p2p->af_sent_channel,
						       extra_listen_time)) {
				unsigned long duration;

				extra_listen_time += 100;
				duration = msecs_to_jiffies(extra_listen_time);
				wait_for_completion_timeout(&p2p->wait_next_af,
							    duration);
			}
			clear_bit(BRCMF_P2P_STATUS_WAITING_NEXT_AF_LISTEN,
				  &p2p->status);
		}
	}

	if (p2p->block_gon_req_tx) {
		/* if ack is true, supplicant will wait more time(100ms).
		 * so we will return it as a success to get more time .
		 */
		p2p->block_gon_req_tx = false;
		ack = true;
	}

	clear_bit(BRCMF_P2P_STATUS_WAITING_NEXT_ACT_FRAME, &p2p->status);
	/* if all done, turn mpc on again */
	if (config_af_params.mpc_onoff == 1)
		brcmf_set_mpc(ifp, 1);

	return ack;
}