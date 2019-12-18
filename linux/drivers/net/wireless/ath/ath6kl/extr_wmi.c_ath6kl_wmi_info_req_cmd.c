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
struct wmi_get_p2p_info {int /*<<< orphan*/  info_req_flags; } ;
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WMI ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  WMI_GET_P2P_INFO_CMDID ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

int ath6kl_wmi_info_req_cmd(struct wmi *wmi, u8 if_idx, u32 info_req_flags)
{
	struct sk_buff *skb;
	struct wmi_get_p2p_info *p;

	skb = ath6kl_wmi_get_new_buf(sizeof(*p));
	if (!skb)
		return -ENOMEM;

	ath6kl_dbg(ATH6KL_DBG_WMI, "info_req_cmd: flags=%x\n",
		   info_req_flags);
	p = (struct wmi_get_p2p_info *) skb->data;
	p->info_req_flags = cpu_to_le32(info_req_flags);
	return ath6kl_wmi_cmd_send(wmi, if_idx, skb, WMI_GET_P2P_INFO_CMDID,
				   NO_SYNC_WMIFLAG);
}