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
struct md_rdev {int /*<<< orphan*/  flags; int /*<<< orphan*/  wb_io_wait; int /*<<< orphan*/  wb_list; int /*<<< orphan*/  wb_list_lock; TYPE_2__* bdev; } ;
struct TYPE_4__ {TYPE_1__* bd_queue; } ;
struct TYPE_3__ {int nr_hw_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WBCollisionCheck ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rdev_init_wb(struct md_rdev *rdev)
{
	if (rdev->bdev->bd_queue->nr_hw_queues == 1)
		return 0;

	spin_lock_init(&rdev->wb_list_lock);
	INIT_LIST_HEAD(&rdev->wb_list);
	init_waitqueue_head(&rdev->wb_io_wait);
	set_bit(WBCollisionCheck, &rdev->flags);

	return 1;
}