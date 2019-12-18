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
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct ena_rx_buffer {int /*<<< orphan*/  ena_buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  refil_partial; } ;
struct ena_ring {size_t next_to_use; size_t* free_ids; int /*<<< orphan*/  ena_com_io_sq; int /*<<< orphan*/  qid; int /*<<< orphan*/  netdev; int /*<<< orphan*/  syncp; TYPE_1__ rx_stats; int /*<<< orphan*/  ring_size; int /*<<< orphan*/  adapter; struct ena_rx_buffer* rx_buffer_info; } ;

/* Variables and functions */
 size_t ENA_RX_RING_IDX_NEXT (size_t,int /*<<< orphan*/ ) ; 
 int GFP_ATOMIC ; 
 int __GFP_COMP ; 
 int ena_alloc_rx_page (struct ena_ring*,struct ena_rx_buffer*,int) ; 
 int ena_com_add_single_rx_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ena_com_write_sq_doorbell (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (scalar_t__) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  netif_warn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_err ; 
 int /*<<< orphan*/  rx_status ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int validate_rx_req_id (struct ena_ring*,size_t) ; 

__attribute__((used)) static int ena_refill_rx_bufs(struct ena_ring *rx_ring, u32 num)
{
	u16 next_to_use, req_id;
	u32 i;
	int rc;

	next_to_use = rx_ring->next_to_use;

	for (i = 0; i < num; i++) {
		struct ena_rx_buffer *rx_info;

		req_id = rx_ring->free_ids[next_to_use];
		rc = validate_rx_req_id(rx_ring, req_id);
		if (unlikely(rc < 0))
			break;

		rx_info = &rx_ring->rx_buffer_info[req_id];


		rc = ena_alloc_rx_page(rx_ring, rx_info,
				       GFP_ATOMIC | __GFP_COMP);
		if (unlikely(rc < 0)) {
			netif_warn(rx_ring->adapter, rx_err, rx_ring->netdev,
				   "failed to alloc buffer for rx queue %d\n",
				   rx_ring->qid);
			break;
		}
		rc = ena_com_add_single_rx_desc(rx_ring->ena_com_io_sq,
						&rx_info->ena_buf,
						req_id);
		if (unlikely(rc)) {
			netif_warn(rx_ring->adapter, rx_status, rx_ring->netdev,
				   "failed to add buffer for rx queue %d\n",
				   rx_ring->qid);
			break;
		}
		next_to_use = ENA_RX_RING_IDX_NEXT(next_to_use,
						   rx_ring->ring_size);
	}

	if (unlikely(i < num)) {
		u64_stats_update_begin(&rx_ring->syncp);
		rx_ring->rx_stats.refil_partial++;
		u64_stats_update_end(&rx_ring->syncp);
		netdev_warn(rx_ring->netdev,
			    "refilled rx qid %d with only %d buffers (from %d)\n",
			    rx_ring->qid, i, num);
	}

	/* ena_com_write_sq_doorbell issues a wmb() */
	if (likely(i))
		ena_com_write_sq_doorbell(rx_ring->ena_com_io_sq);

	rx_ring->next_to_use = next_to_use;

	return i;
}