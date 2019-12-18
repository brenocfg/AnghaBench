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
struct lan743x_tx {int dummy; } ;
struct TYPE_2__ {int nr_frags; } ;

/* Variables and functions */
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static int lan743x_tx_get_desc_cnt(struct lan743x_tx *tx,
				   struct sk_buff *skb)
{
	int result = 1; /* 1 for the main skb buffer */
	int nr_frags = 0;

	if (skb_is_gso(skb))
		result++; /* requires an extension descriptor */
	nr_frags = skb_shinfo(skb)->nr_frags;
	result += nr_frags; /* 1 for each fragment buffer */
	return result;
}