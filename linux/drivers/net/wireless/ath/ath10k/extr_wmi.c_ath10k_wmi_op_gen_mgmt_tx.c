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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_2__ peer_macaddr; void* buf_len; scalar_t__ tx_power; scalar_t__ tx_rate; void* vdev_id; } ;
struct wmi_mgmt_tx_cmd {int /*<<< orphan*/  buf; TYPE_3__ hdr; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct ath10k_vif {int vdev_id; } ;
struct ath10k_skb_cb {TYPE_1__* vif; } ;
struct ath10k {int dummy; } ;
struct TYPE_4__ {scalar_t__ drv_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 struct ath10k_skb_cb* ATH10K_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int IEEE80211_CCMP_MIC_LEN ; 
 int IEEE80211_FCTL_FTYPE ; 
 int IEEE80211_FCTL_STYPE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 void* __cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,struct sk_buff*,int,int,int) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,int) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_get_DA (struct ieee80211_hdr*) ; 
 scalar_t__ ieee80211_has_protected (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_action (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_deauth (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_disassoc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_mgmt (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  round_up (int,int) ; 
 int /*<<< orphan*/  trace_ath10k_tx_hdr (struct ath10k*,scalar_t__,int) ; 
 int /*<<< orphan*/  trace_ath10k_tx_payload (struct ath10k*,scalar_t__,int) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_op_gen_mgmt_tx(struct ath10k *ar, struct sk_buff *msdu)
{
	struct ath10k_skb_cb *cb = ATH10K_SKB_CB(msdu);
	struct ath10k_vif *arvif;
	struct wmi_mgmt_tx_cmd *cmd;
	struct ieee80211_hdr *hdr;
	struct sk_buff *skb;
	int len;
	u32 vdev_id;
	u32 buf_len = msdu->len;
	u16 fc;

	hdr = (struct ieee80211_hdr *)msdu->data;
	fc = le16_to_cpu(hdr->frame_control);

	if (cb->vif) {
		arvif = (void *)cb->vif->drv_priv;
		vdev_id = arvif->vdev_id;
	} else {
		vdev_id = 0;
	}

	if (WARN_ON_ONCE(!ieee80211_is_mgmt(hdr->frame_control)))
		return ERR_PTR(-EINVAL);

	len = sizeof(cmd->hdr) + msdu->len;

	if ((ieee80211_is_action(hdr->frame_control) ||
	     ieee80211_is_deauth(hdr->frame_control) ||
	     ieee80211_is_disassoc(hdr->frame_control)) &&
	     ieee80211_has_protected(hdr->frame_control)) {
		len += IEEE80211_CCMP_MIC_LEN;
		buf_len += IEEE80211_CCMP_MIC_LEN;
	}

	len = round_up(len, 4);

	skb = ath10k_wmi_alloc_skb(ar, len);
	if (!skb)
		return ERR_PTR(-ENOMEM);

	cmd = (struct wmi_mgmt_tx_cmd *)skb->data;

	cmd->hdr.vdev_id = __cpu_to_le32(vdev_id);
	cmd->hdr.tx_rate = 0;
	cmd->hdr.tx_power = 0;
	cmd->hdr.buf_len = __cpu_to_le32(buf_len);

	ether_addr_copy(cmd->hdr.peer_macaddr.addr, ieee80211_get_DA(hdr));
	memcpy(cmd->buf, msdu->data, msdu->len);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi mgmt tx skb %pK len %d ftype %02x stype %02x\n",
		   msdu, skb->len, fc & IEEE80211_FCTL_FTYPE,
		   fc & IEEE80211_FCTL_STYPE);
	trace_ath10k_tx_hdr(ar, skb->data, skb->len);
	trace_ath10k_tx_payload(ar, skb->data, skb->len);

	return skb;
}