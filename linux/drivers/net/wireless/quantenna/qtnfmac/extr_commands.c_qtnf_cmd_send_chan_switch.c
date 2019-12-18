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
struct sk_buff {scalar_t__ data; } ;
struct qtnf_wmac {int /*<<< orphan*/  bus; int /*<<< orphan*/  macid; } ;
struct qtnf_vif {int /*<<< orphan*/  vifid; struct qtnf_wmac* mac; } ;
struct qlink_cmd_chan_switch {int /*<<< orphan*/  beacon_count; int /*<<< orphan*/  block_tx; int /*<<< orphan*/  radar_required; int /*<<< orphan*/  channel; } ;
struct TYPE_4__ {TYPE_1__* chan; } ;
struct cfg80211_csa_settings {int /*<<< orphan*/  count; int /*<<< orphan*/  block_tx; int /*<<< orphan*/  radar_required; TYPE_2__ chandef; } ;
struct TYPE_3__ {int /*<<< orphan*/  hw_value; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  QLINK_CMD_CHAN_SWITCH ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_bus_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_bus_unlock (int /*<<< orphan*/ ) ; 
 struct sk_buff* qtnf_cmd_alloc_new_cmdskb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qtnf_cmd_send (int /*<<< orphan*/ ,struct sk_buff*) ; 

int qtnf_cmd_send_chan_switch(struct qtnf_vif *vif,
			      struct cfg80211_csa_settings *params)
{
	struct qtnf_wmac *mac = vif->mac;
	struct qlink_cmd_chan_switch *cmd;
	struct sk_buff *cmd_skb;
	int ret;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(mac->macid, vif->vifid,
					    QLINK_CMD_CHAN_SWITCH,
					    sizeof(*cmd));
	if (!cmd_skb)
		return -ENOMEM;

	qtnf_bus_lock(mac->bus);

	cmd = (struct qlink_cmd_chan_switch *)cmd_skb->data;
	cmd->channel = cpu_to_le16(params->chandef.chan->hw_value);
	cmd->radar_required = params->radar_required;
	cmd->block_tx = params->block_tx;
	cmd->beacon_count = params->count;

	ret = qtnf_cmd_send(mac->bus, cmd_skb);
	if (ret)
		goto out;

out:
	qtnf_bus_unlock(mac->bus);

	return ret;
}