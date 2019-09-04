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
struct nicvf {scalar_t__ hw_tso; scalar_t__ t88; } ;
struct TYPE_2__ {scalar_t__ nr_frags; scalar_t__ gso_size; } ;

/* Variables and functions */
 int MIN_SQ_DESC_PER_PKT_XMIT ; 
 scalar_t__ POST_CQE_DESC_COUNT ; 
 int nicvf_tso_count_subdescs (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static int nicvf_sq_subdesc_required(struct nicvf *nic, struct sk_buff *skb)
{
	int subdesc_cnt = MIN_SQ_DESC_PER_PKT_XMIT;

	if (skb_shinfo(skb)->gso_size && !nic->hw_tso) {
		subdesc_cnt = nicvf_tso_count_subdescs(skb);
		return subdesc_cnt;
	}

	/* Dummy descriptors to get TSO pkt completion notification */
	if (nic->t88 && nic->hw_tso && skb_shinfo(skb)->gso_size)
		subdesc_cnt += POST_CQE_DESC_COUNT;

	if (skb_shinfo(skb)->nr_frags)
		subdesc_cnt += skb_shinfo(skb)->nr_frags;

	return subdesc_cnt;
}