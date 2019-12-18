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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct hinic_sq_task {int dummy; } ;
typedef  enum hinic_offload_type { ____Placeholder_hinic_offload_type } hinic_offload_type ;

/* Variables and functions */
 int EPROTONOSUPPORT ; 
 scalar_t__ HINIC_MSS_MIN ; 
 int /*<<< orphan*/  HINIC_SQ_CTRL_CLEAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HINIC_SQ_CTRL_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HINIC_SQ_CTRL_SET (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_PAYLOAD_OFFSET ; 
 int /*<<< orphan*/  QUEUE_INFO_MSS ; 
 int /*<<< orphan*/  QUEUE_INFO_PLDOFF ; 
 int TX_OFFLOAD_CSUM ; 
 int TX_OFFLOAD_TSO ; 
 int TX_OFFLOAD_VLAN ; 
 int VLAN_PRIO_SHIFT ; 
 int /*<<< orphan*/  hinic_task_set_l2hdr (struct hinic_sq_task*,int /*<<< orphan*/ ) ; 
 int offload_csum (struct hinic_sq_task*,int /*<<< orphan*/ *,struct sk_buff*) ; 
 int offload_tso (struct hinic_sq_task*,int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  offload_vlan (struct hinic_sq_task*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 
 int skb_vlan_tag_get (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_vlan_tag_present (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hinic_tx_offload(struct sk_buff *skb, struct hinic_sq_task *task,
			    u32 *queue_info)
{
	enum hinic_offload_type offload = 0;
	u16 vlan_tag;
	int enabled;

	enabled = offload_tso(task, queue_info, skb);
	if (enabled > 0) {
		offload |= TX_OFFLOAD_TSO;
	} else if (enabled == 0) {
		enabled = offload_csum(task, queue_info, skb);
		if (enabled)
			offload |= TX_OFFLOAD_CSUM;
	} else {
		return -EPROTONOSUPPORT;
	}

	if (unlikely(skb_vlan_tag_present(skb))) {
		vlan_tag = skb_vlan_tag_get(skb);
		offload_vlan(task, queue_info, vlan_tag,
			     vlan_tag >> VLAN_PRIO_SHIFT);
		offload |= TX_OFFLOAD_VLAN;
	}

	if (offload)
		hinic_task_set_l2hdr(task, skb_network_offset(skb));

	/* payload offset should not more than 221 */
	if (HINIC_SQ_CTRL_GET(*queue_info, QUEUE_INFO_PLDOFF) >
	    MAX_PAYLOAD_OFFSET) {
		return -EPROTONOSUPPORT;
	}

	/* mss should not less than 80 */
	if (HINIC_SQ_CTRL_GET(*queue_info, QUEUE_INFO_MSS) < HINIC_MSS_MIN) {
		*queue_info = HINIC_SQ_CTRL_CLEAR(*queue_info, QUEUE_INFO_MSS);
		*queue_info |= HINIC_SQ_CTRL_SET(HINIC_MSS_MIN, QUEUE_INFO_MSS);
	}

	return 0;
}