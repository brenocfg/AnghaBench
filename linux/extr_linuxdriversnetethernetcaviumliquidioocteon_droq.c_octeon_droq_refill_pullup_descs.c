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
typedef  size_t u32 ;
struct octeon_droq_desc {scalar_t__ buffer_ptr; } ;
struct octeon_droq {size_t refill_idx; size_t read_idx; int /*<<< orphan*/  max_count; int /*<<< orphan*/  refill_count; TYPE_1__* recv_buf_list; } ;
struct TYPE_2__ {int /*<<< orphan*/ * buffer; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 void* incr_index (size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32
octeon_droq_refill_pullup_descs(struct octeon_droq *droq,
				struct octeon_droq_desc *desc_ring)
{
	u32 desc_refilled = 0;

	u32 refill_index = droq->refill_idx;

	while (refill_index != droq->read_idx) {
		if (droq->recv_buf_list[refill_index].buffer) {
			droq->recv_buf_list[droq->refill_idx].buffer =
				droq->recv_buf_list[refill_index].buffer;
			droq->recv_buf_list[droq->refill_idx].data =
				droq->recv_buf_list[refill_index].data;
			desc_ring[droq->refill_idx].buffer_ptr =
				desc_ring[refill_index].buffer_ptr;
			droq->recv_buf_list[refill_index].buffer = NULL;
			desc_ring[refill_index].buffer_ptr = 0;
			do {
				droq->refill_idx = incr_index(droq->refill_idx,
							      1,
							      droq->max_count);
				desc_refilled++;
				droq->refill_count--;
			} while (droq->recv_buf_list[droq->refill_idx].buffer);
		}
		refill_index = incr_index(refill_index, 1, droq->max_count);
	}                       /* while */
	return desc_refilled;
}