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
struct verify_rq_based_data {int /*<<< orphan*/  sq_count; int /*<<< orphan*/  mq_count; } ;
struct request_queue {int dummy; } ;
struct dm_target {int dummy; } ;
struct dm_dev {int /*<<< orphan*/  bdev; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 struct request_queue* bdev_get_queue (int /*<<< orphan*/ ) ; 
 int queue_is_mq (struct request_queue*) ; 

__attribute__((used)) static int device_is_rq_based(struct dm_target *ti, struct dm_dev *dev,
			      sector_t start, sector_t len, void *data)
{
	struct request_queue *q = bdev_get_queue(dev->bdev);
	struct verify_rq_based_data *v = data;

	if (queue_is_mq(q))
		v->mq_count++;
	else
		v->sq_count++;

	return queue_is_mq(q);
}