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
struct wmi_tlv {scalar_t__ value; void* len; void* tag; } ;
struct wmi_stop_scan_cmd {void* scan_req_id; void* scan_id; void* vdev_id; void* req_type; } ;
struct TYPE_2__ {int scan_id; int vdev_id; } ;
struct wmi_stop_scan_arg {int req_id; scalar_t__ req_type; TYPE_1__ u; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int WMI_HOST_SCAN_REQUESTOR_ID_PREFIX ; 
 int WMI_HOST_SCAN_REQ_ID_PREFIX ; 
 scalar_t__ WMI_SCAN_STOP_ONE ; 
 int WMI_TLV_TAG_STRUCT_STOP_SCAN_CMD ; 
 void* __cpu_to_le16 (int) ; 
 void* __cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,int) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_tlv_op_gen_stop_scan(struct ath10k *ar,
				const struct wmi_stop_scan_arg *arg)
{
	struct wmi_stop_scan_cmd *cmd;
	struct wmi_tlv *tlv;
	struct sk_buff *skb;
	u32 scan_id;
	u32 req_id;

	if (arg->req_id > 0xFFF)
		return ERR_PTR(-EINVAL);
	if (arg->req_type == WMI_SCAN_STOP_ONE && arg->u.scan_id > 0xFFF)
		return ERR_PTR(-EINVAL);

	skb = ath10k_wmi_alloc_skb(ar, sizeof(*tlv) + sizeof(*cmd));
	if (!skb)
		return ERR_PTR(-ENOMEM);

	scan_id = arg->u.scan_id;
	scan_id |= WMI_HOST_SCAN_REQ_ID_PREFIX;

	req_id = arg->req_id;
	req_id |= WMI_HOST_SCAN_REQUESTOR_ID_PREFIX;

	tlv = (void *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_STOP_SCAN_CMD);
	tlv->len = __cpu_to_le16(sizeof(*cmd));
	cmd = (void *)tlv->value;
	cmd->req_type = __cpu_to_le32(arg->req_type);
	cmd->vdev_id = __cpu_to_le32(arg->u.vdev_id);
	cmd->scan_id = __cpu_to_le32(scan_id);
	cmd->scan_req_id = __cpu_to_le32(req_id);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv stop scan\n");
	return skb;
}