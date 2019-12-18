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
typedef  int /*<<< orphan*/  u16 ;
struct wmi_set_rts_cmd {int /*<<< orphan*/  threshold; } ;
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  WMI_SET_RTS_CMDID ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 

int ath6kl_wmi_set_rts_cmd(struct wmi *wmi, u16 threshold)
{
	struct sk_buff *skb;
	struct wmi_set_rts_cmd *cmd;
	int ret;

	skb = ath6kl_wmi_get_new_buf(sizeof(struct wmi_set_rts_cmd));
	if (!skb)
		return -ENOMEM;

	cmd = (struct wmi_set_rts_cmd *) skb->data;
	cmd->threshold = cpu_to_le16(threshold);

	ret = ath6kl_wmi_cmd_send(wmi, 0, skb, WMI_SET_RTS_CMDID,
				  NO_SYNC_WMIFLAG);
	return ret;
}