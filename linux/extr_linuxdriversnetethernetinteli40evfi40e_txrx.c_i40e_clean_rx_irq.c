#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  l2tag1; } ;
struct TYPE_12__ {TYPE_3__ lo_dword; } ;
struct TYPE_10__ {int /*<<< orphan*/  status_error_len; } ;
struct TYPE_13__ {TYPE_4__ qword0; TYPE_2__ qword1; } ;
union i40e_rx_desc {TYPE_5__ wb; } ;
typedef  int u8 ;
typedef  int u64 ;
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ len; } ;
struct i40e_rx_buffer {int /*<<< orphan*/  pagecnt_bias; } ;
struct TYPE_14__ {unsigned int packets; unsigned int bytes; } ;
struct TYPE_9__ {int /*<<< orphan*/  alloc_buff_failed; } ;
struct i40e_ring {TYPE_8__* q_vector; int /*<<< orphan*/  syncp; TYPE_6__ stats; struct sk_buff* skb; TYPE_1__ rx_stats; int /*<<< orphan*/  next_to_clean; } ;
struct TYPE_15__ {unsigned int total_packets; unsigned int total_bytes; } ;
struct TYPE_16__ {TYPE_7__ rx; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ I40E_DESC_UNUSED (struct i40e_ring*) ; 
 int /*<<< orphan*/  I40E_RXD_QW1_ERROR_SHIFT ; 
 int I40E_RXD_QW1_LENGTH_PBUF_MASK ; 
 int I40E_RXD_QW1_LENGTH_PBUF_SHIFT ; 
 int I40E_RXD_QW1_PTYPE_MASK ; 
 int I40E_RXD_QW1_PTYPE_SHIFT ; 
 scalar_t__ I40E_RX_BUFFER_WRITE ; 
 union i40e_rx_desc* I40E_RX_DESC (struct i40e_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_RX_DESC_STATUS_L2TAG1P_SHIFT ; 
 int /*<<< orphan*/  clean_rx_irq ; 
 int /*<<< orphan*/  clean_rx_irq_rx ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  i40e_add_rx_frag (struct i40e_ring*,struct i40e_rx_buffer*,struct sk_buff*,unsigned int) ; 
 struct sk_buff* i40e_build_skb (struct i40e_ring*,struct i40e_rx_buffer*,unsigned int) ; 
 scalar_t__ i40e_cleanup_headers (struct i40e_ring*,struct sk_buff*) ; 
 struct sk_buff* i40e_construct_skb (struct i40e_ring*,struct i40e_rx_buffer*,unsigned int) ; 
 struct i40e_rx_buffer* i40e_get_rx_buffer (struct i40e_ring*,unsigned int) ; 
 scalar_t__ i40e_is_non_eop (struct i40e_ring*,union i40e_rx_desc*,struct sk_buff*) ; 
 int /*<<< orphan*/  i40e_put_rx_buffer (struct i40e_ring*,struct i40e_rx_buffer*) ; 
 int /*<<< orphan*/  i40e_receive_skb (struct i40e_ring*,struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  i40e_test_staterr (union i40e_rx_desc*,int) ; 
 int /*<<< orphan*/  i40e_trace (int /*<<< orphan*/ ,struct i40e_ring*,union i40e_rx_desc*,struct sk_buff*) ; 
 scalar_t__ i40evf_alloc_rx_buffers (struct i40e_ring*,scalar_t__) ; 
 int /*<<< orphan*/  i40evf_process_skb_fields (struct i40e_ring*,union i40e_rx_desc*,struct sk_buff*,int) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ ring_uses_build_skb (struct i40e_ring*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40e_clean_rx_irq(struct i40e_ring *rx_ring, int budget)
{
	unsigned int total_rx_bytes = 0, total_rx_packets = 0;
	struct sk_buff *skb = rx_ring->skb;
	u16 cleaned_count = I40E_DESC_UNUSED(rx_ring);
	bool failure = false;

	while (likely(total_rx_packets < (unsigned int)budget)) {
		struct i40e_rx_buffer *rx_buffer;
		union i40e_rx_desc *rx_desc;
		unsigned int size;
		u16 vlan_tag;
		u8 rx_ptype;
		u64 qword;

		/* return some buffers to hardware, one at a time is too slow */
		if (cleaned_count >= I40E_RX_BUFFER_WRITE) {
			failure = failure ||
				  i40evf_alloc_rx_buffers(rx_ring, cleaned_count);
			cleaned_count = 0;
		}

		rx_desc = I40E_RX_DESC(rx_ring, rx_ring->next_to_clean);

		/* status_error_len will always be zero for unused descriptors
		 * because it's cleared in cleanup, and overlaps with hdr_addr
		 * which is always zero because packet split isn't used, if the
		 * hardware wrote DD then the length will be non-zero
		 */
		qword = le64_to_cpu(rx_desc->wb.qword1.status_error_len);

		/* This memory barrier is needed to keep us from reading
		 * any other fields out of the rx_desc until we have
		 * verified the descriptor has been written back.
		 */
		dma_rmb();

		size = (qword & I40E_RXD_QW1_LENGTH_PBUF_MASK) >>
		       I40E_RXD_QW1_LENGTH_PBUF_SHIFT;
		if (!size)
			break;

		i40e_trace(clean_rx_irq, rx_ring, rx_desc, skb);
		rx_buffer = i40e_get_rx_buffer(rx_ring, size);

		/* retrieve a buffer from the ring */
		if (skb)
			i40e_add_rx_frag(rx_ring, rx_buffer, skb, size);
		else if (ring_uses_build_skb(rx_ring))
			skb = i40e_build_skb(rx_ring, rx_buffer, size);
		else
			skb = i40e_construct_skb(rx_ring, rx_buffer, size);

		/* exit if we failed to retrieve a buffer */
		if (!skb) {
			rx_ring->rx_stats.alloc_buff_failed++;
			rx_buffer->pagecnt_bias++;
			break;
		}

		i40e_put_rx_buffer(rx_ring, rx_buffer);
		cleaned_count++;

		if (i40e_is_non_eop(rx_ring, rx_desc, skb))
			continue;

		/* ERR_MASK will only have valid bits if EOP set, and
		 * what we are doing here is actually checking
		 * I40E_RX_DESC_ERROR_RXE_SHIFT, since it is the zeroth bit in
		 * the error field
		 */
		if (unlikely(i40e_test_staterr(rx_desc, BIT(I40E_RXD_QW1_ERROR_SHIFT)))) {
			dev_kfree_skb_any(skb);
			skb = NULL;
			continue;
		}

		if (i40e_cleanup_headers(rx_ring, skb)) {
			skb = NULL;
			continue;
		}

		/* probably a little skewed due to removing CRC */
		total_rx_bytes += skb->len;

		qword = le64_to_cpu(rx_desc->wb.qword1.status_error_len);
		rx_ptype = (qword & I40E_RXD_QW1_PTYPE_MASK) >>
			   I40E_RXD_QW1_PTYPE_SHIFT;

		/* populate checksum, VLAN, and protocol */
		i40evf_process_skb_fields(rx_ring, rx_desc, skb, rx_ptype);


		vlan_tag = (qword & BIT(I40E_RX_DESC_STATUS_L2TAG1P_SHIFT)) ?
			   le16_to_cpu(rx_desc->wb.qword0.lo_dword.l2tag1) : 0;

		i40e_trace(clean_rx_irq_rx, rx_ring, rx_desc, skb);
		i40e_receive_skb(rx_ring, skb, vlan_tag);
		skb = NULL;

		/* update budget accounting */
		total_rx_packets++;
	}

	rx_ring->skb = skb;

	u64_stats_update_begin(&rx_ring->syncp);
	rx_ring->stats.packets += total_rx_packets;
	rx_ring->stats.bytes += total_rx_bytes;
	u64_stats_update_end(&rx_ring->syncp);
	rx_ring->q_vector->rx.total_packets += total_rx_packets;
	rx_ring->q_vector->rx.total_bytes += total_rx_bytes;

	/* guarantee a trip back through this routine if there was a failure */
	return failure ? budget : (int)total_rx_packets;
}