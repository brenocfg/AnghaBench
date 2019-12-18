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
struct sk_buff {unsigned char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MAC_SKB_BACK_PTR_SIZE ; 
 int /*<<< orphan*/  XLR_RX_BUF_SIZE ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,struct sk_buff**,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned char *xlr_alloc_skb(void)
{
	struct sk_buff *skb;
	int buf_len = sizeof(struct sk_buff *);
	unsigned char *skb_data;

	/* skb->data is cache aligned */
	skb = alloc_skb(XLR_RX_BUF_SIZE, GFP_ATOMIC);
	if (!skb)
		return NULL;
	skb_data = skb->data;
	skb_reserve(skb, MAC_SKB_BACK_PTR_SIZE);
	memcpy(skb_data, &skb, buf_len);

	return skb->data;
}