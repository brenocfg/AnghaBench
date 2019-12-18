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
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct htc_packet {int dummy; } ;

/* Variables and functions */
 scalar_t__ ATH6KL_DATA_OFFSET ; 
 scalar_t__ ATH6KL_HTC_ALIGN_BYTES ; 
 int L1_CACHE_BYTES ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 scalar_t__ roundup (scalar_t__,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

struct sk_buff *ath6kl_buf_alloc(int size)
{
	struct sk_buff *skb;
	u16 reserved;

	/* Add chacheline space at front and back of buffer */
	reserved = roundup((2 * L1_CACHE_BYTES) + ATH6KL_DATA_OFFSET +
		   sizeof(struct htc_packet) + ATH6KL_HTC_ALIGN_BYTES, 4);
	skb = dev_alloc_skb(size + reserved);

	if (skb)
		skb_reserve(skb, reserved - L1_CACHE_BYTES);
	return skb;
}