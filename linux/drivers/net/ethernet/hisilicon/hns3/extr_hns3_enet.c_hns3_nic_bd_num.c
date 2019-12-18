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
struct sk_buff {scalar_t__ len; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_2__ {int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 scalar_t__ HNS3_MAX_BD_SIZE ; 
 unsigned int hns3_tx_bd_count (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  skb_frag_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static unsigned int hns3_nic_bd_num(struct sk_buff *skb)
{
	unsigned int bd_num;
	int i;

	/* if the total len is within the max bd limit */
	if (likely(skb->len <= HNS3_MAX_BD_SIZE))
		return skb_shinfo(skb)->nr_frags + 1;

	bd_num = hns3_tx_bd_count(skb_headlen(skb));

	for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		bd_num += hns3_tx_bd_count(skb_frag_size(frag));
	}

	return bd_num;
}