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
struct sk_buff {scalar_t__ data; } ;
struct qtnf_vif {TYPE_1__* mac; int /*<<< orphan*/  vifid; } ;
struct qlink_cmd_external_auth {int /*<<< orphan*/  status; int /*<<< orphan*/  bssid; } ;
struct cfg80211_external_auth_params {int /*<<< orphan*/  status; int /*<<< orphan*/  bssid; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; int /*<<< orphan*/  macid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  QLINK_CMD_EXTERNAL_AUTH ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_bus_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_bus_unlock (int /*<<< orphan*/ ) ; 
 struct sk_buff* qtnf_cmd_alloc_new_cmdskb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qtnf_cmd_send (int /*<<< orphan*/ ,struct sk_buff*) ; 

int qtnf_cmd_send_external_auth(struct qtnf_vif *vif,
				struct cfg80211_external_auth_params *auth)
{
	struct sk_buff *cmd_skb;
	struct qlink_cmd_external_auth *cmd;
	int ret;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QLINK_CMD_EXTERNAL_AUTH,
					    sizeof(*cmd));
	if (!cmd_skb)
		return -ENOMEM;

	cmd = (struct qlink_cmd_external_auth *)cmd_skb->data;

	ether_addr_copy(cmd->bssid, auth->bssid);
	cmd->status = cpu_to_le16(auth->status);

	qtnf_bus_lock(vif->mac->bus);
	ret = qtnf_cmd_send(vif->mac->bus, cmd_skb);
	if (ret)
		goto out;

out:
	qtnf_bus_unlock(vif->mac->bus);

	return ret;
}