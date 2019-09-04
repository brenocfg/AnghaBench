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
struct bc_state {int /*<<< orphan*/  rx_fcs; int /*<<< orphan*/ * rx_skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPP_INITFCS ; 
 int /*<<< orphan*/  gigaset_new_rx_skb (struct bc_state*) ; 
 int /*<<< orphan*/  skb_trim (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void hdlc_flush(struct bc_state *bcs)
{
	/* clear skb or allocate new if not skipping */
	if (bcs->rx_skb != NULL)
		skb_trim(bcs->rx_skb, 0);
	else
		gigaset_new_rx_skb(bcs);

	/* reset packet state */
	bcs->rx_fcs = PPP_INITFCS;
}