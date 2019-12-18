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
struct wcn36xx_vif {int /*<<< orphan*/  self_ucast_dpu_sign; int /*<<< orphan*/  self_dpu_desc_index; int /*<<< orphan*/  self_sta_index; } ;
struct wcn36xx_tx_bd {int dpu_ne; int ub; int ack_policy; int /*<<< orphan*/  dpu_sign; int /*<<< orphan*/  dpu_desc_idx; int /*<<< orphan*/  sta_index; int /*<<< orphan*/  bd_rate; } ;
struct wcn36xx_sta {int /*<<< orphan*/  tid; int /*<<< orphan*/  is_data_encrypted; int /*<<< orphan*/  dpu_desc_index; int /*<<< orphan*/  sta_index; int /*<<< orphan*/  bss_dpu_desc_index; int /*<<< orphan*/  bss_sta_index; int /*<<< orphan*/  ucast_dpu_sign; struct wcn36xx_vif* vif; } ;
struct wcn36xx {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct ieee80211_vif {scalar_t__ type; } ;
struct ieee80211_qos_hdr {int dummy; } ;
struct ieee80211_hdr_3addr {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; int /*<<< orphan*/  addr2; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  WCN36XX_BD_RATE_DATA ; 
 struct wcn36xx_vif* get_vif_by_addr (struct wcn36xx*,int /*<<< orphan*/ ) ; 
 int ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_nullfunc (int /*<<< orphan*/ ) ; 
 struct ieee80211_vif* wcn36xx_priv_to_vif (struct wcn36xx_vif*) ; 
 int /*<<< orphan*/  wcn36xx_set_tx_pdu (struct wcn36xx_tx_bd*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_tx_start_ampdu (struct wcn36xx*,struct wcn36xx_sta*,struct sk_buff*) ; 

__attribute__((used)) static void wcn36xx_set_tx_data(struct wcn36xx_tx_bd *bd,
				struct wcn36xx *wcn,
				struct wcn36xx_vif **vif_priv,
				struct wcn36xx_sta *sta_priv,
				struct sk_buff *skb,
				bool bcast)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	struct ieee80211_vif *vif = NULL;
	struct wcn36xx_vif *__vif_priv = NULL;
	bool is_data_qos;

	bd->bd_rate = WCN36XX_BD_RATE_DATA;

	/*
	 * For not unicast frames mac80211 will not set sta pointer so use
	 * self_sta_index instead.
	 */
	if (sta_priv) {
		__vif_priv = sta_priv->vif;
		vif = wcn36xx_priv_to_vif(__vif_priv);

		bd->dpu_sign = sta_priv->ucast_dpu_sign;
		if (vif->type == NL80211_IFTYPE_STATION) {
			bd->sta_index = sta_priv->bss_sta_index;
			bd->dpu_desc_idx = sta_priv->bss_dpu_desc_index;
		} else if (vif->type == NL80211_IFTYPE_AP ||
			   vif->type == NL80211_IFTYPE_ADHOC ||
			   vif->type == NL80211_IFTYPE_MESH_POINT) {
			bd->sta_index = sta_priv->sta_index;
			bd->dpu_desc_idx = sta_priv->dpu_desc_index;
		}
	} else {
		__vif_priv = get_vif_by_addr(wcn, hdr->addr2);
		bd->sta_index = __vif_priv->self_sta_index;
		bd->dpu_desc_idx = __vif_priv->self_dpu_desc_index;
		bd->dpu_sign = __vif_priv->self_ucast_dpu_sign;
	}

	if (ieee80211_is_nullfunc(hdr->frame_control) ||
	   (sta_priv && !sta_priv->is_data_encrypted))
		bd->dpu_ne = 1;

	if (bcast) {
		bd->ub = 1;
		bd->ack_policy = 1;
	}
	*vif_priv = __vif_priv;

	is_data_qos = ieee80211_is_data_qos(hdr->frame_control);

	wcn36xx_set_tx_pdu(bd,
			   is_data_qos ?
			   sizeof(struct ieee80211_qos_hdr) :
			   sizeof(struct ieee80211_hdr_3addr),
			   skb->len, sta_priv ? sta_priv->tid : 0);

	if (sta_priv && is_data_qos)
		wcn36xx_tx_start_ampdu(wcn, sta_priv, skb);
}