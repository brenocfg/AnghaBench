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
struct sk_buff {unsigned char* data; int len; } ;
struct hfi1_vnic_rx_queue {int /*<<< orphan*/  skbq; } ;

/* Variables and functions */
 int OPA_VNIC_ICRC_TAIL_LEN ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline struct sk_buff *hfi1_vnic_get_skb(struct hfi1_vnic_rx_queue *rxq)
{
	unsigned char *pad_info;
	struct sk_buff *skb;

	skb = skb_dequeue(&rxq->skbq);
	if (unlikely(!skb))
		return NULL;

	/* remove tail padding and icrc */
	pad_info = skb->data + skb->len - 1;
	skb_trim(skb, (skb->len - OPA_VNIC_ICRC_TAIL_LEN -
		       ((*pad_info) & 0x7)));

	return skb;
}