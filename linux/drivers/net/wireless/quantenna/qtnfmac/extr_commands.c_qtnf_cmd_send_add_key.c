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
struct sk_buff {scalar_t__ data; } ;
struct qtnf_vif {TYPE_1__* mac; int /*<<< orphan*/  vifid; } ;
struct qlink_cmd_add_key {int pairwise; int /*<<< orphan*/  key_index; int /*<<< orphan*/  cipher; int /*<<< orphan*/  addr; } ;
struct key_params {scalar_t__ key_len; scalar_t__ seq_len; scalar_t__ seq; scalar_t__ key; int /*<<< orphan*/  cipher; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; int /*<<< orphan*/  macid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  QLINK_CMD_ADD_KEY ; 
 int /*<<< orphan*/  QTN_TLV_ID_KEY ; 
 int /*<<< orphan*/  QTN_TLV_ID_SEQ ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  qtnf_bus_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_bus_unlock (int /*<<< orphan*/ ) ; 
 struct sk_buff* qtnf_cmd_alloc_new_cmdskb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qtnf_cmd_send (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  qtnf_cmd_skb_put_tlv_arr (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

int qtnf_cmd_send_add_key(struct qtnf_vif *vif, u8 key_index, bool pairwise,
			  const u8 *mac_addr, struct key_params *params)
{
	struct sk_buff *cmd_skb;
	struct qlink_cmd_add_key *cmd;
	int ret = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QLINK_CMD_ADD_KEY,
					    sizeof(*cmd));
	if (!cmd_skb)
		return -ENOMEM;

	qtnf_bus_lock(vif->mac->bus);

	cmd = (struct qlink_cmd_add_key *)cmd_skb->data;

	if (mac_addr)
		ether_addr_copy(cmd->addr, mac_addr);
	else
		eth_broadcast_addr(cmd->addr);

	cmd->cipher = cpu_to_le32(params->cipher);
	cmd->key_index = key_index;
	cmd->pairwise = pairwise;

	if (params->key && params->key_len > 0)
		qtnf_cmd_skb_put_tlv_arr(cmd_skb, QTN_TLV_ID_KEY,
					 params->key,
					 params->key_len);

	if (params->seq && params->seq_len > 0)
		qtnf_cmd_skb_put_tlv_arr(cmd_skb, QTN_TLV_ID_SEQ,
					 params->seq,
					 params->seq_len);

	ret = qtnf_cmd_send(vif->mac->bus, cmd_skb);
	if (ret)
		goto out;

out:
	qtnf_bus_unlock(vif->mac->bus);

	return ret;
}