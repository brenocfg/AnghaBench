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
struct qlcnic_rx_buffer {int /*<<< orphan*/  list; } ;
struct qlcnic_recv_context {struct qlcnic_host_rds_ring* rds_rings; } ;
struct qlcnic_host_rds_ring {int num_desc; int /*<<< orphan*/  free_list; struct qlcnic_rx_buffer* rx_buf_arr; } ;
struct qlcnic_adapter {int max_rds_rings; struct qlcnic_recv_context* recv_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void qlcnic_reset_rx_buffers_list(struct qlcnic_adapter *adapter)
{
	struct qlcnic_recv_context *recv_ctx;
	struct qlcnic_host_rds_ring *rds_ring;
	struct qlcnic_rx_buffer *rx_buf;
	int i, ring;

	recv_ctx = adapter->recv_ctx;
	for (ring = 0; ring < adapter->max_rds_rings; ring++) {
		rds_ring = &recv_ctx->rds_rings[ring];

		INIT_LIST_HEAD(&rds_ring->free_list);

		rx_buf = rds_ring->rx_buf_arr;
		for (i = 0; i < rds_ring->num_desc; i++) {
			list_add_tail(&rx_buf->list,
					&rds_ring->free_list);
			rx_buf++;
		}
	}
}