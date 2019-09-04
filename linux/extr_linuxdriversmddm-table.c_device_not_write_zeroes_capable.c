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
struct TYPE_2__ {int /*<<< orphan*/  max_write_zeroes_sectors; } ;
struct request_queue {TYPE_1__ limits; } ;
struct dm_target {int dummy; } ;
struct dm_dev {int /*<<< orphan*/  bdev; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 struct request_queue* bdev_get_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int device_not_write_zeroes_capable(struct dm_target *ti, struct dm_dev *dev,
					   sector_t start, sector_t len, void *data)
{
	struct request_queue *q = bdev_get_queue(dev->bdev);

	return q && !q->limits.max_write_zeroes_sectors;
}