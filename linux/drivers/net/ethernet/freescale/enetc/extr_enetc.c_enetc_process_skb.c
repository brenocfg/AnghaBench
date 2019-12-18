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
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct enetc_bdr {int /*<<< orphan*/  ndev; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enetc_process_skb(struct enetc_bdr *rx_ring,
			      struct sk_buff *skb)
{
	skb_record_rx_queue(skb, rx_ring->index);
	skb->protocol = eth_type_trans(skb, rx_ring->ndev);
}