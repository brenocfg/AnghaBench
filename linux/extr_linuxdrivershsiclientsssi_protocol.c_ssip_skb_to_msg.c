#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  data; } ;
struct scatterlist {int dummy; } ;
struct TYPE_5__ {unsigned int nents; struct scatterlist* sgl; } ;
struct hsi_msg {TYPE_1__ sgt; } ;
struct TYPE_6__ {int /*<<< orphan*/  p; } ;
struct TYPE_7__ {int /*<<< orphan*/  page_offset; int /*<<< orphan*/  size; TYPE_2__ page; } ;
typedef  TYPE_3__ skb_frag_t ;
struct TYPE_8__ {int nr_frags; TYPE_3__* frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 TYPE_4__* skb_shinfo (struct sk_buff*) ; 

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
		sg_set_page(sg, frag->page.p, frag->size, frag->page_offset);
	}
}