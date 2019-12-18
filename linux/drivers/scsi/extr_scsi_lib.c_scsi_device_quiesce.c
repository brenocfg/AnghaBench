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
struct scsi_device {scalar_t__ quiesced_by; int /*<<< orphan*/  state_mutex; struct request_queue* request_queue; } ;
struct request_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDEV_QUIESCE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  blk_clear_pm_only (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_freeze_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_unfreeze_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_set_pm_only (struct request_queue*) ; 
 scalar_t__ current ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int scsi_device_set_state (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

int
scsi_device_quiesce(struct scsi_device *sdev)
{
	struct request_queue *q = sdev->request_queue;
	int err;

	/*
	 * It is allowed to call scsi_device_quiesce() multiple times from
	 * the same context but concurrent scsi_device_quiesce() calls are
	 * not allowed.
	 */
	WARN_ON_ONCE(sdev->quiesced_by && sdev->quiesced_by != current);

	if (sdev->quiesced_by == current)
		return 0;

	blk_set_pm_only(q);

	blk_mq_freeze_queue(q);
	/*
	 * Ensure that the effect of blk_set_pm_only() will be visible
	 * for percpu_ref_tryget() callers that occur after the queue
	 * unfreeze even if the queue was already frozen before this function
	 * was called. See also https://lwn.net/Articles/573497/.
	 */
	synchronize_rcu();
	blk_mq_unfreeze_queue(q);

	mutex_lock(&sdev->state_mutex);
	err = scsi_device_set_state(sdev, SDEV_QUIESCE);
	if (err == 0)
		sdev->quiesced_by = current;
	else
		blk_clear_pm_only(q);
	mutex_unlock(&sdev->state_mutex);

	return err;
}