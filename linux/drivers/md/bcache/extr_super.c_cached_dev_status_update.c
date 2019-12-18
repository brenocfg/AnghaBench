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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct cached_dev {int io_disable; scalar_t__ offline_seconds; TYPE_1__ disk; int /*<<< orphan*/  backing_dev_name; int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 scalar_t__ BACKING_DEV_OFFLINE_TIMEOUT ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  bcache_device_stop (TYPE_1__*) ; 
 struct request_queue* bdev_get_queue (int /*<<< orphan*/ ) ; 
 scalar_t__ blk_queue_dying (struct request_queue*) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  wait_for_kthread_stop () ; 

__attribute__((used)) static int cached_dev_status_update(void *arg)
{
	struct cached_dev *dc = arg;
	struct request_queue *q;

	/*
	 * If this delayed worker is stopping outside, directly quit here.
	 * dc->io_disable might be set via sysfs interface, so check it
	 * here too.
	 */
	while (!kthread_should_stop() && !dc->io_disable) {
		q = bdev_get_queue(dc->bdev);
		if (blk_queue_dying(q))
			dc->offline_seconds++;
		else
			dc->offline_seconds = 0;

		if (dc->offline_seconds >= BACKING_DEV_OFFLINE_TIMEOUT) {
			pr_err("%s: device offline for %d seconds",
			       dc->backing_dev_name,
			       BACKING_DEV_OFFLINE_TIMEOUT);
			pr_err("%s: disable I/O request due to backing "
			       "device offline", dc->disk.name);
			dc->io_disable = true;
			/* let others know earlier that io_disable is true */
			smp_mb();
			bcache_device_stop(&dc->disk);
			break;
		}
		schedule_timeout_interruptible(HZ);
	}

	wait_for_kthread_stop();
	return 0;
}