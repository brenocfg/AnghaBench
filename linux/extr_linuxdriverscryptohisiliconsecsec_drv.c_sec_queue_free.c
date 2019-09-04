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
struct sec_queue {int in_use; int /*<<< orphan*/  queue_id; struct sec_dev_info* dev_info; } ;
struct sec_dev_info {int /*<<< orphan*/  dev_lock; int /*<<< orphan*/  queues_in_use; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SEC_Q_NUM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sec_queue_free(struct sec_queue *queue)
{
	struct sec_dev_info *info = queue->dev_info;

	if (queue->queue_id >= SEC_Q_NUM) {
		dev_err(info->dev, "No queue %d\n", queue->queue_id);
		return -ENODEV;
	}

	if (!queue->in_use) {
		dev_err(info->dev, "Queue %d is idle\n", queue->queue_id);
		return -ENODEV;
	}

	mutex_lock(&info->dev_lock);
	queue->in_use = false;
	info->queues_in_use--;
	mutex_unlock(&info->dev_lock);

	return 0;
}