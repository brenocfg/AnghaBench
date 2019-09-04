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
typedef  int u32 ;
struct flexrm_ring {int bd_write_offset; void* bd_base; int /*<<< orphan*/  lock; int /*<<< orphan*/  requests_bmap; struct brcm_message** requests; TYPE_1__* mbox; int /*<<< orphan*/  msg_send_count; scalar_t__ bd_dma_base; scalar_t__ regs; } ;
struct brcm_message {int error; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BD_START_ADDR_DECODE (int) ; 
 int EIO ; 
 int ENOSPC ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 scalar_t__ RING_BD_READ_PTR ; 
 int RING_BD_SIZE ; 
 scalar_t__ RING_BD_START_ADDR ; 
 int /*<<< orphan*/  RING_BD_TOGGLE_VALID (long) ; 
 int RING_DESC_SIZE ; 
 int /*<<< orphan*/  RING_MAX_REQ_COUNT ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int bitmap_find_free_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_release_region (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int flexrm_dma_map (int /*<<< orphan*/ ,struct brcm_message*) ; 
 int /*<<< orphan*/  flexrm_dma_unmap (int /*<<< orphan*/ ,struct brcm_message*) ; 
 int flexrm_estimate_header_desc_count (int) ; 
 int flexrm_estimate_nonheader_desc_count (struct brcm_message*) ; 
 int /*<<< orphan*/  flexrm_is_next_table_desc (void*) ; 
 int /*<<< orphan*/  flexrm_sanity_check (struct brcm_message*) ; 
 void* flexrm_write_descs (struct brcm_message*,int,int,void*,int /*<<< orphan*/ ,void*,void*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int flexrm_new_request(struct flexrm_ring *ring,
				struct brcm_message *batch_msg,
				struct brcm_message *msg)
{
	void *next;
	unsigned long flags;
	u32 val, count, nhcnt;
	u32 read_offset, write_offset;
	bool exit_cleanup = false;
	int ret = 0, reqid;

	/* Do sanity check on message */
	if (!flexrm_sanity_check(msg))
		return -EIO;
	msg->error = 0;

	/* If no requests possible then save data pointer and goto done. */
	spin_lock_irqsave(&ring->lock, flags);
	reqid = bitmap_find_free_region(ring->requests_bmap,
					RING_MAX_REQ_COUNT, 0);
	spin_unlock_irqrestore(&ring->lock, flags);
	if (reqid < 0)
		return -ENOSPC;
	ring->requests[reqid] = msg;

	/* Do DMA mappings for the message */
	ret = flexrm_dma_map(ring->mbox->dev, msg);
	if (ret < 0) {
		ring->requests[reqid] = NULL;
		spin_lock_irqsave(&ring->lock, flags);
		bitmap_release_region(ring->requests_bmap, reqid, 0);
		spin_unlock_irqrestore(&ring->lock, flags);
		return ret;
	}

	/* Determine current HW BD read offset */
	read_offset = readl_relaxed(ring->regs + RING_BD_READ_PTR);
	val = readl_relaxed(ring->regs + RING_BD_START_ADDR);
	read_offset *= RING_DESC_SIZE;
	read_offset += (u32)(BD_START_ADDR_DECODE(val) - ring->bd_dma_base);

	/*
	 * Number required descriptors = number of non-header descriptors +
	 *				 number of header descriptors +
	 *				 1x null descriptor
	 */
	nhcnt = flexrm_estimate_nonheader_desc_count(msg);
	count = flexrm_estimate_header_desc_count(nhcnt) + nhcnt + 1;

	/* Check for available descriptor space. */
	write_offset = ring->bd_write_offset;
	while (count) {
		if (!flexrm_is_next_table_desc(ring->bd_base + write_offset))
			count--;
		write_offset += RING_DESC_SIZE;
		if (write_offset == RING_BD_SIZE)
			write_offset = 0x0;
		if (write_offset == read_offset)
			break;
	}
	if (count) {
		ret = -ENOSPC;
		exit_cleanup = true;
		goto exit;
	}

	/* Write descriptors to ring */
	next = flexrm_write_descs(msg, nhcnt, reqid,
			ring->bd_base + ring->bd_write_offset,
			RING_BD_TOGGLE_VALID(ring->bd_write_offset),
			ring->bd_base, ring->bd_base + RING_BD_SIZE);
	if (IS_ERR(next)) {
		ret = PTR_ERR(next);
		exit_cleanup = true;
		goto exit;
	}

	/* Save ring BD write offset */
	ring->bd_write_offset = (unsigned long)(next - ring->bd_base);

	/* Increment number of messages sent */
	atomic_inc_return(&ring->msg_send_count);

exit:
	/* Update error status in message */
	msg->error = ret;

	/* Cleanup if we failed */
	if (exit_cleanup) {
		flexrm_dma_unmap(ring->mbox->dev, msg);
		ring->requests[reqid] = NULL;
		spin_lock_irqsave(&ring->lock, flags);
		bitmap_release_region(ring->requests_bmap, reqid, 0);
		spin_unlock_irqrestore(&ring->lock, flags);
	}

	return ret;
}