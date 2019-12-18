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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wmi_ap_apsd_buffered_traffic_cmd {int /*<<< orphan*/  flags; void* bitmap; void* aid; } ;
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  WMI_AP_APSD_BUFFERED_TRAFFIC_CMDID ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

int ath6kl_wmi_set_apsd_bfrd_traf(struct wmi *wmi, u8 if_idx,
					     u16 aid, u16 bitmap, u32 flags)
{
	struct wmi_ap_apsd_buffered_traffic_cmd *cmd;
	struct sk_buff *skb;

	skb = ath6kl_wmi_get_new_buf(sizeof(*cmd));
	if (!skb)
		return -ENOMEM;

	cmd = (struct wmi_ap_apsd_buffered_traffic_cmd *)skb->data;
	cmd->aid = cpu_to_le16(aid);
	cmd->bitmap = cpu_to_le16(bitmap);
	cmd->flags = cpu_to_le32(flags);

	return ath6kl_wmi_cmd_send(wmi, if_idx, skb,
				   WMI_AP_APSD_BUFFERED_TRAFFIC_CMDID,
				   NO_SYNC_WMIFLAG);
}