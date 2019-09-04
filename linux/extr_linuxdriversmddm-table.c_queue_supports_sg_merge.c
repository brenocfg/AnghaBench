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
struct request_queue {int /*<<< orphan*/  queue_flags; } ;
struct dm_target {int dummy; } ;
struct dm_dev {int /*<<< orphan*/  bdev; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_NO_SG_MERGE ; 
 struct request_queue* bdev_get_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int queue_supports_sg_merge(struct dm_target *ti, struct dm_dev *dev,
				   sector_t start, sector_t len, void *data)
{
	struct request_queue *q = bdev_get_queue(dev->bdev);

	return q && !test_bit(QUEUE_FLAG_NO_SG_MERGE, &q->queue_flags);
}