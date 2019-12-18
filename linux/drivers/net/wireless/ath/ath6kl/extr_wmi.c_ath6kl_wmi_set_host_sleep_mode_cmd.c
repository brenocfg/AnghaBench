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
struct wmi_set_host_sleep_mode_cmd {void* awake; void* asleep; } ;
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
typedef  enum ath6kl_host_mode { ____Placeholder_ath6kl_host_mode } ath6kl_host_mode ;

/* Variables and functions */
 int ATH6KL_HOST_MODE_ASLEEP ; 
 int ATH6KL_HOST_MODE_AWAKE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  WMI_SET_HOST_SLEEP_MODE_CMDID ; 
 int /*<<< orphan*/  ath6kl_err (char*,int) ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 
 int /*<<< orphan*/  ath6kl_wmi_relinquish_implicit_pstream_credits (struct wmi*) ; 
 void* cpu_to_le32 (int) ; 

int ath6kl_wmi_set_host_sleep_mode_cmd(struct wmi *wmi, u8 if_idx,
				       enum ath6kl_host_mode host_mode)
{
	struct sk_buff *skb;
	struct wmi_set_host_sleep_mode_cmd *cmd;
	int ret;

	if ((host_mode != ATH6KL_HOST_MODE_ASLEEP) &&
	    (host_mode != ATH6KL_HOST_MODE_AWAKE)) {
		ath6kl_err("invalid host sleep mode: %d\n", host_mode);
		return -EINVAL;
	}

	skb = ath6kl_wmi_get_new_buf(sizeof(*cmd));
	if (!skb)
		return -ENOMEM;

	cmd = (struct wmi_set_host_sleep_mode_cmd *) skb->data;

	if (host_mode == ATH6KL_HOST_MODE_ASLEEP) {
		ath6kl_wmi_relinquish_implicit_pstream_credits(wmi);
		cmd->asleep = cpu_to_le32(1);
	} else {
		cmd->awake = cpu_to_le32(1);
	}

	ret = ath6kl_wmi_cmd_send(wmi, if_idx, skb,
				  WMI_SET_HOST_SLEEP_MODE_CMDID,
				  NO_SYNC_WMIFLAG);
	return ret;
}