#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  data; } ;
struct scatterlist {int dummy; } ;
struct TYPE_3__ {unsigned int nents; struct scatterlist* sgl; } ;
struct hsi_msg {TYPE_1__ sgt; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_4__ {int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_frag_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_frag_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void ssip_skb_to_msg(struct sk_buff *skb, struct hsi_msg *msg)
{
	skb_frag_t *frag;
	struct scatterlist *sg;
	int i;

	BUG_ON(msg->sgt.nents != (unsigned int)(skb_shinfo(skb)->nr_frags + 1));

	sg = msg->sgt.sgl;
	sg_set_buf(sg, skb->data, skb_headlen(skb));
	for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
		sg = sg_next(sg);
		BUG_ON(!sg);
		frag = &skb_shinfo(skb)->frags[i];
		sg_set_page(sg, skb_frag_page(frag), skb_frag_size(frag),
				skb_frag_off(frag));
	}
}