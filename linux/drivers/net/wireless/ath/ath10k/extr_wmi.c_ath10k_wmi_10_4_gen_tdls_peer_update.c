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
typedef  int u32 ;
struct wmi_tdls_peer_update_cmd_arg {int vdev_id; int peer_state; int /*<<< orphan*/  addr; } ;
struct wmi_tdls_peer_capabilities {int /*<<< orphan*/ * peer_chan_list; void* pref_offchan_bw; void* pref_offchan_num; void* is_peer_responder; int /*<<< orphan*/ * peer_operclass; void* peer_operclass_len; void* peer_chan_len; void* self_curr_operclass; void* peer_curr_operclass; void* off_chan_support; void* buff_sta_support; void* peer_qos; } ;
struct wmi_tdls_peer_capab_arg {int peer_chan_len; int buff_sta_support; int off_chan_support; int peer_curr_operclass; int self_curr_operclass; int peer_operclass_len; int is_peer_responder; int pref_offchan_num; int pref_offchan_bw; int /*<<< orphan*/ * peer_operclass; int /*<<< orphan*/  peer_max_sp; int /*<<< orphan*/  peer_uapsd_queues; } ;
struct wmi_channel_arg {int dummy; } ;
struct wmi_channel {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct wmi_10_4_tdls_peer_update_cmd {struct wmi_tdls_peer_capabilities peer_capab; void* peer_state; TYPE_1__ peer_macaddr; void* vdev_id; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int WMI_TDLS_MAX_SUPP_OPER_CLASSES ; 
 void* __cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int,int,int) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,int) ; 
 int ath10k_wmi_prepare_peer_qos (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_wmi_put_wmi_channel (struct wmi_channel*,struct wmi_channel_arg const*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_10_4_gen_tdls_peer_update(struct ath10k *ar,
				     const struct wmi_tdls_peer_update_cmd_arg *arg,
				     const struct wmi_tdls_peer_capab_arg *cap,
				     const struct wmi_channel_arg *chan_arg)
{
	struct wmi_10_4_tdls_peer_update_cmd *cmd;
	struct wmi_tdls_peer_capabilities *peer_cap;
	struct wmi_channel *chan;
	struct sk_buff *skb;
	u32 peer_qos;
	int len, chan_len;
	int i;

	/* tdls peer update cmd has place holder for one channel*/
	chan_len = cap->peer_chan_len ? (cap->peer_chan_len - 1) : 0;

	len = sizeof(*cmd) + chan_len * sizeof(*chan);

	skb = ath10k_wmi_alloc_skb(ar, len);
	if (!skb)
		return ERR_PTR(-ENOMEM);

	memset(skb->data, 0, sizeof(*cmd));

	cmd = (struct wmi_10_4_tdls_peer_update_cmd *)skb->data;
	cmd->vdev_id = __cpu_to_le32(arg->vdev_id);
	ether_addr_copy(cmd->peer_macaddr.addr, arg->addr);
	cmd->peer_state = __cpu_to_le32(arg->peer_state);

	peer_qos = ath10k_wmi_prepare_peer_qos(cap->peer_uapsd_queues,
					       cap->peer_max_sp);

	peer_cap = &cmd->peer_capab;
	peer_cap->peer_qos = __cpu_to_le32(peer_qos);
	peer_cap->buff_sta_support = __cpu_to_le32(cap->buff_sta_support);
	peer_cap->off_chan_support = __cpu_to_le32(cap->off_chan_support);
	peer_cap->peer_curr_operclass = __cpu_to_le32(cap->peer_curr_operclass);
	peer_cap->self_curr_operclass = __cpu_to_le32(cap->self_curr_operclass);
	peer_cap->peer_chan_len = __cpu_to_le32(cap->peer_chan_len);
	peer_cap->peer_operclass_len = __cpu_to_le32(cap->peer_operclass_len);

	for (i = 0; i < WMI_TDLS_MAX_SUPP_OPER_CLASSES; i++)
		peer_cap->peer_operclass[i] = cap->peer_operclass[i];

	peer_cap->is_peer_responder = __cpu_to_le32(cap->is_peer_responder);
	peer_cap->pref_offchan_num = __cpu_to_le32(cap->pref_offchan_num);
	peer_cap->pref_offchan_bw = __cpu_to_le32(cap->pref_offchan_bw);

	for (i = 0; i < cap->peer_chan_len; i++) {
		chan = (struct wmi_channel *)&peer_cap->peer_chan_list[i];
		ath10k_wmi_put_wmi_channel(chan, &chan_arg[i]);
	}

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi tdls peer update vdev %i state %d n_chans %u\n",
		   arg->vdev_id, arg->peer_state, cap->peer_chan_len);
	return skb;
}