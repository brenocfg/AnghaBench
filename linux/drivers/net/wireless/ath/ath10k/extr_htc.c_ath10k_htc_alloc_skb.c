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
struct sk_buff {scalar_t__ data; } ;
struct ath10k_htc_hdr {int dummy; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,int) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

struct sk_buff *ath10k_htc_alloc_skb(struct ath10k *ar, int size)
{
	struct sk_buff *skb;

	skb = dev_alloc_skb(size + sizeof(struct ath10k_htc_hdr));
	if (!skb)
		return NULL;

	skb_reserve(skb, sizeof(struct ath10k_htc_hdr));

	/* FW/HTC requires 4-byte aligned streams */
	if (!IS_ALIGNED((unsigned long)skb->data, 4))
		ath10k_warn(ar, "Unaligned HTC tx skb\n");

	return skb;
}