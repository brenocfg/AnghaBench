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
typedef  scalar_t__ u32 ;
struct mei_device {int dummy; } ;
struct hbm_dma_ring_ctrl {int /*<<< orphan*/  hbuf_wr_idx; int /*<<< orphan*/  hbuf_rd_idx; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 struct hbm_dma_ring_ctrl* mei_dma_ring_ctrl (struct mei_device*) ; 
 scalar_t__ mei_dma_ring_hbuf_depth (struct mei_device*) ; 
 int /*<<< orphan*/  mei_dma_ring_is_allocated (struct mei_device*) ; 

u32 mei_dma_ring_empty_slots(struct mei_device *dev)
{
	struct hbm_dma_ring_ctrl *ctrl = mei_dma_ring_ctrl(dev);
	u32 wr_idx, rd_idx, hbuf_depth, empty;

	if (!mei_dma_ring_is_allocated(dev))
		return 0;

	if (WARN_ON(!ctrl))
		return 0;

	/* easier to work in slots */
	hbuf_depth = mei_dma_ring_hbuf_depth(dev);
	rd_idx = READ_ONCE(ctrl->hbuf_rd_idx);
	wr_idx = READ_ONCE(ctrl->hbuf_wr_idx);

	if (rd_idx > wr_idx)
		empty = rd_idx - wr_idx;
	else
		empty = hbuf_depth - (wr_idx - rd_idx);

	return empty;
}