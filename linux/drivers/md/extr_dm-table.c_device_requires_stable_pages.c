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
struct request_queue {int /*<<< orphan*/  backing_dev_info; } ;
struct dm_target {int dummy; } ;
struct dm_dev {int /*<<< orphan*/  bdev; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 struct request_queue* bdev_get_queue (int /*<<< orphan*/ ) ; 
 scalar_t__ bdi_cap_stable_pages_required (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int device_requires_stable_pages(struct dm_target *ti,
					struct dm_dev *dev, sector_t start,
					sector_t len, void *data)
{
	struct request_queue *q = bdev_get_queue(dev->bdev);

	return q && bdi_cap_stable_pages_required(q->backing_dev_info);
}