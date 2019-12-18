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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct wmi_delba_send_cmd {void* reasoncode; void* initiator; void* tid; TYPE_1__ peer_macaddr; void* vdev_id; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 void* __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,int) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_op_gen_delba_send(struct ath10k *ar, u32 vdev_id, const u8 *mac,
			     u32 tid, u32 initiator, u32 reason)
{
	struct wmi_delba_send_cmd *cmd;
	struct sk_buff *skb;

	if (!mac)
		return ERR_PTR(-EINVAL);

	skb = ath10k_wmi_alloc_skb(ar, sizeof(*cmd));
	if (!skb)
		return ERR_PTR(-ENOMEM);

	cmd = (struct wmi_delba_send_cmd *)skb->data;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	ether_addr_copy(cmd->peer_macaddr.addr, mac);
	cmd->tid = __cpu_to_le32(tid);
	cmd->initiator = __cpu_to_le32(initiator);
	cmd->reasoncode = __cpu_to_le32(reason);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi delba send vdev_id 0x%X mac_addr %pM tid %u initiator %u reason %u\n",
		   vdev_id, mac, tid, initiator, reason);
	return skb;
}