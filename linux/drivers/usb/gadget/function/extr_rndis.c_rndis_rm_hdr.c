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
struct sk_buff_head {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct gether {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EINVAL ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  RNDIS_MSG_PACKET ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ get_unaligned (int /*<<< orphan*/ ) ; 
 scalar_t__ get_unaligned_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,scalar_t__) ; 

int rndis_rm_hdr(struct gether *port,
			struct sk_buff *skb,
			struct sk_buff_head *list)
{
	/* tmp points to a struct rndis_packet_msg_type */
	__le32 *tmp = (void *)skb->data;

	/* MessageType, MessageLength */
	if (cpu_to_le32(RNDIS_MSG_PACKET)
			!= get_unaligned(tmp++)) {
		dev_kfree_skb_any(skb);
		return -EINVAL;
	}
	tmp++;

	/* DataOffset, DataLength */
	if (!skb_pull(skb, get_unaligned_le32(tmp++) + 8)) {
		dev_kfree_skb_any(skb);
		return -EOVERFLOW;
	}
	skb_trim(skb, get_unaligned_le32(tmp++));

	skb_queue_tail(list, skb);
	return 0;
}