#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  staterr; } ;
union fm10k_rx_desc {TYPE_1__ d; } ;
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct TYPE_5__ {unsigned int packets; unsigned int bytes; } ;
struct fm10k_ring {int /*<<< orphan*/  syncp; TYPE_2__ stats; struct sk_buff* skb; int /*<<< orphan*/  next_to_clean; } ;
struct TYPE_6__ {unsigned int total_packets; unsigned int total_bytes; } ;
struct fm10k_q_vector {TYPE_3__ rx; } ;

/* Variables and functions */
 scalar_t__ FM10K_RX_BUFFER_WRITE ; 
 union fm10k_rx_desc* FM10K_RX_DESC (struct fm10k_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  fm10k_alloc_rx_buffers (struct fm10k_ring*,scalar_t__) ; 
 scalar_t__ fm10k_cleanup_headers (struct fm10k_ring*,union fm10k_rx_desc*,struct sk_buff*) ; 
 scalar_t__ fm10k_desc_unused (struct fm10k_ring*) ; 
 struct sk_buff* fm10k_fetch_rx_buffer (struct fm10k_ring*,union fm10k_rx_desc*,struct sk_buff*) ; 
 scalar_t__ fm10k_is_non_eop (struct fm10k_ring*,union fm10k_rx_desc*) ; 
 scalar_t__ fm10k_process_skb_fields (struct fm10k_ring*,union fm10k_rx_desc*,struct sk_buff*) ; 
 int /*<<< orphan*/  fm10k_receive_skb (struct fm10k_q_vector*,struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fm10k_clean_rx_irq(struct fm10k_q_vector *q_vector,
			      struct fm10k_ring *rx_ring,
			      int budget)
{
	struct sk_buff *skb = rx_ring->skb;
	unsigned int total_bytes = 0, total_packets = 0;
	u16 cleaned_count = fm10k_desc_unused(rx_ring);

	while (likely(total_packets < budget)) {
		union fm10k_rx_desc *rx_desc;

		/* return some buffers to hardware, one at a time is too slow */
		if (cleaned_count >= FM10K_RX_BUFFER_WRITE) {
			fm10k_alloc_rx_buffers(rx_ring, cleaned_count);
			cleaned_count = 0;
		}

		rx_desc = FM10K_RX_DESC(rx_ring, rx_ring->next_to_clean);

		if (!rx_desc->d.staterr)
			break;

		/* This memory barrier is needed to keep us from reading
		 * any other fields out of the rx_desc until we know the
		 * descriptor has been written back
		 */
		dma_rmb();

		/* retrieve a buffer from the ring */
		skb = fm10k_fetch_rx_buffer(rx_ring, rx_desc, skb);

		/* exit if we failed to retrieve a buffer */
		if (!skb)
			break;

		cleaned_count++;

		/* fetch next buffer in frame if non-eop */
		if (fm10k_is_non_eop(rx_ring, rx_desc))
			continue;

		/* verify the packet layout is correct */
		if (fm10k_cleanup_headers(rx_ring, rx_desc, skb)) {
			skb = NULL;
			continue;
		}

		/* populate checksum, timestamp, VLAN, and protocol */
		total_bytes += fm10k_process_skb_fields(rx_ring, rx_desc, skb);

		fm10k_receive_skb(q_vector, skb);

		/* reset skb pointer */
		skb = NULL;

		/* update budget accounting */
		total_packets++;
	}

	/* place incomplete frames back on ring for completion */
	rx_ring->skb = skb;

	u64_stats_update_begin(&rx_ring->syncp);
	rx_ring->stats.packets += total_packets;
	rx_ring->stats.bytes += total_bytes;
	u64_stats_update_end(&rx_ring->syncp);
	q_vector->rx.total_packets += total_packets;
	q_vector->rx.total_bytes += total_bytes;

	return total_packets;
}