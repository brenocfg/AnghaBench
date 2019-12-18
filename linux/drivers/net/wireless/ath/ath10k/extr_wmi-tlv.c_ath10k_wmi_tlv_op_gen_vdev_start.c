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
struct wmi_vdev_start_request_arg {int ssid_len; int vdev_id; int bcn_intval; int dtim_period; int bcn_tx_rate; int bcn_tx_power; int disable_hw_ack; int /*<<< orphan*/  channel; int /*<<< orphan*/  ssid; scalar_t__ pmf_enabled; scalar_t__ hidden_ssid; } ;
struct TYPE_2__ {int /*<<< orphan*/  ssid; void* ssid_len; } ;
struct wmi_tlv_vdev_start_cmd {TYPE_1__ ssid; void* disable_hw_ack; void* bcn_tx_power; void* bcn_tx_rate; void* flags; void* dtim_period; void* bcn_intval; void* vdev_id; } ;
struct wmi_tlv {void* len; void* tag; scalar_t__ value; } ;
struct wmi_channel {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int WMI_TLV_TAG_ARRAY_STRUCT ; 
 int WMI_TLV_TAG_STRUCT_CHANNEL ; 
 int WMI_TLV_TAG_STRUCT_VDEV_START_REQUEST_CMD ; 
 int WMI_VDEV_START_HIDDEN_SSID ; 
 int WMI_VDEV_START_PMF_ENABLED ; 
 void* __cpu_to_le16 (int) ; 
 void* __cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,size_t) ; 
 int /*<<< orphan*/  ath10k_wmi_put_wmi_channel (struct wmi_channel*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_tlv_op_gen_vdev_start(struct ath10k *ar,
				 const struct wmi_vdev_start_request_arg *arg,
				 bool restart)
{
	struct wmi_tlv_vdev_start_cmd *cmd;
	struct wmi_channel *ch;
	struct wmi_tlv *tlv;
	struct sk_buff *skb;
	size_t len;
	void *ptr;
	u32 flags = 0;

	if (WARN_ON(arg->hidden_ssid && !arg->ssid))
		return ERR_PTR(-EINVAL);
	if (WARN_ON(arg->ssid_len > sizeof(cmd->ssid.ssid)))
		return ERR_PTR(-EINVAL);

	len = (sizeof(*tlv) + sizeof(*cmd)) +
	      (sizeof(*tlv) + sizeof(*ch)) +
	      (sizeof(*tlv) + 0);
	skb = ath10k_wmi_alloc_skb(ar, len);
	if (!skb)
		return ERR_PTR(-ENOMEM);

	if (arg->hidden_ssid)
		flags |= WMI_VDEV_START_HIDDEN_SSID;
	if (arg->pmf_enabled)
		flags |= WMI_VDEV_START_PMF_ENABLED;

	ptr = (void *)skb->data;

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_VDEV_START_REQUEST_CMD);
	tlv->len = __cpu_to_le16(sizeof(*cmd));
	cmd = (void *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(arg->vdev_id);
	cmd->bcn_intval = __cpu_to_le32(arg->bcn_intval);
	cmd->dtim_period = __cpu_to_le32(arg->dtim_period);
	cmd->flags = __cpu_to_le32(flags);
	cmd->bcn_tx_rate = __cpu_to_le32(arg->bcn_tx_rate);
	cmd->bcn_tx_power = __cpu_to_le32(arg->bcn_tx_power);
	cmd->disable_hw_ack = __cpu_to_le32(arg->disable_hw_ack);

	if (arg->ssid) {
		cmd->ssid.ssid_len = __cpu_to_le32(arg->ssid_len);
		memcpy(cmd->ssid.ssid, arg->ssid, arg->ssid_len);
	}

	ptr += sizeof(*tlv);
	ptr += sizeof(*cmd);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_CHANNEL);
	tlv->len = __cpu_to_le16(sizeof(*ch));
	ch = (void *)tlv->value;
	ath10k_wmi_put_wmi_channel(ch, &arg->channel);

	ptr += sizeof(*tlv);
	ptr += sizeof(*ch);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_STRUCT);
	tlv->len = 0;

	/* Note: This is a nested TLV containing:
	 * [wmi_tlv][wmi_p2p_noa_descriptor][wmi_tlv]..
	 */

	ptr += sizeof(*tlv);
	ptr += 0;

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv vdev start\n");
	return skb;
}