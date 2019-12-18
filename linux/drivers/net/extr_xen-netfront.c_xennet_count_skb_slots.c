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
struct sk_buff {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_2__ {int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 int gnttab_count_grant (unsigned long,unsigned long) ; 
 unsigned long offset_in_page (int /*<<< orphan*/ ) ; 
 unsigned long skb_frag_off (int /*<<< orphan*/ *) ; 
 unsigned long skb_frag_size (int /*<<< orphan*/ *) ; 
 unsigned long skb_headlen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static int xennet_count_skb_slots(struct sk_buff *skb)
{
	int i, frags = skb_shinfo(skb)->nr_frags;
	int slots;

	slots = gnttab_count_grant(offset_in_page(skb->data),
				   skb_headlen(skb));

	for (i = 0; i < frags; i++) {
		skb_frag_t *frag = skb_shinfo(skb)->frags + i;
		unsigned long size = skb_frag_size(frag);
		unsigned long offset = skb_frag_off(frag);

		/* Skip unused frames from start of page */
		offset &= ~PAGE_MASK;

		slots += gnttab_count_grant(offset, size);
	}

	return slots;
}