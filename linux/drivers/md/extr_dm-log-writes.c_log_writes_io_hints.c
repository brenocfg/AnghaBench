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
struct request_queue {int dummy; } ;
struct queue_limits {int max_discard_sectors; int /*<<< orphan*/  physical_block_size; int /*<<< orphan*/  io_min; int /*<<< orphan*/  logical_block_size; int /*<<< orphan*/  discard_granularity; } ;
struct log_writes_c {int device_supports_discard; TYPE_1__* dev; int /*<<< orphan*/  sectorsize; } ;
struct dm_target {struct log_writes_c* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int SECTOR_SHIFT ; 
 int UINT_MAX ; 
 struct request_queue* bdev_get_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdev_logical_block_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdev_physical_block_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_discard (struct request_queue*) ; 

__attribute__((used)) static void log_writes_io_hints(struct dm_target *ti, struct queue_limits *limits)
{
	struct log_writes_c *lc = ti->private;
	struct request_queue *q = bdev_get_queue(lc->dev->bdev);

	if (!q || !blk_queue_discard(q)) {
		lc->device_supports_discard = false;
		limits->discard_granularity = lc->sectorsize;
		limits->max_discard_sectors = (UINT_MAX >> SECTOR_SHIFT);
	}
	limits->logical_block_size = bdev_logical_block_size(lc->dev->bdev);
	limits->physical_block_size = bdev_physical_block_size(lc->dev->bdev);
	limits->io_min = limits->physical_block_size;
}