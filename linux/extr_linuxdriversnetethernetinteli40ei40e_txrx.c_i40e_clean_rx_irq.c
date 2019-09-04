#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  l2tag1; } ;
struct TYPE_13__ {TYPE_3__ lo_dword; } ;
struct TYPE_11__ {int /*<<< orphan*/  status_error_len; } ;
struct TYPE_14__ {TYPE_4__ qword0; TYPE_2__ qword1; } ;
union i40e_rx_desc {TYPE_5__ wb; } ;
typedef  int u8 ;
typedef  int u64 ;
typedef  scalar_t__ u16 ;
struct xdp_buff {scalar_t__ data; scalar_t__ data_end; scalar_t__ data_hard_start; scalar_t__ data_meta; int /*<<< orphan*/ * rxq; } ;
struct sk_buff {scalar_t__ len; } ;
struct i40e_rx_buffer {int /*<<< orphan*/  pagecnt_bias; scalar_t__ page_offset; int /*<<< orphan*/  page; } ;
struct TYPE_16__ {unsigned int packets; unsigned int bytes; } ;
struct TYPE_10__ {int /*<<< orphan*/  alloc_buff_failed; } ;
struct i40e_ring {size_t queue_index; TYPE_9__* q_vector; int /*<<< orphan*/  syncp; TYPE_7__ stats; struct sk_buff* skb; TYPE_6__* vsi; TYPE_1__ rx_stats; int /*<<< orphan*/  next_to_clean; int /*<<< orphan*/  xdp_rxq; } ;
struct TYPE_17__ {unsigned int total_packets; unsigned int total_bytes; } ;
struct TYPE_18__ {TYPE_8__ rx; } ;
struct TYPE_15__ {struct i40e_ring** xdp_rings; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ I40E_DESC_UNUSED (struct i40e_ring*) ; 
 int I40E_RXD_QW1_LENGTH_PBUF_MASK ; 
 int I40E_RXD_QW1_LENGTH_PBUF_SHIFT ; 
 int I40E_RXD_QW1_PTYPE_MASK ; 
 int I40E_RXD_QW1_PTYPE_SHIFT ; 
 scalar_t__ I40E_RX_BUFFER_WRITE ; 
 union i40e_rx_desc* I40E_RX_DESC (struct i40e_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_RX_DESC_STATUS_L2TAG1P_SHIFT ; 
 unsigned int I40E_XDP_REDIR ; 
 unsigned int I40E_XDP_TX ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 unsigned int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  clean_rx_irq ; 
 int /*<<< orphan*/  clean_rx_irq_rx ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  i40e_add_rx_frag (struct i40e_ring*,struct i40e_rx_buffer*,struct sk_buff*,unsigned int) ; 
 scalar_t__ i40e_alloc_rx_buffers (struct i40e_ring*,scalar_t__) ; 
 struct sk_buff* i40e_build_skb (struct i40e_ring*,struct i40e_rx_buffer*,struct xdp_buff*) ; 
 int /*<<< orphan*/  i40e_clean_programming_status (struct i40e_ring*,union i40e_rx_desc*,int) ; 
 scalar_t__ i40e_cleanup_headers (struct i40e_ring*,struct sk_buff*,union i40e_rx_desc*) ; 
 struct sk_buff* i40e_construct_skb (struct i40e_ring*,struct i40e_rx_buffer*,struct xdp_buff*) ; 
 struct i40e_rx_buffer* i40e_get_rx_buffer (struct i40e_ring*,unsigned int) ; 
 scalar_t__ i40e_is_non_eop (struct i40e_ring*,union i40e_rx_desc*,struct sk_buff*) ; 
 int /*<<< orphan*/  i40e_process_skb_fields (struct i40e_ring*,union i40e_rx_desc*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  i40e_put_rx_buffer (struct i40e_ring*,struct i40e_rx_buffer*) ; 
 int /*<<< orphan*/  i40e_receive_skb (struct i40e_ring*,struct sk_buff*,scalar_t__) ; 
 struct sk_buff* i40e_run_xdp (struct i40e_ring*,struct xdp_buff*) ; 
 int /*<<< orphan*/  i40e_rx_buffer_flip (struct i40e_ring*,struct i40e_rx_buffer*,unsigned int) ; 
 int /*<<< orphan*/  i40e_rx_is_programming_status (int) ; 
 scalar_t__ i40e_rx_offset (struct i40e_ring*) ; 
 int /*<<< orphan*/  i40e_trace (int /*<<< orphan*/ ,struct i40e_ring*,union i40e_rx_desc*,struct sk_buff*) ; 
 int /*<<< orphan*/  i40e_xdp_ring_update_tail (struct i40e_ring*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ page_address (int /*<<< orphan*/ ) ; 
 scalar_t__ ring_uses_build_skb (struct i40e_ring*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdp_do_flush_map () ; 

__attribute__((used)) static int i40e_clean_rx_irq(struct i40e_ring *rx_ring, int budget)
{
	unsigned int total_rx_bytes = 0, total_rx_packets = 0;
	struct sk_buff *skb = rx_ring->skb;
	u16 cleaned_count = I40E_DESC_UNUSED(rx_ring);
	unsigned int xdp_xmit = 0;
	bool failure = false;
	struct xdp_buff xdp;

	xdp.rxq = &rx_ring->xdp_rxq;

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
				  i40e_alloc_rx_buffers(rx_ring, cleaned_count);
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

		if (unlikely(i40e_rx_is_programming_status(qword))) {
			i40e_clean_programming_status(rx_ring, rx_desc, qword);
			cleaned_count++;
			continue;
		}
		size = (qword & I40E_RXD_QW1_LENGTH_PBUF_MASK) >>
		       I40E_RXD_QW1_LENGTH_PBUF_SHIFT;
		if (!size)
			break;

		i40e_trace(clean_rx_irq, rx_ring, rx_desc, skb);
		rx_buffer = i40e_get_rx_buffer(rx_ring, size);

		/* retrieve a buffer from the ring */
		if (!skb) {
			xdp.data = page_address(rx_buffer->page) +
				   rx_buffer->page_offset;
			xdp.data_meta = xdp.data;
			xdp.data_hard_start = xdp.data -
					      i40e_rx_offset(rx_ring);
			xdp.data_end = xdp.data + size;

			skb = i40e_run_xdp(rx_ring, &xdp);
		}

		if (IS_ERR(skb)) {
			unsigned int xdp_res = -PTR_ERR(skb);

			if (xdp_res & (I40E_XDP_TX | I40E_XDP_REDIR)) {
				xdp_xmit |= xdp_res;
				i40e_rx_buffer_flip(rx_ring, rx_buffer, size);
			} else {
				rx_buffer->pagecnt_bias++;
			}
			total_rx_bytes += size;
			total_rx_packets++;
		} else if (skb) {
			i40e_add_rx_frag(rx_ring, rx_buffer, skb, size);
		} else if (ring_uses_build_skb(rx_ring)) {
			skb = i40e_build_skb(rx_ring, rx_buffer, &xdp);
		} else {
			skb = i40e_construct_skb(rx_ring, rx_buffer, &xdp);
		}

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

		if (i40e_cleanup_headers(rx_ring, skb, rx_desc)) {
			skb = NULL;
			continue;
		}

		/* probably a little skewed due to removing CRC */
		total_rx_bytes += skb->len;

		qword = le64_to_cpu(rx_desc->wb.qword1.status_error_len);
		rx_ptype = (qword & I40E_RXD_QW1_PTYPE_MASK) >>
			   I40E_RXD_QW1_PTYPE_SHIFT;

		/* populate checksum, VLAN, and protocol */
		i40e_process_skb_fields(rx_ring, rx_desc, skb, rx_ptype);

		vlan_tag = (qword & BIT(I40E_RX_DESC_STATUS_L2TAG1P_SHIFT)) ?
			   le16_to_cpu(rx_desc->wb.qword0.lo_dword.l2tag1) : 0;

		i40e_trace(clean_rx_irq_rx, rx_ring, rx_desc, skb);
		i40e_receive_skb(rx_ring, skb, vlan_tag);
		skb = NULL;

		/* update budget accounting */
		total_rx_packets++;
	}

	if (xdp_xmit & I40E_XDP_REDIR)
		xdp_do_flush_map();

	if (xdp_xmit & I40E_XDP_TX) {
		struct i40e_ring *xdp_ring =
			rx_ring->vsi->xdp_rings[rx_ring->queue_index];

		i40e_xdp_ring_update_tail(xdp_ring);
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