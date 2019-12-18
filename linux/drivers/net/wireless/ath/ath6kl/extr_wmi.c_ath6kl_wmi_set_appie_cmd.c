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
typedef  scalar_t__ u8 ;
struct wmi_set_appie_cmd {int /*<<< orphan*/  ie_info; scalar_t__ ie_len; scalar_t__ mgmt_frm_type; } ;
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WMI ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  WMI_SET_APPIE_CMDID ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int ath6kl_wmi_cmd_send (struct wmi*,scalar_t__,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__ const*,scalar_t__) ; 

int ath6kl_wmi_set_appie_cmd(struct wmi *wmi, u8 if_idx, u8 mgmt_frm_type,
			     const u8 *ie, u8 ie_len)
{
	struct sk_buff *skb;
	struct wmi_set_appie_cmd *p;

	skb = ath6kl_wmi_get_new_buf(sizeof(*p) + ie_len);
	if (!skb)
		return -ENOMEM;

	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "set_appie_cmd: mgmt_frm_type=%u ie_len=%u\n",
		   mgmt_frm_type, ie_len);
	p = (struct wmi_set_appie_cmd *) skb->data;
	p->mgmt_frm_type = mgmt_frm_type;
	p->ie_len = ie_len;

	if (ie != NULL && ie_len > 0)
		memcpy(p->ie_info, ie, ie_len);

	return ath6kl_wmi_cmd_send(wmi, if_idx, skb, WMI_SET_APPIE_CMDID,
				   NO_SYNC_WMIFLAG);
}