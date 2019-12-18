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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct wmi_tlv_dbglog_cmd {void* value; void* param; } ;
struct wmi_tlv {void* len; void* tag; scalar_t__ value; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {int dummy; } ;
typedef  int /*<<< orphan*/  bmap_len ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ WMI_TLV_DBGLOG_ALL_MODULES ; 
 int /*<<< orphan*/  WMI_TLV_DBGLOG_LOG_LEVEL_VALUE (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WMI_TLV_DBGLOG_LOG_LEVEL_VERBOSE ; 
 int /*<<< orphan*/  WMI_TLV_DBGLOG_LOG_LEVEL_WARN ; 
 int /*<<< orphan*/  WMI_TLV_DBGLOG_PARAM_LOG_LEVEL ; 
 size_t WMI_TLV_TAG_ARRAY_UINT32 ; 
 size_t WMI_TLV_TAG_STRUCT_DEBUG_LOG_CONFIG_CMD ; 
 void* __cpu_to_le16 (size_t) ; 
 void* __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,size_t) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_tlv_op_gen_dbglog_cfg(struct ath10k *ar, u64 module_enable,
				 u32 log_level)
{
	struct wmi_tlv_dbglog_cmd *cmd;
	struct wmi_tlv *tlv;
	struct sk_buff *skb;
	size_t len, bmap_len;
	u32 value;
	void *ptr;

	if (module_enable) {
		value = WMI_TLV_DBGLOG_LOG_LEVEL_VALUE(
				module_enable,
				WMI_TLV_DBGLOG_LOG_LEVEL_VERBOSE);
	} else {
		value = WMI_TLV_DBGLOG_LOG_LEVEL_VALUE(
				WMI_TLV_DBGLOG_ALL_MODULES,
				WMI_TLV_DBGLOG_LOG_LEVEL_WARN);
	}

	bmap_len = 0;
	len = sizeof(*tlv) + sizeof(*cmd) + sizeof(*tlv) + bmap_len;
	skb = ath10k_wmi_alloc_skb(ar, len);
	if (!skb)
		return ERR_PTR(-ENOMEM);

	ptr = (void *)skb->data;

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_DEBUG_LOG_CONFIG_CMD);
	tlv->len = __cpu_to_le16(sizeof(*cmd));
	cmd = (void *)tlv->value;
	cmd->param = __cpu_to_le32(WMI_TLV_DBGLOG_PARAM_LOG_LEVEL);
	cmd->value = __cpu_to_le32(value);

	ptr += sizeof(*tlv);
	ptr += sizeof(*cmd);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_UINT32);
	tlv->len = __cpu_to_le16(bmap_len);

	/* nothing to do here */

	ptr += sizeof(*tlv);
	ptr += sizeof(bmap_len);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv dbglog value 0x%08x\n", value);
	return skb;
}