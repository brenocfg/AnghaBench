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
typedef  scalar_t__ u16 ;
struct sas_task {int task_state_flags; int /*<<< orphan*/  task_state_lock; int /*<<< orphan*/  uldd_task; int /*<<< orphan*/  dev; } ;
struct isci_remote_device {int /*<<< orphan*/  flags; } ;
struct isci_host {int /*<<< orphan*/  scic_lock; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDEV_GONE ; 
 int /*<<< orphan*/  ISCI_TAG_TCI (scalar_t__) ; 
 int /*<<< orphan*/  SAM_STAT_TASK_ABORTED ; 
 int /*<<< orphan*/  SAS_DEVICE_UNKNOWN ; 
 int /*<<< orphan*/  SAS_QUEUE_FULL ; 
 int SAS_TASK_AT_INITIATOR ; 
 int /*<<< orphan*/  SAS_TASK_COMPLETE ; 
 int SAS_TASK_STATE_ABORTED ; 
 int /*<<< orphan*/  SAS_TASK_UNDELIVERED ; 
 scalar_t__ SCI_CONTROLLER_INVALID_IO_TAG ; 
 int SCI_FAILURE ; 
 int SCI_SUCCESS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,struct sas_task*,int /*<<< orphan*/ ,struct isci_remote_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct isci_host* dev_to_ihost (int /*<<< orphan*/ ) ; 
 scalar_t__ isci_alloc_tag (struct isci_host*) ; 
 int isci_device_io_ready (struct isci_remote_device*,struct sas_task*) ; 
 struct isci_remote_device* isci_lookup_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isci_put_device (struct isci_remote_device*) ; 
 int isci_request_execute (struct isci_host*,struct isci_remote_device*,struct sas_task*,scalar_t__) ; 
 int /*<<< orphan*/  isci_task_refuse (struct isci_host*,struct sas_task*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isci_tci_free (struct isci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int isci_task_execute_task(struct sas_task *task, gfp_t gfp_flags)
{
	struct isci_host *ihost = dev_to_ihost(task->dev);
	struct isci_remote_device *idev;
	unsigned long flags;
	enum sci_status status = SCI_FAILURE;
	bool io_ready;
	u16 tag;

	spin_lock_irqsave(&ihost->scic_lock, flags);
	idev = isci_lookup_device(task->dev);
	io_ready = isci_device_io_ready(idev, task);
	tag = isci_alloc_tag(ihost);
	spin_unlock_irqrestore(&ihost->scic_lock, flags);

	dev_dbg(&ihost->pdev->dev,
		"task: %p, dev: %p idev: %p:%#lx cmd = %p\n",
		task, task->dev, idev, idev ? idev->flags : 0,
		task->uldd_task);

	if (!idev) {
		isci_task_refuse(ihost, task, SAS_TASK_UNDELIVERED,
				 SAS_DEVICE_UNKNOWN);
	} else if (!io_ready || tag == SCI_CONTROLLER_INVALID_IO_TAG) {
		/* Indicate QUEUE_FULL so that the scsi midlayer
		 * retries.
		  */
		isci_task_refuse(ihost, task, SAS_TASK_COMPLETE,
				 SAS_QUEUE_FULL);
	} else {
		/* There is a device and it's ready for I/O. */
		spin_lock_irqsave(&task->task_state_lock, flags);

		if (task->task_state_flags & SAS_TASK_STATE_ABORTED) {
			/* The I/O was aborted. */
			spin_unlock_irqrestore(&task->task_state_lock, flags);

			isci_task_refuse(ihost, task,
					 SAS_TASK_UNDELIVERED,
					 SAM_STAT_TASK_ABORTED);
		} else {
			task->task_state_flags |= SAS_TASK_AT_INITIATOR;
			spin_unlock_irqrestore(&task->task_state_lock, flags);

			/* build and send the request. */
			status = isci_request_execute(ihost, idev, task, tag);

			if (status != SCI_SUCCESS) {
				spin_lock_irqsave(&task->task_state_lock, flags);
				/* Did not really start this command. */
				task->task_state_flags &= ~SAS_TASK_AT_INITIATOR;
				spin_unlock_irqrestore(&task->task_state_lock, flags);

				if (test_bit(IDEV_GONE, &idev->flags)) {
					/* Indicate that the device
					 * is gone.
					 */
					isci_task_refuse(ihost, task,
						SAS_TASK_UNDELIVERED,
						SAS_DEVICE_UNKNOWN);
				} else {
					/* Indicate QUEUE_FULL so that
					 * the scsi midlayer retries.
					 * If the request failed for
					 * remote device reasons, it
					 * gets returned as
					 * SAS_TASK_UNDELIVERED next
					 * time through.
					 */
					isci_task_refuse(ihost, task,
						SAS_TASK_COMPLETE,
						SAS_QUEUE_FULL);
				}
			}
		}
	}

	if (status != SCI_SUCCESS && tag != SCI_CONTROLLER_INVALID_IO_TAG) {
		spin_lock_irqsave(&ihost->scic_lock, flags);
		/* command never hit the device, so just free
		 * the tci and skip the sequence increment
		 */
		isci_tci_free(ihost, ISCI_TAG_TCI(tag));
		spin_unlock_irqrestore(&ihost->scic_lock, flags);
	}

	isci_put_device(idev);
	return 0;
}