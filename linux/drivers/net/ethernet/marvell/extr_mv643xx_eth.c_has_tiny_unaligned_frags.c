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
struct TYPE_2__ {int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int skb_frag_off (int /*<<< orphan*/  const*) ; 
 int skb_frag_size (int /*<<< orphan*/  const*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static inline unsigned int has_tiny_unaligned_frags(struct sk_buff *skb)
{
	int frag;

	for (frag = 0; frag < skb_shinfo(skb)->nr_frags; frag++) {
		const skb_frag_t *fragp = &skb_shinfo(skb)->frags[frag];

		if (skb_frag_size(fragp) <= 8 && skb_frag_off(fragp) & 7)
			return 1;
	}

	return 0;
}