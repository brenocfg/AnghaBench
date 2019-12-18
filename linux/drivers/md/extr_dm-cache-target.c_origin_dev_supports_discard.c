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
struct request_queue {int dummy; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 struct request_queue* bdev_get_queue (struct block_device*) ; 
 scalar_t__ blk_queue_discard (struct request_queue*) ; 

__attribute__((used)) static bool origin_dev_supports_discard(struct block_device *origin_bdev)
{
	struct request_queue *q = bdev_get_queue(origin_bdev);

	return q && blk_queue_discard(q);
}