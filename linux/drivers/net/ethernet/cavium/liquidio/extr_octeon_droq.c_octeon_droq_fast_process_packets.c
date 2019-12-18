#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int len; } ;
union octeon_rh {TYPE_2__ r_dh; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct octeon_skb_page_info {int /*<<< orphan*/ * page; } ;
struct octeon_droq_info {scalar_t__ length; union octeon_rh rh; } ;
struct TYPE_10__ {int /*<<< orphan*/  dropped_toomany; int /*<<< orphan*/  bytes_received; int /*<<< orphan*/  pkts_received; int /*<<< orphan*/  rx_alloc_failure; } ;
struct TYPE_9__ {scalar_t__ drop_on_max; int /*<<< orphan*/  farg; int /*<<< orphan*/  (* fptr ) (int /*<<< orphan*/ ,struct sk_buff*,scalar_t__,union octeon_rh*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct octeon_droq {size_t read_idx; scalar_t__ refill_count; scalar_t__ buffer_size; scalar_t__ refill_threshold; int /*<<< orphan*/  pkts_pending; int /*<<< orphan*/  pkts_credit_reg; TYPE_5__ stats; TYPE_4__ ops; int /*<<< orphan*/  napi; int /*<<< orphan*/  max_count; TYPE_3__* recv_buf_list; int /*<<< orphan*/  q_no; } ;
struct octeon_device {int /*<<< orphan*/  octeon_id; TYPE_1__* pci_dev; } ;
struct TYPE_8__ {struct sk_buff* buffer; struct octeon_skb_page_info pg_info; scalar_t__ data; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CN23XX_SLI_DEF_BP ; 
 int /*<<< orphan*/  DUMP_PREFIX_ADDRESS ; 
 scalar_t__ OCTNET_FRM_LENGTH_SIZE ; 
 int /*<<< orphan*/  OCT_DROQ_INFO_SIZE ; 
 int ROUNDUP8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,scalar_t__) ; 
 void* incr_index (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_droq_check_hw_for_pkts (struct octeon_droq*) ; 
 scalar_t__ octeon_droq_dispatch_pkt (struct octeon_device*,struct octeon_droq*,union octeon_rh*,struct octeon_droq_info*) ; 
 int /*<<< orphan*/  octeon_droq_drop_packets (struct octeon_device*,struct octeon_droq*,scalar_t__) ; 
 int octeon_droq_refill (struct octeon_device*,struct octeon_droq*) ; 
 struct sk_buff* octeon_fast_packet_alloc (scalar_t__) ; 
 int /*<<< orphan*/  octeon_fast_packet_next (struct octeon_droq*,struct sk_buff*,int,int) ; 
 int /*<<< orphan*/  octeon_schedule_rxq_oom_work (struct octeon_device*,struct octeon_droq*) ; 
 int /*<<< orphan*/  octeon_swap_8B_data (int /*<<< orphan*/ *,int) ; 
 scalar_t__ opcode_slow_path (union octeon_rh*) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recv_buffer_fast_free (void*) ; 
 int /*<<< orphan*/  recv_buffer_free (struct sk_buff*) ; 
 scalar_t__ recv_buffer_recycle (struct octeon_device*,struct octeon_skb_page_info*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct sk_buff*,scalar_t__,union octeon_rh*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
octeon_droq_fast_process_packets(struct octeon_device *oct,
				 struct octeon_droq *droq,
				 u32 pkts_to_process)
{
	u32 pkt, total_len = 0, pkt_count, retval;
	struct octeon_droq_info *info;
	union octeon_rh *rh;

	pkt_count = pkts_to_process;

	for (pkt = 0; pkt < pkt_count; pkt++) {
		u32 pkt_len = 0;
		struct sk_buff *nicbuf = NULL;
		struct octeon_skb_page_info *pg_info;
		void *buf;

		info = (struct octeon_droq_info *)
			droq->recv_buf_list[droq->read_idx].data;
		octeon_swap_8B_data((u64 *)info, 2);

		if (!info->length) {
			dev_err(&oct->pci_dev->dev,
				"DROQ[%d] idx: %d len:0, pkt_cnt: %d\n",
				droq->q_no, droq->read_idx, pkt_count);
			print_hex_dump_bytes("", DUMP_PREFIX_ADDRESS,
					     (u8 *)info,
					     OCT_DROQ_INFO_SIZE);
			break;
		}

		/* Len of resp hdr in included in the received data len. */
		rh = &info->rh;

		info->length += OCTNET_FRM_LENGTH_SIZE;
		rh->r_dh.len += (ROUNDUP8(OCT_DROQ_INFO_SIZE) / sizeof(u64));
		total_len += (u32)info->length;
		if (opcode_slow_path(rh)) {
			u32 buf_cnt;

			buf_cnt = octeon_droq_dispatch_pkt(oct, droq, rh, info);
			droq->read_idx = incr_index(droq->read_idx,
						    buf_cnt, droq->max_count);
			droq->refill_count += buf_cnt;
		} else {
			if (info->length <= droq->buffer_size) {
				pkt_len = (u32)info->length;
				nicbuf = droq->recv_buf_list[
					droq->read_idx].buffer;
				pg_info = &droq->recv_buf_list[
					droq->read_idx].pg_info;
				if (recv_buffer_recycle(oct, pg_info))
					pg_info->page = NULL;
				droq->recv_buf_list[droq->read_idx].buffer =
					NULL;

				droq->read_idx = incr_index(droq->read_idx, 1,
							    droq->max_count);
				droq->refill_count++;
			} else {
				nicbuf = octeon_fast_packet_alloc((u32)
								  info->length);
				pkt_len = 0;
				/* nicbuf allocation can fail. We'll handle it
				 * inside the loop.
				 */
				while (pkt_len < info->length) {
					int cpy_len, idx = droq->read_idx;

					cpy_len = ((pkt_len + droq->buffer_size)
						   > info->length) ?
						((u32)info->length - pkt_len) :
						droq->buffer_size;

					if (nicbuf) {
						octeon_fast_packet_next(droq,
									nicbuf,
									cpy_len,
									idx);
						buf = droq->recv_buf_list[
							idx].buffer;
						recv_buffer_fast_free(buf);
						droq->recv_buf_list[idx].buffer
							= NULL;
					} else {
						droq->stats.rx_alloc_failure++;
					}

					pkt_len += cpy_len;
					droq->read_idx =
						incr_index(droq->read_idx, 1,
							   droq->max_count);
					droq->refill_count++;
				}
			}

			if (nicbuf) {
				if (droq->ops.fptr) {
					droq->ops.fptr(oct->octeon_id,
						       nicbuf, pkt_len,
						       rh, &droq->napi,
						       droq->ops.farg);
				} else {
					recv_buffer_free(nicbuf);
				}
			}
		}

		if (droq->refill_count >= droq->refill_threshold) {
			int desc_refilled = octeon_droq_refill(oct, droq);

			if (desc_refilled) {
				/* Flush the droq descriptor data to memory to
				 * be sure that when we update the credits the
				 * data in memory is accurate.
				 */
				wmb();
				writel(desc_refilled, droq->pkts_credit_reg);
			}
		}
	}                       /* for (each packet)... */

	/* Increment refill_count by the number of buffers processed. */
	droq->stats.pkts_received += pkt;
	droq->stats.bytes_received += total_len;

	retval = pkt;
	if ((droq->ops.drop_on_max) && (pkts_to_process - pkt)) {
		octeon_droq_drop_packets(oct, droq, (pkts_to_process - pkt));

		droq->stats.dropped_toomany += (pkts_to_process - pkt);
		retval = pkts_to_process;
	}

	atomic_sub(retval, &droq->pkts_pending);

	if (droq->refill_count >= droq->refill_threshold &&
	    readl(droq->pkts_credit_reg) < CN23XX_SLI_DEF_BP) {
		octeon_droq_check_hw_for_pkts(droq);

		/* Make sure there are no pkts_pending */
		if (!atomic_read(&droq->pkts_pending))
			octeon_schedule_rxq_oom_work(oct, droq);
	}

	return retval;
}