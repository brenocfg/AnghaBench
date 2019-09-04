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
typedef  void* u8 ;
typedef  size_t u32 ;
struct hidma_tre {size_t tre_index; scalar_t__ queued; void* err_code; void* err_info; } ;
struct hidma_lldev {size_t tre_processed_off; int /*<<< orphan*/  task; int /*<<< orphan*/  handoff_fifo; int /*<<< orphan*/  lock; int /*<<< orphan*/  tre_ring_size; int /*<<< orphan*/  pending_tre_count; int /*<<< orphan*/  dev; struct hidma_tre** pending_tre_list; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HIDMA_INCREMENT_ITERATOR (size_t,size_t,int /*<<< orphan*/ ) ; 
 size_t HIDMA_TRE_SIZE ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kfifo_put (int /*<<< orphan*/ *,struct hidma_tre*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hidma_post_completed(struct hidma_lldev *lldev, u8 err_info,
				u8 err_code)
{
	struct hidma_tre *tre;
	unsigned long flags;
	u32 tre_iterator;

	spin_lock_irqsave(&lldev->lock, flags);

	tre_iterator = lldev->tre_processed_off;
	tre = lldev->pending_tre_list[tre_iterator / HIDMA_TRE_SIZE];
	if (!tre) {
		spin_unlock_irqrestore(&lldev->lock, flags);
		dev_warn(lldev->dev, "tre_index [%d] and tre out of sync\n",
			 tre_iterator / HIDMA_TRE_SIZE);
		return -EINVAL;
	}
	lldev->pending_tre_list[tre->tre_index] = NULL;

	/*
	 * Keep track of pending TREs that SW is expecting to receive
	 * from HW. We got one now. Decrement our counter.
	 */
	if (atomic_dec_return(&lldev->pending_tre_count) < 0) {
		dev_warn(lldev->dev, "tre count mismatch on completion");
		atomic_set(&lldev->pending_tre_count, 0);
	}

	HIDMA_INCREMENT_ITERATOR(tre_iterator, HIDMA_TRE_SIZE,
				 lldev->tre_ring_size);
	lldev->tre_processed_off = tre_iterator;
	spin_unlock_irqrestore(&lldev->lock, flags);

	tre->err_info = err_info;
	tre->err_code = err_code;
	tre->queued = 0;

	kfifo_put(&lldev->handoff_fifo, tre);
	tasklet_schedule(&lldev->task);

	return 0;
}