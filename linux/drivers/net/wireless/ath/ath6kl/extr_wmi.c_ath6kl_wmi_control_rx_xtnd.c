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
typedef  int u32 ;
typedef  int u16 ;
struct wmix_cmd_hdr {int /*<<< orphan*/  cmd_id; } ;
struct wmi {int /*<<< orphan*/  parent_dev; } ;
struct sk_buff {int len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WMI ; 
 int EINVAL ; 
#define  WMIX_DBGLOG_EVENTID 129 
#define  WMIX_HB_CHALLENGE_RESP_EVENTID 128 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ath6kl_debug_fwlog_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ath6kl_err (char*) ; 
 int /*<<< orphan*/  ath6kl_warn (char*,int) ; 
 int /*<<< orphan*/  ath6kl_wmi_hb_challenge_resp_event (struct wmi*,int /*<<< orphan*/ *,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int ath6kl_wmi_control_rx_xtnd(struct wmi *wmi, struct sk_buff *skb)
{
	struct wmix_cmd_hdr *cmd;
	u32 len;
	u16 id;
	u8 *datap;
	int ret = 0;

	if (skb->len < sizeof(struct wmix_cmd_hdr)) {
		ath6kl_err("bad packet 1\n");
		return -EINVAL;
	}

	cmd = (struct wmix_cmd_hdr *) skb->data;
	id = le32_to_cpu(cmd->cmd_id);

	skb_pull(skb, sizeof(struct wmix_cmd_hdr));

	datap = skb->data;
	len = skb->len;

	switch (id) {
	case WMIX_HB_CHALLENGE_RESP_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "wmi event hb challenge resp\n");
		ath6kl_wmi_hb_challenge_resp_event(wmi, datap, len);
		break;
	case WMIX_DBGLOG_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "wmi event dbglog len %d\n", len);
		ath6kl_debug_fwlog_event(wmi->parent_dev, datap, len);
		break;
	default:
		ath6kl_warn("unknown cmd id 0x%x\n", id);
		ret = -EINVAL;
		break;
	}

	return ret;
}