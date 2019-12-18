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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct qtnf_vif {TYPE_1__* mac; int /*<<< orphan*/  vifid; } ;
struct qlink_cmd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; int /*<<< orphan*/  macid; } ;

/* Variables and functions */
 int E2BIG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  QLINK_CMD_MGMT_SET_APPIE ; 
 size_t QTNF_MAX_CMD_BUF_SIZE ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  qtnf_bus_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_bus_unlock (int /*<<< orphan*/ ) ; 
 struct sk_buff* qtnf_cmd_alloc_new_cmdskb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qtnf_cmd_send (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  qtnf_cmd_tlv_ie_set_add (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

int qtnf_cmd_send_mgmt_set_appie(struct qtnf_vif *vif, u8 frame_type,
				 const u8 *buf, size_t len)
{
	struct sk_buff *cmd_skb;
	int ret;

	if (len > QTNF_MAX_CMD_BUF_SIZE) {
		pr_warn("VIF%u.%u: %u frame is too big: %zu\n", vif->mac->macid,
			vif->vifid, frame_type, len);
		return -E2BIG;
	}

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QLINK_CMD_MGMT_SET_APPIE,
					    sizeof(struct qlink_cmd));
	if (!cmd_skb)
		return -ENOMEM;

	qtnf_cmd_tlv_ie_set_add(cmd_skb, frame_type, buf, len);

	qtnf_bus_lock(vif->mac->bus);
	ret = qtnf_cmd_send(vif->mac->bus, cmd_skb);
	if (ret)
		goto out;

out:
	qtnf_bus_unlock(vif->mac->bus);

	return ret;
}