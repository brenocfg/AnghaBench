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
struct pool_c {TYPE_1__* data_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 struct request_queue* bdev_get_queue (int /*<<< orphan*/ ) ; 
 scalar_t__ blk_queue_discard (struct request_queue*) ; 

__attribute__((used)) static bool data_dev_supports_discard(struct pool_c *pt)
{
	struct request_queue *q = bdev_get_queue(pt->data_dev->bdev);

	return q && blk_queue_discard(q);
}