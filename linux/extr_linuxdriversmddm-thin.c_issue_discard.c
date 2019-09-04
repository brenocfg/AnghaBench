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
struct thin_c {TYPE_1__* pool_dev; int /*<<< orphan*/  pool; } ;
struct discard_op {int /*<<< orphan*/  bio; struct thin_c* tc; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  scalar_t__ dm_block_t ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int __blkdev_issue_discard (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  block_to_sectors (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int issue_discard(struct discard_op *op, dm_block_t data_b, dm_block_t data_e)
{
	struct thin_c *tc = op->tc;
	sector_t s = block_to_sectors(tc->pool, data_b);
	sector_t len = block_to_sectors(tc->pool, data_e - data_b);

	return __blkdev_issue_discard(tc->pool_dev->bdev, s, len,
				      GFP_NOWAIT, 0, &op->bio);
}