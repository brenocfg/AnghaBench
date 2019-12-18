#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  status_error_len; } ;
struct TYPE_6__ {TYPE_1__ qword1; } ;
union i40e_rx_desc {TYPE_2__ wb; } ;
typedef  unsigned int u64 ;
typedef  scalar_t__ u16 ;
struct xdp_buff {scalar_t__ data; scalar_t__ data_end; scalar_t__ data_hard_start; scalar_t__ data_meta; int /*<<< orphan*/ * rxq; } ;
struct sk_buff {scalar_t__ len; } ;
struct i40e_rx_buffer {int /*<<< orphan*/  pagecnt_bias; scalar_t__ page_offset; int /*<<< orphan*/  page; } ;
struct TYPE_7__ {int /*<<< orphan*/  alloc_buff_failed; } ;
struct i40e_ring {struct sk_buff* skb; TYPE_4__* q_vector; TYPE_3__ rx_stats; int /*<<< orphan*/  next_to_clean; int /*<<< orphan*/  xdp_rxq; } ;
struct TYPE_8__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 scalar_t__ I40E_DESC_UNUSED (struct i40e_ring*) ; 
 unsigned int I40E_RXD_QW1_LENGTH_PBUF_MASK ; 
 unsigned int I40E_RXD_QW1_LENGTH_PBUF_SHIFT ; 
 scalar_t__ I40E_RX_BUFFER_WRITE ; 
 union i40e_rx_desc* I40E_RX_DESC (struct i40e_ring*,int /*<<< orphan*/ ) ; 
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
 struct i40e_rx_buffer* i40e_clean_programming_status (struct i40e_ring*,union i40e_rx_desc*,unsigned int) ; 
 scalar_t__ i40e_cleanup_headers (struct i40e_ring*,struct sk_buff*,union i40e_rx_desc*) ; 
 struct sk_buff* i40e_construct_skb (struct i40e_ring*,struct i40e_rx_buffer*,struct xdp_buff*) ; 
 int /*<<< orphan*/  i40e_finalize_xdp_rx (struct i40e_ring*,unsigned int) ; 
 struct i40e_rx_buffer* i40e_get_rx_buffer (struct i40e_ring*,unsigned int) ; 
 scalar_t__ i40e_is_non_eop (struct i40e_ring*,union i40e_rx_desc*,struct sk_buff*) ; 
 int /*<<< orphan*/  i40e_process_skb_fields (struct i40e_ring*,union i40e_rx_desc*,struct sk_buff*) ; 
 int /*<<< orphan*/  i40e_put_rx_buffer (struct i40e_ring*,struct i40e_rx_buffer*) ; 
 int /*<<< orphan*/  i40e_reuse_rx_page (struct i40e_ring*,struct i40e_rx_buffer*) ; 
 struct sk_buff* i40e_run_xdp (struct i40e_ring*,struct xdp_buff*) ; 
 int /*<<< orphan*/  i40e_rx_buffer_flip (struct i40e_ring*,struct i40e_rx_buffer*,unsigned int) ; 
 scalar_t__ i40e_rx_offset (struct i40e_ring*) ; 
 int /*<<< orphan*/  i40e_trace (int /*<<< orphan*/ ,struct i40e_ring*,union i40e_rx_desc*,struct sk_buff*) ; 
 int /*<<< orphan*/  i40e_update_rx_stats (struct i40e_ring*,unsigned int,unsigned int) ; 
 unsigned int le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ page_address (int /*<<< orphan*/ ) ; 
 scalar_t__ ring_uses_build_skb (struct i40e_ring*) ; 
 scalar_t__ unlikely (struct i40e_rx_buffer*) ; 

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

		rx_buffer = i40e_clean_programming_status(rx_ring, rx_desc,
							  qword);
		if (unlikely(rx_buffer)) {
			i40e_reuse_rx_page(rx_ring, rx_buffer);
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

		/* populate checksum, VLAN, and protocol */
		i40e_process_skb_fields(rx_ring, rx_desc, skb);

		i40e_trace(clean_rx_irq_rx, rx_ring, rx_desc, skb);
		napi_gro_receive(&rx_ring->q_vector->napi, skb);
		skb = NULL;

		/* update budget accounting */
		total_rx_packets++;
	}

	i40e_finalize_xdp_rx(rx_ring, xdp_xmit);
	rx_ring->skb = skb;

	i40e_update_rx_stats(rx_ring, total_rx_bytes, total_rx_packets);

	/* guarantee a trip back through this routine if there was a failure */
	return failure ? budget : (int)total_rx_packets;
}