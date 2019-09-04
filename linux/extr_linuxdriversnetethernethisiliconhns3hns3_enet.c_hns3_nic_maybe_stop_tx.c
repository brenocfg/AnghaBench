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
struct hns3_enet_ring {int dummy; } ;
struct TYPE_2__ {int nr_frags; } ;

/* Variables and functions */
 int EBUSY ; 
 int ring_space (struct hns3_enet_ring*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static int hns3_nic_maybe_stop_tx(struct sk_buff **out_skb, int *bnum,
				  struct hns3_enet_ring *ring)
{
	struct sk_buff *skb = *out_skb;
	int buf_num;

	/* No. of segments (plus a header) */
	buf_num = skb_shinfo(skb)->nr_frags + 1;

	if (buf_num > ring_space(ring))
		return -EBUSY;

	*bnum = buf_num;

	return 0;
}