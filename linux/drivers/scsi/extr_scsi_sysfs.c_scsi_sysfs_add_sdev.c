#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct scsi_target {int /*<<< orphan*/  dev; } ;
struct TYPE_14__ {int /*<<< orphan*/  kobj; } ;
struct scsi_device {int is_visible; TYPE_2__* host; TYPE_3__ sdev_gendev; TYPE_3__ sdev_dev; struct scsi_target* sdev_target; struct request_queue* request_queue; } ;
struct request_queue {int dummy; } ;
struct TYPE_13__ {TYPE_1__* hostt; } ;
struct TYPE_12__ {scalar_t__ sdev_groups; scalar_t__* sdev_attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int bsg_scsi_register_queue (struct request_queue*,TYPE_3__*) ; 
 int device_add (TYPE_3__*) ; 
 int device_create_file (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  device_del (TYPE_3__*) ; 
 int /*<<< orphan*/  device_enable_async_suspend (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_forbid (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_3__*) ; 
 int /*<<< orphan*/  scsi_autopm_get_device (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_autopm_get_target (struct scsi_target*) ; 
 int /*<<< orphan*/  scsi_autopm_put_device (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_autopm_put_target (struct scsi_target*) ; 
 int /*<<< orphan*/  scsi_dh_add_device (struct scsi_device*) ; 
 int scsi_target_add (struct scsi_target*) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int) ; 
 int sysfs_create_groups (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  transport_add_device (TYPE_3__*) ; 
 int /*<<< orphan*/  transport_configure_device (int /*<<< orphan*/ *) ; 

int scsi_sysfs_add_sdev(struct scsi_device *sdev)
{
	int error, i;
	struct request_queue *rq = sdev->request_queue;
	struct scsi_target *starget = sdev->sdev_target;

	error = scsi_target_add(starget);
	if (error)
		return error;

	transport_configure_device(&starget->dev);

	device_enable_async_suspend(&sdev->sdev_gendev);
	scsi_autopm_get_target(starget);
	pm_runtime_set_active(&sdev->sdev_gendev);
	pm_runtime_forbid(&sdev->sdev_gendev);
	pm_runtime_enable(&sdev->sdev_gendev);
	scsi_autopm_put_target(starget);

	scsi_autopm_get_device(sdev);

	scsi_dh_add_device(sdev);

	error = device_add(&sdev->sdev_gendev);
	if (error) {
		sdev_printk(KERN_INFO, sdev,
				"failed to add device: %d\n", error);
		return error;
	}

	device_enable_async_suspend(&sdev->sdev_dev);
	error = device_add(&sdev->sdev_dev);
	if (error) {
		sdev_printk(KERN_INFO, sdev,
				"failed to add class device: %d\n", error);
		device_del(&sdev->sdev_gendev);
		return error;
	}
	transport_add_device(&sdev->sdev_gendev);
	sdev->is_visible = 1;

	error = bsg_scsi_register_queue(rq, &sdev->sdev_gendev);
	if (error)
		/* we're treating error on bsg register as non-fatal,
		 * so pretend nothing went wrong */
		sdev_printk(KERN_INFO, sdev,
			    "Failed to register bsg queue, errno=%d\n", error);

	/* add additional host specific attributes */
	if (sdev->host->hostt->sdev_attrs) {
		for (i = 0; sdev->host->hostt->sdev_attrs[i]; i++) {
			error = device_create_file(&sdev->sdev_gendev,
					sdev->host->hostt->sdev_attrs[i]);
			if (error)
				return error;
		}
	}

	if (sdev->host->hostt->sdev_groups) {
		error = sysfs_create_groups(&sdev->sdev_gendev.kobj,
				sdev->host->hostt->sdev_groups);
		if (error)
			return error;
	}

	scsi_autopm_put_device(sdev);
	return error;
}