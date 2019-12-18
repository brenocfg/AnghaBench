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
struct scsi_device {unsigned int queue_depth; int /*<<< orphan*/  device_busy; int /*<<< orphan*/  device_blocked; } ;
struct request_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  SCSI_LOG_MLQUEUE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*) ; 

__attribute__((used)) static inline int scsi_dev_queue_ready(struct request_queue *q,
				  struct scsi_device *sdev)
{
	unsigned int busy;

	busy = atomic_inc_return(&sdev->device_busy) - 1;
	if (atomic_read(&sdev->device_blocked)) {
		if (busy)
			goto out_dec;

		/*
		 * unblock after device_blocked iterates to zero
		 */
		if (atomic_dec_return(&sdev->device_blocked) > 0)
			goto out_dec;
		SCSI_LOG_MLQUEUE(3, sdev_printk(KERN_INFO, sdev,
				   "unblocking device at zero depth\n"));
	}

	if (busy >= sdev->queue_depth)
		goto out_dec;

	return 1;
out_dec:
	atomic_dec(&sdev->device_busy);
	return 0;
}