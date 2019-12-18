#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  struct sk_buff sk_buff ;
struct hns3_enet_ring {struct sk_buff* skb; int pending_buf; TYPE_1__* tqp; } ;
struct TYPE_2__ {scalar_t__ io_base; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ HNS3_RING_RX_RING_FBDNUM_REG ; 
 int RCB_NOF_ALLOC_RX_BUFF_ONCE ; 
 int hns3_desc_unused (struct hns3_enet_ring*) ; 
 int hns3_handle_rx_bd (struct hns3_enet_ring*,struct sk_buff**) ; 
 int /*<<< orphan*/  hns3_nic_alloc_rx_buffers (struct hns3_enet_ring*,int) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  rmb () ; 
 scalar_t__ unlikely (int) ; 

int hns3_clean_rx_ring(struct hns3_enet_ring *ring, int budget,
		       void (*rx_fn)(struct hns3_enet_ring *, struct sk_buff *))
{
#define RCB_NOF_ALLOC_RX_BUFF_ONCE 16
	int unused_count = hns3_desc_unused(ring);
	struct sk_buff *skb = ring->skb;
	int recv_pkts = 0;
	int recv_bds = 0;
	int err, num;

	num = readl_relaxed(ring->tqp->io_base + HNS3_RING_RX_RING_FBDNUM_REG);
	rmb(); /* Make sure num taken effect before the other data is touched */

	num -= unused_count;
	unused_count -= ring->pending_buf;

	while (recv_pkts < budget && recv_bds < num) {
		/* Reuse or realloc buffers */
		if (unused_count >= RCB_NOF_ALLOC_RX_BUFF_ONCE) {
			hns3_nic_alloc_rx_buffers(ring, unused_count);
			unused_count = hns3_desc_unused(ring) -
					ring->pending_buf;
		}

		/* Poll one pkt */
		err = hns3_handle_rx_bd(ring, &skb);
		if (unlikely(!skb)) /* This fault cannot be repaired */
			goto out;

		if (err == -ENXIO) { /* Do not get FE for the packet */
			goto out;
		} else if (unlikely(err)) {  /* Do jump the err */
			recv_bds += ring->pending_buf;
			unused_count += ring->pending_buf;
			ring->skb = NULL;
			ring->pending_buf = 0;
			continue;
		}

		rx_fn(ring, skb);
		recv_bds += ring->pending_buf;
		unused_count += ring->pending_buf;
		ring->skb = NULL;
		ring->pending_buf = 0;

		recv_pkts++;
	}

out:
	/* Make all data has been write before submit */
	if (unused_count > 0)
		hns3_nic_alloc_rx_buffers(ring, unused_count);

	return recv_pkts;
}