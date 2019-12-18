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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wmi_scan_params_cmd {void* maxact_scan_per_ssid; int /*<<< orphan*/  max_dfsch_act_time; void* scan_ctrl_flags; void* short_scan_ratio; void* pas_chdwell_time; void* maxact_chdwell_time; void* minact_chdwell_time; void* bg_period; void* fg_end_period; void* fg_start_period; } ;
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  WMI_SET_SCAN_PARAMS_CMDID ; 
 int ath6kl_wmi_cmd_send (struct wmi*,void*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

int ath6kl_wmi_scanparams_cmd(struct wmi *wmi, u8 if_idx,
			      u16 fg_start_sec,
			      u16 fg_end_sec, u16 bg_sec,
			      u16 minact_chdw_msec, u16 maxact_chdw_msec,
			      u16 pas_chdw_msec, u8 short_scan_ratio,
			      u8 scan_ctrl_flag, u32 max_dfsch_act_time,
			      u16 maxact_scan_per_ssid)
{
	struct sk_buff *skb;
	struct wmi_scan_params_cmd *sc;
	int ret;

	skb = ath6kl_wmi_get_new_buf(sizeof(*sc));
	if (!skb)
		return -ENOMEM;

	sc = (struct wmi_scan_params_cmd *) skb->data;
	sc->fg_start_period = cpu_to_le16(fg_start_sec);
	sc->fg_end_period = cpu_to_le16(fg_end_sec);
	sc->bg_period = cpu_to_le16(bg_sec);
	sc->minact_chdwell_time = cpu_to_le16(minact_chdw_msec);
	sc->maxact_chdwell_time = cpu_to_le16(maxact_chdw_msec);
	sc->pas_chdwell_time = cpu_to_le16(pas_chdw_msec);
	sc->short_scan_ratio = short_scan_ratio;
	sc->scan_ctrl_flags = scan_ctrl_flag;
	sc->max_dfsch_act_time = cpu_to_le32(max_dfsch_act_time);
	sc->maxact_scan_per_ssid = cpu_to_le16(maxact_scan_per_ssid);

	ret = ath6kl_wmi_cmd_send(wmi, if_idx, skb, WMI_SET_SCAN_PARAMS_CMDID,
				  NO_SYNC_WMIFLAG);
	return ret;
}