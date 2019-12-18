#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {scalar_t__ data; } ;
struct qtnf_vif {int /*<<< orphan*/  vifid; TYPE_1__* mac; } ;
struct qtnf_bus {int dummy; } ;
struct qlink_cmd_start_cac {int /*<<< orphan*/  chan; int /*<<< orphan*/  cac_time_ms; } ;
struct cfg80211_chan_def {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  macid; struct qtnf_bus* bus; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  QLINK_CMD_START_CAC ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlink_chandef_cfg2q (struct cfg80211_chan_def const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qtnf_bus_lock (struct qtnf_bus*) ; 
 int /*<<< orphan*/  qtnf_bus_unlock (struct qtnf_bus*) ; 
 struct sk_buff* qtnf_cmd_alloc_new_cmdskb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qtnf_cmd_send (struct qtnf_bus*,struct sk_buff*) ; 

int qtnf_cmd_start_cac(const struct qtnf_vif *vif,
		       const struct cfg80211_chan_def *chdef,
		       u32 cac_time_ms)
{
	struct qtnf_bus *bus = vif->mac->bus;
	struct sk_buff *cmd_skb;
	struct qlink_cmd_start_cac *cmd;
	int ret;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QLINK_CMD_START_CAC,
					    sizeof(*cmd));
	if (!cmd_skb)
		return -ENOMEM;

	cmd = (struct qlink_cmd_start_cac *)cmd_skb->data;
	cmd->cac_time_ms = cpu_to_le32(cac_time_ms);
	qlink_chandef_cfg2q(chdef, &cmd->chan);

	qtnf_bus_lock(bus);
	ret = qtnf_cmd_send(bus, cmd_skb);
	if (ret)
		goto out;

out:
	qtnf_bus_unlock(bus);

	return ret;
}