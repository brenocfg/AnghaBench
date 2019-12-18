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
typedef  union iavf_rx_desc {int dummy; } iavf_rx_desc ;
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct iavf_ring {int /*<<< orphan*/  netdev; int /*<<< orphan*/  queue_index; int /*<<< orphan*/  vsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iavf_rx_checksum (int /*<<< orphan*/ ,struct sk_buff*,union iavf_rx_desc*) ; 
 int /*<<< orphan*/  iavf_rx_hash (struct iavf_ring*,union iavf_rx_desc*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
void iavf_process_skb_fields(struct iavf_ring *rx_ring,
			     union iavf_rx_desc *rx_desc, struct sk_buff *skb,
			     u8 rx_ptype)
{
	iavf_rx_hash(rx_ring, rx_desc, skb, rx_ptype);

	iavf_rx_checksum(rx_ring->vsi, skb, rx_desc);

	skb_record_rx_queue(skb, rx_ring->queue_index);

	/* modifies the skb - consumes the enet header */
	skb->protocol = eth_type_trans(skb, rx_ring->netdev);
}