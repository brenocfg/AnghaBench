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
struct TYPE_2__ {unsigned int gso_size; int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int HNS3_MAX_BD_NUM_NORMAL ; 
 scalar_t__ hns3_gso_hdr_len (struct sk_buff*) ; 
 scalar_t__ skb_frag_size (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static bool hns3_skb_need_linearized(struct sk_buff *skb)
{
	int bd_limit = HNS3_MAX_BD_NUM_NORMAL - 1;
	unsigned int tot_len = 0;
	int i;

	for (i = 0; i < bd_limit; i++)
		tot_len += skb_frag_size(&skb_shinfo(skb)->frags[i]);

	/* ensure headlen + the first 7 frags is greater than mss + header
	 * and the first 7 frags is greater than mss.
	 */
	if (((tot_len + skb_headlen(skb)) < (skb_shinfo(skb)->gso_size +
	    hns3_gso_hdr_len(skb))) || (tot_len < skb_shinfo(skb)->gso_size))
		return true;

	/* ensure the remaining continuous 7 buffer is greater than mss */
	for (i = 0; i < (skb_shinfo(skb)->nr_frags - bd_limit - 1); i++) {
		tot_len -= skb_frag_size(&skb_shinfo(skb)->frags[i]);
		tot_len += skb_frag_size(&skb_shinfo(skb)->frags[i + bd_limit]);

		if (tot_len < skb_shinfo(skb)->gso_size)
			return true;
	}

	return false;
}