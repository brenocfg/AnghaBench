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
typedef  int u16 ;
struct wmi_p2p_probe_response_cmd {int /*<<< orphan*/  data; int /*<<< orphan*/  len; int /*<<< orphan*/  destination_addr; int /*<<< orphan*/  freq; } ;
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WMI ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  WMI_SEND_PROBE_RESPONSE_CMDID ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (size_t) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

int ath6kl_wmi_send_probe_response_cmd(struct wmi *wmi, u8 if_idx, u32 freq,
				       const u8 *dst, const u8 *data,
				       u16 data_len)
{
	struct sk_buff *skb;
	struct wmi_p2p_probe_response_cmd *p;
	size_t cmd_len = sizeof(*p) + data_len;

	if (data_len == 0)
		cmd_len++; /* work around target minimum length requirement */

	skb = ath6kl_wmi_get_new_buf(cmd_len);
	if (!skb)
		return -ENOMEM;

	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "send_probe_response_cmd: freq=%u dst=%pM len=%u\n",
		   freq, dst, data_len);
	p = (struct wmi_p2p_probe_response_cmd *) skb->data;
	p->freq = cpu_to_le32(freq);
	memcpy(p->destination_addr, dst, ETH_ALEN);
	p->len = cpu_to_le16(data_len);
	memcpy(p->data, data, data_len);
	return ath6kl_wmi_cmd_send(wmi, if_idx, skb,
				   WMI_SEND_PROBE_RESPONSE_CMDID,
				   NO_SYNC_WMIFLAG);
}