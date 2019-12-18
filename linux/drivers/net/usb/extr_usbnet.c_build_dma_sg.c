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
struct urb {unsigned int num_sgs; unsigned int transfer_buffer_length; int /*<<< orphan*/ * sg; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct scatterlist {int dummy; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_2__ {int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/ * kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sg_set_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sg_set_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_frag_page (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_frag_size (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_headlen (struct sk_buff const*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff const*) ; 

__attribute__((used)) static int build_dma_sg(const struct sk_buff *skb, struct urb *urb)
{
	unsigned num_sgs, total_len = 0;
	int i, s = 0;

	num_sgs = skb_shinfo(skb)->nr_frags + 1;
	if (num_sgs == 1)
		return 0;

	/* reserve one for zero packet */
	urb->sg = kmalloc_array(num_sgs + 1, sizeof(struct scatterlist),
				GFP_ATOMIC);
	if (!urb->sg)
		return -ENOMEM;

	urb->num_sgs = num_sgs;
	sg_init_table(urb->sg, urb->num_sgs + 1);

	sg_set_buf(&urb->sg[s++], skb->data, skb_headlen(skb));
	total_len += skb_headlen(skb);

	for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
		skb_frag_t *f = &skb_shinfo(skb)->frags[i];

		total_len += skb_frag_size(f);
		sg_set_page(&urb->sg[i + s], skb_frag_page(f), skb_frag_size(f),
			    skb_frag_off(f));
	}
	urb->transfer_buffer_length = total_len;

	return 1;
}