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
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct wmi_vdev_install_key_cmd {TYPE_1__ peer_macaddr; void* key_rxmic_len; void* key_txmic_len; void* key_len; void* key_cipher; void* key_flags; void* key_idx; void* vdev_id; } ;
struct wmi_vdev_install_key_arg {scalar_t__ key_cipher; scalar_t__ key_len; scalar_t__ vdev_id; scalar_t__ key_idx; scalar_t__ key_flags; scalar_t__ key_txmic_len; scalar_t__ key_rxmic_len; int /*<<< orphan*/  key_data; int /*<<< orphan*/  macaddr; } ;
struct wmi_tlv {scalar_t__ value; void* len; void* tag; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {scalar_t__* wmi_key_cipher; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 size_t WMI_CIPHER_NONE ; 
 int WMI_TLV_TAG_ARRAY_BYTE ; 
 int WMI_TLV_TAG_STRUCT_VDEV_INSTALL_KEY_CMD ; 
 void* __cpu_to_le16 (int) ; 
 void* __cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,size_t) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int roundup (scalar_t__,int) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_tlv_op_gen_vdev_install_key(struct ath10k *ar,
				       const struct wmi_vdev_install_key_arg *arg)
{
	struct wmi_vdev_install_key_cmd *cmd;
	struct wmi_tlv *tlv;
	struct sk_buff *skb;
	size_t len;
	void *ptr;

	if (arg->key_cipher == ar->wmi_key_cipher[WMI_CIPHER_NONE] &&
	    arg->key_data)
		return ERR_PTR(-EINVAL);
	if (arg->key_cipher != ar->wmi_key_cipher[WMI_CIPHER_NONE] &&
	    !arg->key_data)
		return ERR_PTR(-EINVAL);

	len = sizeof(*tlv) + sizeof(*cmd) +
	      sizeof(*tlv) + roundup(arg->key_len, sizeof(__le32));
	skb = ath10k_wmi_alloc_skb(ar, len);
	if (!skb)
		return ERR_PTR(-ENOMEM);

	ptr = (void *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_VDEV_INSTALL_KEY_CMD);
	tlv->len = __cpu_to_le16(sizeof(*cmd));
	cmd = (void *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(arg->vdev_id);
	cmd->key_idx = __cpu_to_le32(arg->key_idx);
	cmd->key_flags = __cpu_to_le32(arg->key_flags);
	cmd->key_cipher = __cpu_to_le32(arg->key_cipher);
	cmd->key_len = __cpu_to_le32(arg->key_len);
	cmd->key_txmic_len = __cpu_to_le32(arg->key_txmic_len);
	cmd->key_rxmic_len = __cpu_to_le32(arg->key_rxmic_len);

	if (arg->macaddr)
		ether_addr_copy(cmd->peer_macaddr.addr, arg->macaddr);

	ptr += sizeof(*tlv);
	ptr += sizeof(*cmd);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_BYTE);
	tlv->len = __cpu_to_le16(roundup(arg->key_len, sizeof(__le32)));
	if (arg->key_data)
		memcpy(tlv->value, arg->key_data, arg->key_len);

	ptr += sizeof(*tlv);
	ptr += roundup(arg->key_len, sizeof(__le32));

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv vdev install key\n");
	return skb;
}