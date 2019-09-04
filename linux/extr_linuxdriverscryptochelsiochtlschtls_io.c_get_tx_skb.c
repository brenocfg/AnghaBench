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
struct sock {int /*<<< orphan*/  sk_allocation; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 scalar_t__ TX_HEADER_LEN ; 
 int /*<<< orphan*/  ULPCB_FLAG_NEED_HDR ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_entail (struct sock*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *get_tx_skb(struct sock *sk, int size)
{
	struct sk_buff *skb;

	skb = alloc_skb(size + TX_HEADER_LEN, sk->sk_allocation);
	if (likely(skb)) {
		skb_reserve(skb, TX_HEADER_LEN);
		skb_entail(sk, skb, ULPCB_FLAG_NEED_HDR);
		skb_reset_transport_header(skb);
	}
	return skb;
}