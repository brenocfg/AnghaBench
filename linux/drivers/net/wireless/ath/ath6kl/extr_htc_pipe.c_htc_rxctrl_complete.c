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
struct htc_target {int dummy; } ;
struct htc_packet {scalar_t__ endpoint; int /*<<< orphan*/  status; struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECANCELED ; 
 scalar_t__ ENDPOINT_0 ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 

__attribute__((used)) static void htc_rxctrl_complete(struct htc_target *context,
				struct htc_packet *packet)
{
	struct sk_buff *skb = packet->skb;

	if (packet->endpoint == ENDPOINT_0 &&
	    packet->status == -ECANCELED &&
	    skb != NULL)
		dev_kfree_skb(skb);
}