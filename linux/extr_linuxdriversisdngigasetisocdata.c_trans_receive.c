#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_1__* bas; } ;
struct bc_state {int rx_bufsize; TYPE_2__ hw; struct sk_buff* rx_skb; int /*<<< orphan*/  ignore; } ;
struct TYPE_3__ {int /*<<< orphan*/  goodbytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_STREAM_DUMP ; 
 int /*<<< orphan*/  bitrev8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_bytes (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 struct sk_buff* gigaset_new_rx_skb (struct bc_state*) ; 
 int /*<<< orphan*/  gigaset_skb_rcvd (struct bc_state*,struct sk_buff*) ; 
 unsigned char* skb_put (struct sk_buff*,unsigned int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void trans_receive(unsigned char *src, unsigned count,
				 struct bc_state *bcs)
{
	struct sk_buff *skb;
	int dobytes;
	unsigned char *dst;

	if (unlikely(bcs->ignore)) {
		bcs->ignore--;
		return;
	}
	skb = bcs->rx_skb;
	if (skb == NULL) {
		skb = gigaset_new_rx_skb(bcs);
		if (skb == NULL)
			return;
	}
	dobytes = bcs->rx_bufsize - skb->len;
	while (count > 0) {
		dst = skb_put(skb, count < dobytes ? count : dobytes);
		while (count > 0 && dobytes > 0) {
			*dst++ = bitrev8(*src++);
			count--;
			dobytes--;
		}
		if (dobytes == 0) {
			dump_bytes(DEBUG_STREAM_DUMP,
				   "rcv data", skb->data, skb->len);
			bcs->hw.bas->goodbytes += skb->len;
			gigaset_skb_rcvd(bcs, skb);
			skb = gigaset_new_rx_skb(bcs);
			if (skb == NULL)
				return;
			dobytes = bcs->rx_bufsize;
		}
	}
}