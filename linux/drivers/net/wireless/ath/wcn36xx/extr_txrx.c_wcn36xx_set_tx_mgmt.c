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
struct wcn36xx_vif {scalar_t__ is_joining; int /*<<< orphan*/  self_dpu_desc_index; int /*<<< orphan*/  self_sta_index; } ;
struct wcn36xx_tx_bd {int dpu_ne; int ub; int ack_policy; int /*<<< orphan*/  queue_id; void* bd_rate; int /*<<< orphan*/  dpu_desc_idx; int /*<<< orphan*/  sta_index; } ;
struct wcn36xx {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct ieee80211_qos_hdr {int dummy; } ;
struct ieee80211_hdr_3addr {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; int /*<<< orphan*/  addr2; } ;

/* Variables and functions */
 scalar_t__ NL80211_BAND_5GHZ ; 
 scalar_t__ WCN36XX_BAND (struct wcn36xx*) ; 
 void* WCN36XX_BD_RATE_CTRL ; 
 void* WCN36XX_BD_RATE_MGMT ; 
 int /*<<< orphan*/  WCN36XX_TID ; 
 int /*<<< orphan*/  WCN36XX_TX_B_WQ_ID ; 
 int /*<<< orphan*/  WCN36XX_TX_U_WQ_ID ; 
 struct wcn36xx_vif* get_vif_by_addr (struct wcn36xx*,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_ctl (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_mgmt (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_probe_req (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_set_tx_pdu (struct wcn36xx_tx_bd*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_warn (char*) ; 

__attribute__((used)) static void wcn36xx_set_tx_mgmt(struct wcn36xx_tx_bd *bd,
				struct wcn36xx *wcn,
				struct wcn36xx_vif **vif_priv,
				struct sk_buff *skb,
				bool bcast)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	struct wcn36xx_vif *__vif_priv =
		get_vif_by_addr(wcn, hdr->addr2);
	bd->sta_index = __vif_priv->self_sta_index;
	bd->dpu_desc_idx = __vif_priv->self_dpu_desc_index;
	bd->dpu_ne = 1;

	/* default rate for unicast */
	if (ieee80211_is_mgmt(hdr->frame_control))
		bd->bd_rate = (WCN36XX_BAND(wcn) == NL80211_BAND_5GHZ) ?
			WCN36XX_BD_RATE_CTRL :
			WCN36XX_BD_RATE_MGMT;
	else if (ieee80211_is_ctl(hdr->frame_control))
		bd->bd_rate = WCN36XX_BD_RATE_CTRL;
	else
		wcn36xx_warn("frame control type unknown\n");

	/*
	 * In joining state trick hardware that probe is sent as
	 * unicast even if address is broadcast.
	 */
	if (__vif_priv->is_joining &&
	    ieee80211_is_probe_req(hdr->frame_control))
		bcast = false;

	if (bcast) {
		/* broadcast */
		bd->ub = 1;
		/* No ack needed not unicast */
		bd->ack_policy = 1;
		bd->queue_id = WCN36XX_TX_B_WQ_ID;
	} else
		bd->queue_id = WCN36XX_TX_U_WQ_ID;
	*vif_priv = __vif_priv;

	wcn36xx_set_tx_pdu(bd,
			   ieee80211_is_data_qos(hdr->frame_control) ?
			   sizeof(struct ieee80211_qos_hdr) :
			   sizeof(struct ieee80211_hdr_3addr),
			   skb->len, WCN36XX_TID);
}