#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  roam_rssi_floor; void* lrssi_roam_threshold; void* lrssi_scan_threshold; int /*<<< orphan*/  lrssi_scan_period; } ;
struct TYPE_4__ {TYPE_1__ params; } ;
struct roam_ctrl_cmd {int /*<<< orphan*/  roam_ctrl; TYPE_2__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_LRSSI_ROAM_FLOOR ; 
 int /*<<< orphan*/  DEF_LRSSI_SCAN_PERIOD ; 
 scalar_t__ DEF_SCAN_FOR_ROAM_INTVL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  WMI_SET_LRSSI_SCAN_PARAMS ; 
 int /*<<< orphan*/  WMI_SET_ROAM_CTRL_CMDID ; 
 void* a_cpu_to_sle16 (scalar_t__) ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 

int ath6kl_wmi_set_roam_lrssi_cmd(struct wmi *wmi, u8 lrssi)
{
	struct sk_buff *skb;
	struct roam_ctrl_cmd *cmd;

	skb = ath6kl_wmi_get_new_buf(sizeof(*cmd));
	if (!skb)
		return -ENOMEM;

	cmd = (struct roam_ctrl_cmd *) skb->data;

	cmd->info.params.lrssi_scan_period = cpu_to_le16(DEF_LRSSI_SCAN_PERIOD);
	cmd->info.params.lrssi_scan_threshold = a_cpu_to_sle16(lrssi +
						       DEF_SCAN_FOR_ROAM_INTVL);
	cmd->info.params.lrssi_roam_threshold = a_cpu_to_sle16(lrssi);
	cmd->info.params.roam_rssi_floor = DEF_LRSSI_ROAM_FLOOR;
	cmd->roam_ctrl = WMI_SET_LRSSI_SCAN_PARAMS;

	return ath6kl_wmi_cmd_send(wmi, 0, skb, WMI_SET_ROAM_CTRL_CMDID,
			    NO_SYNC_WMIFLAG);
}