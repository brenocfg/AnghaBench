#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct skb_shared_info {int nr_frags; int /*<<< orphan*/ * frags; } ;
struct sk_buff {int len; } ;

/* Variables and functions */
 void* skb_frag_address_safe (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool is_inline(int inline_thold, const struct sk_buff *skb,
		      const struct skb_shared_info *shinfo,
		      void **pfrag)
{
	void *ptr;

	if (skb->len > inline_thold || !inline_thold)
		return false;

	if (shinfo->nr_frags == 1) {
		ptr = skb_frag_address_safe(&shinfo->frags[0]);
		if (unlikely(!ptr))
			return false;
		*pfrag = ptr;
		return true;
	}
	if (shinfo->nr_frags)
		return false;
	return true;
}