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
struct wmi_start_scan_cmd {int scan_type; int num_ch; int /*<<< orphan*/ * ch_list; void* force_scan_intvl; void* home_dwell_time; void* is_legacy; void* force_fg_scan; } ;
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
typedef  int s8 ;
typedef  enum wmi_scan_type { ____Placeholder_wmi_scan_type } wmi_scan_type ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int WMI_LONG_SCAN ; 
 int WMI_MAX_CHANNELS ; 
 int WMI_SHORT_SCAN ; 
 int /*<<< orphan*/  WMI_START_SCAN_CMDID ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_wmi_startscan_cmd(struct wmi *wmi, u8 if_idx,
				    enum wmi_scan_type scan_type,
				    u32 force_fgscan, u32 is_legacy,
				    u32 home_dwell_time,
				    u32 force_scan_interval,
				    s8 num_chan, u16 *ch_list)
{
	struct sk_buff *skb;
	struct wmi_start_scan_cmd *sc;
	s8 size;
	int i, ret;

	size = sizeof(struct wmi_start_scan_cmd);

	if ((scan_type != WMI_LONG_SCAN) && (scan_type != WMI_SHORT_SCAN))
		return -EINVAL;

	if (num_chan > WMI_MAX_CHANNELS)
		return -EINVAL;

	if (num_chan)
		size += sizeof(u16) * (num_chan - 1);

	skb = ath6kl_wmi_get_new_buf(size);
	if (!skb)
		return -ENOMEM;

	sc = (struct wmi_start_scan_cmd *) skb->data;
	sc->scan_type = scan_type;
	sc->force_fg_scan = cpu_to_le32(force_fgscan);
	sc->is_legacy = cpu_to_le32(is_legacy);
	sc->home_dwell_time = cpu_to_le32(home_dwell_time);
	sc->force_scan_intvl = cpu_to_le32(force_scan_interval);
	sc->num_ch = num_chan;

	for (i = 0; i < num_chan; i++)
		sc->ch_list[i] = cpu_to_le16(ch_list[i]);

	ret = ath6kl_wmi_cmd_send(wmi, if_idx, skb, WMI_START_SCAN_CMDID,
				  NO_SYNC_WMIFLAG);

	return ret;
}