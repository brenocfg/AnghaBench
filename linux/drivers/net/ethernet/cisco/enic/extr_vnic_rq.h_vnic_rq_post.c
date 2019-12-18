#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct vnic_rq_buf {unsigned int os_buf_index; unsigned int len; int index; struct vnic_rq_buf* next; int /*<<< orphan*/  wr_id; int /*<<< orphan*/  dma_addr; void* os_buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  desc_avail; } ;
struct vnic_rq {TYPE_2__* ctrl; TYPE_1__ ring; struct vnic_rq_buf* to_use; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  posted_index; } ;

/* Variables and functions */
 int VNIC_RQ_RETURN_RATE ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void vnic_rq_post(struct vnic_rq *rq,
	void *os_buf, unsigned int os_buf_index,
	dma_addr_t dma_addr, unsigned int len,
	uint64_t wrid)
{
	struct vnic_rq_buf *buf = rq->to_use;

	buf->os_buf = os_buf;
	buf->os_buf_index = os_buf_index;
	buf->dma_addr = dma_addr;
	buf->len = len;
	buf->wr_id = wrid;

	buf = buf->next;
	rq->to_use = buf;
	rq->ring.desc_avail--;

	/* Move the posted_index every nth descriptor
	 */

#ifndef VNIC_RQ_RETURN_RATE
#define VNIC_RQ_RETURN_RATE		0xf	/* keep 2^n - 1 */
#endif

	if ((buf->index & VNIC_RQ_RETURN_RATE) == 0) {
		/* Adding write memory barrier prevents compiler and/or CPU
		 * reordering, thus avoiding descriptor posting before
		 * descriptor is initialized. Otherwise, hardware can read
		 * stale descriptor fields.
		 */
		wmb();
		iowrite32(buf->index, &rq->ctrl->posted_index);
	}
}