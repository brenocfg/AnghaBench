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
struct timer_list {int dummy; } ;
struct dasd_block {int /*<<< orphan*/  request_queue; TYPE_1__* base; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_STOPPED_PENDING ; 
 int /*<<< orphan*/  blk_mq_run_hw_queues (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dasd_device_remove_stop_bits (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_schedule_block_bh (struct dasd_block*) ; 
 struct dasd_block* from_timer (struct dasd_block*,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void dasd_block_timeout(struct timer_list *t)
{
	unsigned long flags;
	struct dasd_block *block;

	block = from_timer(block, t, timer);
	spin_lock_irqsave(get_ccwdev_lock(block->base->cdev), flags);
	/* re-activate request queue */
	dasd_device_remove_stop_bits(block->base, DASD_STOPPED_PENDING);
	spin_unlock_irqrestore(get_ccwdev_lock(block->base->cdev), flags);
	dasd_schedule_block_bh(block);
	blk_mq_run_hw_queues(block->request_queue, true);
}