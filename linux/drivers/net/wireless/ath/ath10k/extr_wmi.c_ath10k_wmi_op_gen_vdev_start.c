#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  ssid; void* ssid_len; } ;
struct wmi_vdev_start_request_cmd {TYPE_2__ chan; TYPE_1__ ssid; void* bcn_tx_power; void* bcn_tx_rate; void* flags; void* dtim_period; void* beacon_interval; void* disable_hw_ack; void* vdev_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  max_power; int /*<<< orphan*/  mode; int /*<<< orphan*/  freq; } ;
struct wmi_vdev_start_request_arg {int ssid_len; int vdev_id; int disable_hw_ack; int bcn_intval; int dtim_period; int bcn_tx_rate; int bcn_tx_power; TYPE_3__ channel; int /*<<< orphan*/  ssid; scalar_t__ pmf_enabled; scalar_t__ hidden_ssid; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int WMI_VDEV_START_HIDDEN_SSID ; 
 int WMI_VDEV_START_PMF_ENABLED ; 
 void* __cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,char const*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,int) ; 
 int /*<<< orphan*/  ath10k_wmi_put_wmi_channel (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_op_gen_vdev_start(struct ath10k *ar,
			     const struct wmi_vdev_start_request_arg *arg,
			     bool restart)
{
	struct wmi_vdev_start_request_cmd *cmd;
	struct sk_buff *skb;
	const char *cmdname;
	u32 flags = 0;

	if (WARN_ON(arg->hidden_ssid && !arg->ssid))
		return ERR_PTR(-EINVAL);
	if (WARN_ON(arg->ssid_len > sizeof(cmd->ssid.ssid)))
		return ERR_PTR(-EINVAL);

	if (restart)
		cmdname = "restart";
	else
		cmdname = "start";

	skb = ath10k_wmi_alloc_skb(ar, sizeof(*cmd));
	if (!skb)
		return ERR_PTR(-ENOMEM);

	if (arg->hidden_ssid)
		flags |= WMI_VDEV_START_HIDDEN_SSID;
	if (arg->pmf_enabled)
		flags |= WMI_VDEV_START_PMF_ENABLED;

	cmd = (struct wmi_vdev_start_request_cmd *)skb->data;
	cmd->vdev_id         = __cpu_to_le32(arg->vdev_id);
	cmd->disable_hw_ack  = __cpu_to_le32(arg->disable_hw_ack);
	cmd->beacon_interval = __cpu_to_le32(arg->bcn_intval);
	cmd->dtim_period     = __cpu_to_le32(arg->dtim_period);
	cmd->flags           = __cpu_to_le32(flags);
	cmd->bcn_tx_rate     = __cpu_to_le32(arg->bcn_tx_rate);
	cmd->bcn_tx_power    = __cpu_to_le32(arg->bcn_tx_power);

	if (arg->ssid) {
		cmd->ssid.ssid_len = __cpu_to_le32(arg->ssid_len);
		memcpy(cmd->ssid.ssid, arg->ssid, arg->ssid_len);
	}

	ath10k_wmi_put_wmi_channel(&cmd->chan, &arg->channel);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi vdev %s id 0x%x flags: 0x%0X, freq %d, mode %d, ch_flags: 0x%0X, max_power: %d\n",
		   cmdname, arg->vdev_id,
		   flags, arg->channel.freq, arg->channel.mode,
		   cmd->chan.flags, arg->channel.max_power);

	return skb;
}