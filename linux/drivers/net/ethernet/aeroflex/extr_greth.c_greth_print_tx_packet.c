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
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  skb_frag_address (int /*<<< orphan*/ *) ; 
 int skb_frag_size (int /*<<< orphan*/ *) ; 
 int skb_headlen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void greth_print_tx_packet(struct sk_buff *skb)
{
	int i;
	int length;

	if (skb_shinfo(skb)->nr_frags == 0)
		length = skb->len;
	else
		length = skb_headlen(skb);

	print_hex_dump(KERN_DEBUG, "TX: ", DUMP_PREFIX_OFFSET, 16, 1,
			skb->data, length, true);

	for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {

		print_hex_dump(KERN_DEBUG, "TX: ", DUMP_PREFIX_OFFSET, 16, 1,
			       skb_frag_address(&skb_shinfo(skb)->frags[i]),
			       skb_frag_size(&skb_shinfo(skb)->frags[i]), true);
	}
}