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
struct hnae_ring {int max_desc_num_per_pkt; } ;
struct TYPE_2__ {int nr_frags; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int ring_space (struct hnae_ring*) ; 
 struct sk_buff* skb_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int hns_nic_maybe_stop_tx(
	struct sk_buff **out_skb, int *bnum, struct hnae_ring *ring)
{
	struct sk_buff *skb = *out_skb;
	struct sk_buff *new_skb = NULL;
	int buf_num;

	/* no. of segments (plus a header) */
	buf_num = skb_shinfo(skb)->nr_frags + 1;

	if (unlikely(buf_num > ring->max_desc_num_per_pkt)) {
		if (ring_space(ring) < 1)
			return -EBUSY;

		new_skb = skb_copy(skb, GFP_ATOMIC);
		if (!new_skb)
			return -ENOMEM;

		dev_kfree_skb_any(skb);
		*out_skb = new_skb;
		buf_num = 1;
	} else if (buf_num > ring_space(ring)) {
		return -EBUSY;
	}

	*bnum = buf_num;
	return 0;
}