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
struct wmi_tlv_scan_chan_list_cmd {int /*<<< orphan*/  num_scan_chans; } ;
struct wmi_tlv {scalar_t__ value; void* len; void* tag; } ;
struct wmi_scan_chan_list_arg {int n_channels; struct wmi_channel_arg* channels; } ;
struct wmi_channel_arg {int dummy; } ;
struct wmi_channel {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int WMI_TLV_TAG_ARRAY_STRUCT ; 
 int WMI_TLV_TAG_STRUCT_CHANNEL ; 
 int WMI_TLV_TAG_STRUCT_SCAN_CHAN_LIST_CMD ; 
 void* __cpu_to_le16 (int) ; 
 int /*<<< orphan*/  __cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,size_t) ; 
 int /*<<< orphan*/  ath10k_wmi_put_wmi_channel (struct wmi_channel*,struct wmi_channel_arg*) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_tlv_op_gen_scan_chan_list(struct ath10k *ar,
				     const struct wmi_scan_chan_list_arg *arg)
{
	struct wmi_tlv_scan_chan_list_cmd *cmd;
	struct wmi_channel *ci;
	struct wmi_channel_arg *ch;
	struct wmi_tlv *tlv;
	struct sk_buff *skb;
	size_t chans_len, len;
	int i;
	void *ptr, *chans;

	chans_len = arg->n_channels * (sizeof(*tlv) + sizeof(*ci));
	len = (sizeof(*tlv) + sizeof(*cmd)) +
	      (sizeof(*tlv) + chans_len);

	skb = ath10k_wmi_alloc_skb(ar, len);
	if (!skb)
		return ERR_PTR(-ENOMEM);

	ptr = (void *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_SCAN_CHAN_LIST_CMD);
	tlv->len = __cpu_to_le16(sizeof(*cmd));
	cmd = (void *)tlv->value;
	cmd->num_scan_chans = __cpu_to_le32(arg->n_channels);

	ptr += sizeof(*tlv);
	ptr += sizeof(*cmd);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_STRUCT);
	tlv->len = __cpu_to_le16(chans_len);
	chans = (void *)tlv->value;

	for (i = 0; i < arg->n_channels; i++) {
		ch = &arg->channels[i];

		tlv = chans;
		tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_CHANNEL);
		tlv->len = __cpu_to_le16(sizeof(*ci));
		ci = (void *)tlv->value;

		ath10k_wmi_put_wmi_channel(ci, ch);

		chans += sizeof(*tlv);
		chans += sizeof(*ci);
	}

	ptr += sizeof(*tlv);
	ptr += chans_len;

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv scan chan list\n");
	return skb;
}