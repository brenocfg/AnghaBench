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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_copy; } ;
struct hns3_enet_ring {int /*<<< orphan*/  syncp; TYPE_1__ stats; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned int HNS3_MAX_BD_NUM_NORMAL ; 
 unsigned int HNS3_MAX_BD_NUM_TSO ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 unsigned int hns3_nic_bd_num (struct sk_buff*) ; 
 int /*<<< orphan*/  hns3_skb_need_linearized (struct sk_buff*) ; 
 unsigned int ring_space (struct hns3_enet_ring*) ; 
 struct sk_buff* skb_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int hns3_nic_maybe_stop_tx(struct hns3_enet_ring *ring,
				  struct sk_buff **out_skb)
{
	struct sk_buff *skb = *out_skb;
	unsigned int bd_num;

	bd_num = hns3_nic_bd_num(skb);
	if (unlikely(bd_num > HNS3_MAX_BD_NUM_NORMAL)) {
		struct sk_buff *new_skb;

		if (skb_is_gso(skb) && bd_num <= HNS3_MAX_BD_NUM_TSO &&
		    !hns3_skb_need_linearized(skb))
			goto out;

		/* manual split the send packet */
		new_skb = skb_copy(skb, GFP_ATOMIC);
		if (!new_skb)
			return -ENOMEM;
		dev_kfree_skb_any(skb);
		*out_skb = new_skb;

		bd_num = hns3_nic_bd_num(new_skb);
		if ((skb_is_gso(new_skb) && bd_num > HNS3_MAX_BD_NUM_TSO) ||
		    (!skb_is_gso(new_skb) && bd_num > HNS3_MAX_BD_NUM_NORMAL))
			return -ENOMEM;

		u64_stats_update_begin(&ring->syncp);
		ring->stats.tx_copy++;
		u64_stats_update_end(&ring->syncp);
	}

out:
	if (unlikely(ring_space(ring) < bd_num))
		return -EBUSY;

	return bd_num;
}