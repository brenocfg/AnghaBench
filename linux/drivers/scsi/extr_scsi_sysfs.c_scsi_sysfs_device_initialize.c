#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct scsi_target {int /*<<< orphan*/  reap_ref; int /*<<< orphan*/  devices; int /*<<< orphan*/  scsi_level; } ;
struct TYPE_5__ {int /*<<< orphan*/ * class; int /*<<< orphan*/  parent; int /*<<< orphan*/ * type; int /*<<< orphan*/ * bus; } ;
struct scsi_device {int lun_in_cdb; int /*<<< orphan*/  siblings; int /*<<< orphan*/  same_target_siblings; TYPE_1__ sdev_gendev; int /*<<< orphan*/  scsi_level; int /*<<< orphan*/  lun; int /*<<< orphan*/  id; int /*<<< orphan*/  channel; struct Scsi_Host* host; TYPE_1__ sdev_dev; struct scsi_target* sdev_target; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; int /*<<< orphan*/  __devices; int /*<<< orphan*/  no_scsi2_lun_in_cdb; int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCSI_2 ; 
 int /*<<< orphan*/  SCSI_UNKNOWN ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  get_device (TYPE_1__*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_bus_type ; 
 int /*<<< orphan*/  scsi_dev_type ; 
 int /*<<< orphan*/  sdev_class ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  transport_setup_device (TYPE_1__*) ; 

void scsi_sysfs_device_initialize(struct scsi_device *sdev)
{
	unsigned long flags;
	struct Scsi_Host *shost = sdev->host;
	struct scsi_target  *starget = sdev->sdev_target;

	device_initialize(&sdev->sdev_gendev);
	sdev->sdev_gendev.bus = &scsi_bus_type;
	sdev->sdev_gendev.type = &scsi_dev_type;
	dev_set_name(&sdev->sdev_gendev, "%d:%d:%d:%llu",
		     sdev->host->host_no, sdev->channel, sdev->id, sdev->lun);

	device_initialize(&sdev->sdev_dev);
	sdev->sdev_dev.parent = get_device(&sdev->sdev_gendev);
	sdev->sdev_dev.class = &sdev_class;
	dev_set_name(&sdev->sdev_dev, "%d:%d:%d:%llu",
		     sdev->host->host_no, sdev->channel, sdev->id, sdev->lun);
	/*
	 * Get a default scsi_level from the target (derived from sibling
	 * devices).  This is the best we can do for guessing how to set
	 * sdev->lun_in_cdb for the initial INQUIRY command.  For LUN 0 the
	 * setting doesn't matter, because all the bits are zero anyway.
	 * But it does matter for higher LUNs.
	 */
	sdev->scsi_level = starget->scsi_level;
	if (sdev->scsi_level <= SCSI_2 &&
			sdev->scsi_level != SCSI_UNKNOWN &&
			!shost->no_scsi2_lun_in_cdb)
		sdev->lun_in_cdb = 1;

	transport_setup_device(&sdev->sdev_gendev);
	spin_lock_irqsave(shost->host_lock, flags);
	list_add_tail(&sdev->same_target_siblings, &starget->devices);
	list_add_tail(&sdev->siblings, &shost->__devices);
	spin_unlock_irqrestore(shost->host_lock, flags);
	/*
	 * device can now only be removed via __scsi_remove_device() so hold
	 * the target.  Target will be held in CREATED state until something
	 * beneath it becomes visible (in which case it moves to RUNNING)
	 */
	kref_get(&starget->reap_ref);
}