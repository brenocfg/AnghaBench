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
typedef  int u32 ;
typedef  int u16 ;
struct ena_eth_io_rx_cdesc_base {int /*<<< orphan*/  status; } ;
struct ena_com_io_cq {int cur_rx_pkt_cdesc_start_idx; int cur_rx_pkt_cdesc_count; int head; int q_depth; int /*<<< orphan*/  qid; } ;

/* Variables and functions */
 int ENA_ETH_IO_RX_CDESC_BASE_LAST_MASK ; 
 int ENA_ETH_IO_RX_CDESC_BASE_LAST_SHIFT ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_com_cq_inc_head (struct ena_com_io_cq*) ; 
 struct ena_eth_io_rx_cdesc_base* ena_com_get_next_rx_cdesc (struct ena_com_io_cq*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static u16 ena_com_cdesc_rx_pkt_get(struct ena_com_io_cq *io_cq,
					   u16 *first_cdesc_idx)
{
	struct ena_eth_io_rx_cdesc_base *cdesc;
	u16 count = 0, head_masked;
	u32 last = 0;

	do {
		cdesc = ena_com_get_next_rx_cdesc(io_cq);
		if (!cdesc)
			break;

		ena_com_cq_inc_head(io_cq);
		count++;
		last = (READ_ONCE(cdesc->status) & ENA_ETH_IO_RX_CDESC_BASE_LAST_MASK) >>
			ENA_ETH_IO_RX_CDESC_BASE_LAST_SHIFT;
	} while (!last);

	if (last) {
		*first_cdesc_idx = io_cq->cur_rx_pkt_cdesc_start_idx;
		count += io_cq->cur_rx_pkt_cdesc_count;

		head_masked = io_cq->head & (io_cq->q_depth - 1);

		io_cq->cur_rx_pkt_cdesc_count = 0;
		io_cq->cur_rx_pkt_cdesc_start_idx = head_masked;

		pr_debug("ena q_id: %d packets were completed. first desc idx %u descs# %d\n",
			 io_cq->qid, *first_cdesc_idx, count);
	} else {
		io_cq->cur_rx_pkt_cdesc_count += count;
		count = 0;
	}

	return count;
}