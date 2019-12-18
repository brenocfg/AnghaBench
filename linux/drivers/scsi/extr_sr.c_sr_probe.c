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
struct scsi_device {scalar_t__ type; int changed; int sector_size; int /*<<< orphan*/  sdev_gendev; int /*<<< orphan*/  request_queue; } ;
struct TYPE_2__ {int capacity; int /*<<< orphan*/  name; struct gendisk* disk; scalar_t__ mask; struct scsi_cd* handle; int /*<<< orphan*/ * ops; } ;
struct scsi_cd {int capacity; int media_present; int use; struct scsi_device* device; TYPE_1__ cdi; int /*<<< orphan*/ * driver; scalar_t__ readcd_cdda; scalar_t__ readcd_known; struct gendisk* disk; int /*<<< orphan*/  kref; } ;
struct gendisk {int first_minor; int flags; int events; int event_flags; int /*<<< orphan*/  queue; int /*<<< orphan*/ ** private_data; int /*<<< orphan*/ * fops; int /*<<< orphan*/  disk_name; int /*<<< orphan*/  major; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int DISK_EVENT_EJECT_REQUEST ; 
 int DISK_EVENT_FLAG_POLL ; 
 int DISK_EVENT_FLAG_UEVENT ; 
 int DISK_EVENT_MEDIA_CHANGE ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int GENHD_FL_BLOCK_EVENTS_ON_EXCL_WRITE ; 
 int GENHD_FL_CD ; 
 int GENHD_FL_REMOVABLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  SCSI_CDROM_MAJOR ; 
 int SR_DISKS ; 
 int /*<<< orphan*/  SR_TIMEOUT ; 
 scalar_t__ TYPE_ROM ; 
 scalar_t__ TYPE_WORM ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 struct gendisk* alloc_disk (int) ; 
 int /*<<< orphan*/  blk_pm_runtime_init (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  blk_queue_rq_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct scsi_cd*) ; 
 int /*<<< orphan*/  device_add_disk (int /*<<< orphan*/ *,struct gendisk*,int /*<<< orphan*/ *) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_capabilities (struct scsi_cd*) ; 
 int /*<<< orphan*/  kfree (struct scsi_cd*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct scsi_cd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 
 scalar_t__ register_cdrom (TYPE_1__*) ; 
 int /*<<< orphan*/  scsi_autopm_get_device (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_autopm_put_device (struct scsi_device*) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_capacity (struct gendisk*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sr_bdops ; 
 int /*<<< orphan*/  sr_dops ; 
 int /*<<< orphan*/  sr_index_bits ; 
 int /*<<< orphan*/  sr_index_lock ; 
 int /*<<< orphan*/  sr_template ; 
 int /*<<< orphan*/  sr_vendor_init (struct scsi_cd*) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static int sr_probe(struct device *dev)
{
	struct scsi_device *sdev = to_scsi_device(dev);
	struct gendisk *disk;
	struct scsi_cd *cd;
	int minor, error;

	scsi_autopm_get_device(sdev);
	error = -ENODEV;
	if (sdev->type != TYPE_ROM && sdev->type != TYPE_WORM)
		goto fail;

	error = -ENOMEM;
	cd = kzalloc(sizeof(*cd), GFP_KERNEL);
	if (!cd)
		goto fail;

	kref_init(&cd->kref);

	disk = alloc_disk(1);
	if (!disk)
		goto fail_free;

	spin_lock(&sr_index_lock);
	minor = find_first_zero_bit(sr_index_bits, SR_DISKS);
	if (minor == SR_DISKS) {
		spin_unlock(&sr_index_lock);
		error = -EBUSY;
		goto fail_put;
	}
	__set_bit(minor, sr_index_bits);
	spin_unlock(&sr_index_lock);

	disk->major = SCSI_CDROM_MAJOR;
	disk->first_minor = minor;
	sprintf(disk->disk_name, "sr%d", minor);
	disk->fops = &sr_bdops;
	disk->flags = GENHD_FL_CD | GENHD_FL_BLOCK_EVENTS_ON_EXCL_WRITE;
	disk->events = DISK_EVENT_MEDIA_CHANGE | DISK_EVENT_EJECT_REQUEST;
	disk->event_flags = DISK_EVENT_FLAG_POLL | DISK_EVENT_FLAG_UEVENT;

	blk_queue_rq_timeout(sdev->request_queue, SR_TIMEOUT);

	cd->device = sdev;
	cd->disk = disk;
	cd->driver = &sr_template;
	cd->disk = disk;
	cd->capacity = 0x1fffff;
	cd->device->changed = 1;	/* force recheck CD type */
	cd->media_present = 1;
	cd->use = 1;
	cd->readcd_known = 0;
	cd->readcd_cdda = 0;

	cd->cdi.ops = &sr_dops;
	cd->cdi.handle = cd;
	cd->cdi.mask = 0;
	cd->cdi.capacity = 1;
	sprintf(cd->cdi.name, "sr%d", minor);

	sdev->sector_size = 2048;	/* A guess, just in case */

	/* FIXME: need to handle a get_capabilities failure properly ?? */
	get_capabilities(cd);
	sr_vendor_init(cd);

	set_capacity(disk, cd->capacity);
	disk->private_data = &cd->driver;
	disk->queue = sdev->request_queue;
	cd->cdi.disk = disk;

	if (register_cdrom(&cd->cdi))
		goto fail_put;

	/*
	 * Initialize block layer runtime PM stuffs before the
	 * periodic event checking request gets started in add_disk.
	 */
	blk_pm_runtime_init(sdev->request_queue, dev);

	dev_set_drvdata(dev, cd);
	disk->flags |= GENHD_FL_REMOVABLE;
	device_add_disk(&sdev->sdev_gendev, disk, NULL);

	sdev_printk(KERN_DEBUG, sdev,
		    "Attached scsi CD-ROM %s\n", cd->cdi.name);
	scsi_autopm_put_device(cd->device);

	return 0;

fail_put:
	put_disk(disk);
fail_free:
	kfree(cd);
fail:
	scsi_autopm_put_device(sdev);
	return error;
}