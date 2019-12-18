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
struct sk_buff {void* data; } ;
struct seq_file {int dummy; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_2__ {int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 void* skb_frag_address_safe (int /*<<< orphan*/  const*) ; 
 int skb_frag_size (int /*<<< orphan*/  const*) ; 
 int skb_headlen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  wil_seq_hexdump (struct seq_file*,void*,int,char*) ; 

__attribute__((used)) static void wil_seq_print_skb(struct seq_file *s, struct sk_buff *skb)
{
	int i = 0;
	int len = skb_headlen(skb);
	void *p = skb->data;
	int nr_frags = skb_shinfo(skb)->nr_frags;

	seq_printf(s, "    len = %d\n", len);
	wil_seq_hexdump(s, p, len, "      : ");

	if (nr_frags) {
		seq_printf(s, "    nr_frags = %d\n", nr_frags);
		for (i = 0; i < nr_frags; i++) {
			const skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

			len = skb_frag_size(frag);
			p = skb_frag_address_safe(frag);
			seq_printf(s, "    [%2d] : len = %d\n", i, len);
			wil_seq_hexdump(s, p, len, "      : ");
		}
	}
}