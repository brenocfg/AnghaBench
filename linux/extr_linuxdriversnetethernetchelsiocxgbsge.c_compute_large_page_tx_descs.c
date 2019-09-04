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
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_2__ {unsigned int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 unsigned int PAGE_SIZE ; 
 unsigned int SGE_TX_DESC_MAX_PLEN ; 
 unsigned int skb_frag_size (int /*<<< orphan*/  const*) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static inline unsigned int compute_large_page_tx_descs(struct sk_buff *skb)
{
	unsigned int count = 0;

	if (PAGE_SIZE > SGE_TX_DESC_MAX_PLEN) {
		unsigned int nfrags = skb_shinfo(skb)->nr_frags;
		unsigned int i, len = skb_headlen(skb);
		while (len > SGE_TX_DESC_MAX_PLEN) {
			count++;
			len -= SGE_TX_DESC_MAX_PLEN;
		}
		for (i = 0; nfrags--; i++) {
			const skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
			len = skb_frag_size(frag);
			while (len > SGE_TX_DESC_MAX_PLEN) {
				count++;
				len -= SGE_TX_DESC_MAX_PLEN;
			}
		}
	}
	return count;
}