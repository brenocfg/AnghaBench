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
struct request_queue {int /*<<< orphan*/  sysfs_lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int __blk_mq_register_dev (struct device*,struct request_queue*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int blk_mq_register_dev(struct device *dev, struct request_queue *q)
{
	int ret;

	mutex_lock(&q->sysfs_lock);
	ret = __blk_mq_register_dev(dev, q);
	mutex_unlock(&q->sysfs_lock);

	return ret;
}