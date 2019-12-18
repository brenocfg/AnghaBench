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
typedef  size_t u8 ;
struct sk_buff {int dummy; } ;
struct pkt_gl {size_t nfrags; TYPE_1__* frags; } ;
struct TYPE_4__ {size_t nr_frags; } ;
struct TYPE_3__ {int /*<<< orphan*/  page; scalar_t__ size; scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_fill_page_desc (struct sk_buff*,size_t,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void
cxgbit_copy_frags(struct sk_buff *skb, const struct pkt_gl *gl,
		  unsigned int offset)
{
	u8 skb_frag_idx = skb_shinfo(skb)->nr_frags;
	u8 i;

	/* usually there's just one frag */
	__skb_fill_page_desc(skb, skb_frag_idx, gl->frags[0].page,
			     gl->frags[0].offset + offset,
			     gl->frags[0].size - offset);
	for (i = 1; i < gl->nfrags; i++)
		__skb_fill_page_desc(skb, skb_frag_idx + i,
				     gl->frags[i].page,
				     gl->frags[i].offset,
				     gl->frags[i].size);

	skb_shinfo(skb)->nr_frags += gl->nfrags;

	/* get a reference to the last page, we don't own it */
	get_page(gl->frags[gl->nfrags - 1].page);
}