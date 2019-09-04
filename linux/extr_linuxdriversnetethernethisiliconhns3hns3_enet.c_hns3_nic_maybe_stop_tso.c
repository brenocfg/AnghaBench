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
struct skb_frag_struct {int dummy; } ;
struct sk_buff {int dummy; } ;
struct hns3_enet_ring {int dummy; } ;
struct TYPE_2__ {int nr_frags; struct skb_frag_struct* frags; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int HNS3_MAX_BD_PER_FRAG ; 
 int HNS3_MAX_BD_SIZE ; 
 int ring_space (struct hns3_enet_ring*) ; 
 int skb_frag_size (struct skb_frag_struct*) ; 
 int skb_headlen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static int hns3_nic_maybe_stop_tso(struct sk_buff **out_skb, int *bnum,
				   struct hns3_enet_ring *ring)
{
	struct sk_buff *skb = *out_skb;
	struct skb_frag_struct *frag;
	int bdnum_for_frag;
	int frag_num;
	int buf_num;
	int size;
	int i;

	size = skb_headlen(skb);
	buf_num = (size + HNS3_MAX_BD_SIZE - 1) / HNS3_MAX_BD_SIZE;

	frag_num = skb_shinfo(skb)->nr_frags;
	for (i = 0; i < frag_num; i++) {
		frag = &skb_shinfo(skb)->frags[i];
		size = skb_frag_size(frag);
		bdnum_for_frag =
			(size + HNS3_MAX_BD_SIZE - 1) / HNS3_MAX_BD_SIZE;
		if (bdnum_for_frag > HNS3_MAX_BD_PER_FRAG)
			return -ENOMEM;

		buf_num += bdnum_for_frag;
	}

	if (buf_num > ring_space(ring))
		return -EBUSY;

	*bnum = buf_num;
	return 0;
}