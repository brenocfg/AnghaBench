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
struct request_queue {int /*<<< orphan*/  sysfs_lock; int /*<<< orphan*/  kobj; scalar_t__ elevator; scalar_t__ mq_ops; scalar_t__ request_fn; int /*<<< orphan*/  q_usage_counter; int /*<<< orphan*/  queue_flags; } ;
struct gendisk {struct request_queue* queue; } ;
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int /*<<< orphan*/  KOBJ_REMOVE ; 
 int /*<<< orphan*/  QUEUE_FLAG_INIT_DONE ; 
 int /*<<< orphan*/  QUEUE_FLAG_REGISTERED ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ONCE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __blk_mq_register_dev (struct device*,struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_debugfs_register (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_bypass_end (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_init_done (struct request_queue*) ; 
 int /*<<< orphan*/  blk_throtl_register_queue (struct request_queue*) ; 
 int blk_trace_init_sysfs (struct device*) ; 
 int /*<<< orphan*/  blk_trace_remove_sysfs (struct device*) ; 
 struct device* disk_to_dev (struct gendisk*) ; 
 int elv_register_queue (struct request_queue*) ; 
 int kobject_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  kobject_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_switch_to_percpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_flag_set_unlocked (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wbt_enable_default (struct request_queue*) ; 

int blk_register_queue(struct gendisk *disk)
{
	int ret;
	struct device *dev = disk_to_dev(disk);
	struct request_queue *q = disk->queue;

	if (WARN_ON(!q))
		return -ENXIO;

	WARN_ONCE(test_bit(QUEUE_FLAG_REGISTERED, &q->queue_flags),
		  "%s is registering an already registered queue\n",
		  kobject_name(&dev->kobj));
	queue_flag_set_unlocked(QUEUE_FLAG_REGISTERED, q);

	/*
	 * SCSI probing may synchronously create and destroy a lot of
	 * request_queues for non-existent devices.  Shutting down a fully
	 * functional queue takes measureable wallclock time as RCU grace
	 * periods are involved.  To avoid excessive latency in these
	 * cases, a request_queue starts out in a degraded mode which is
	 * faster to shut down and is made fully functional here as
	 * request_queues for non-existent devices never get registered.
	 */
	if (!blk_queue_init_done(q)) {
		queue_flag_set_unlocked(QUEUE_FLAG_INIT_DONE, q);
		percpu_ref_switch_to_percpu(&q->q_usage_counter);
		blk_queue_bypass_end(q);
	}

	ret = blk_trace_init_sysfs(dev);
	if (ret)
		return ret;

	/* Prevent changes through sysfs until registration is completed. */
	mutex_lock(&q->sysfs_lock);

	ret = kobject_add(&q->kobj, kobject_get(&dev->kobj), "%s", "queue");
	if (ret < 0) {
		blk_trace_remove_sysfs(dev);
		goto unlock;
	}

	if (q->mq_ops) {
		__blk_mq_register_dev(dev, q);
		blk_mq_debugfs_register(q);
	}

	kobject_uevent(&q->kobj, KOBJ_ADD);

	wbt_enable_default(q);

	blk_throtl_register_queue(q);

	if (q->request_fn || (q->mq_ops && q->elevator)) {
		ret = elv_register_queue(q);
		if (ret) {
			mutex_unlock(&q->sysfs_lock);
			kobject_uevent(&q->kobj, KOBJ_REMOVE);
			kobject_del(&q->kobj);
			blk_trace_remove_sysfs(dev);
			kobject_put(&dev->kobj);
			return ret;
		}
	}
	ret = 0;
unlock:
	mutex_unlock(&q->sysfs_lock);
	return ret;
}