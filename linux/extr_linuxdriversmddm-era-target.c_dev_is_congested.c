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
struct dm_dev {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 struct request_queue* bdev_get_queue (int /*<<< orphan*/ ) ; 
 int bdi_congested (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dev_is_congested(struct dm_dev *dev, int bdi_bits)
{
	struct request_queue *q = bdev_get_queue(dev->bdev);
	return bdi_congested(q->backing_dev_info, bdi_bits);
}