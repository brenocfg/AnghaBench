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
struct mei_device {int /*<<< orphan*/  dev; } ;
struct hbm_dma_ring_ctrl {scalar_t__ hbuf_wr_idx; } ;

/* Variables and functions */
 int READ_ONCE (scalar_t__) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int mei_data2slots (int) ; 
 int /*<<< orphan*/  mei_dma_copy_to (struct mei_device*,unsigned char*,int,int) ; 
 struct hbm_dma_ring_ctrl* mei_dma_ring_ctrl (struct mei_device*) ; 
 int mei_dma_ring_hbuf_depth (struct mei_device*) ; 

void mei_dma_ring_write(struct mei_device *dev, unsigned char *buf, u32 len)
{
	struct hbm_dma_ring_ctrl *ctrl = mei_dma_ring_ctrl(dev);
	u32 hbuf_depth;
	u32 wr_idx, rem, slots;

	if (WARN_ON(!ctrl))
		return;

	dev_dbg(dev->dev, "writing to dma %u bytes\n", len);
	hbuf_depth = mei_dma_ring_hbuf_depth(dev);
	wr_idx = READ_ONCE(ctrl->hbuf_wr_idx) & (hbuf_depth - 1);
	slots = mei_data2slots(len);

	if (wr_idx + slots > hbuf_depth) {
		buf += mei_dma_copy_to(dev, buf, wr_idx, hbuf_depth - wr_idx);
		rem = slots - (hbuf_depth - wr_idx);
		wr_idx = 0;
	} else {
		rem = slots;
	}

	mei_dma_copy_to(dev, buf, wr_idx, rem);

	WRITE_ONCE(ctrl->hbuf_wr_idx, ctrl->hbuf_wr_idx + slots);
}