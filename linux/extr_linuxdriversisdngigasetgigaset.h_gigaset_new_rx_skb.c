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
struct sk_buff {int dummy; } ;
struct cardstate {unsigned short hw_hdr_len; int /*<<< orphan*/  dev; } ;
struct bc_state {struct sk_buff* rx_skb; scalar_t__ rx_bufsize; scalar_t__ ignore; struct cardstate* cs; } ;

/* Variables and functions */
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,unsigned short) ; 

__attribute__((used)) static inline struct sk_buff *gigaset_new_rx_skb(struct bc_state *bcs)
{
	struct cardstate *cs = bcs->cs;
	unsigned short hw_hdr_len = cs->hw_hdr_len;

	if (bcs->ignore) {
		bcs->rx_skb = NULL;
	} else {
		bcs->rx_skb = dev_alloc_skb(bcs->rx_bufsize + hw_hdr_len);
		if (bcs->rx_skb == NULL)
			dev_warn(cs->dev, "could not allocate skb\n");
		else
			skb_reserve(bcs->rx_skb, hw_hdr_len);
	}
	return bcs->rx_skb;
}