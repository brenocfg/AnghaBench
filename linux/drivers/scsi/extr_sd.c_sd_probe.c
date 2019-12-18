#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * class; struct device* parent; } ;
struct scsi_disk {int index; int media_present; int first_scan; scalar_t__ opal_dev; scalar_t__ security; scalar_t__ capacity; int /*<<< orphan*/  max_medium_access_timeouts; scalar_t__ ATO; scalar_t__ RCD; scalar_t__ WCE; scalar_t__ cache_override; scalar_t__ write_prot; struct scsi_device* device; int /*<<< orphan*/ * driver; TYPE_1__ dev; int /*<<< orphan*/  openers; struct gendisk* disk; } ;
struct scsi_device {scalar_t__ type; int sector_size; scalar_t__ removable; TYPE_4__* request_queue; int /*<<< orphan*/  ioerr_cnt; } ;
struct gendisk {int first_minor; int event_flags; int /*<<< orphan*/  events; int /*<<< orphan*/  flags; TYPE_4__* queue; int /*<<< orphan*/ ** private_data; int /*<<< orphan*/ * fops; int /*<<< orphan*/  major; int /*<<< orphan*/  disk_name; } ;
struct device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  rq_timeout; } ;

/* Variables and functions */
 int DISK_EVENT_FLAG_POLL ; 
 int DISK_EVENT_FLAG_UEVENT ; 
 int /*<<< orphan*/  DISK_EVENT_MEDIA_CHANGE ; 
 int /*<<< orphan*/  DISK_NAME_LEN ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GENHD_FL_EXT_DEVT ; 
 int /*<<< orphan*/  GENHD_FL_REMOVABLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  SCSI_LOG_HLQUEUE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD_MAX_MEDIUM_TIMEOUTS ; 
 int /*<<< orphan*/  SD_MINORS ; 
 int /*<<< orphan*/  SD_MOD_TIMEOUT ; 
 int /*<<< orphan*/  SD_TIMEOUT ; 
 scalar_t__ TYPE_DISK ; 
 scalar_t__ TYPE_MOD ; 
 scalar_t__ TYPE_RBC ; 
 scalar_t__ TYPE_ZBC ; 
 struct gendisk* alloc_disk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_pm_runtime_init (TYPE_4__*,struct device*) ; 
 int /*<<< orphan*/  blk_queue_rq_timeout (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct scsi_disk*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int device_add (TYPE_1__*) ; 
 int /*<<< orphan*/  device_add_disk (struct device*,struct gendisk*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int ida_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,int) ; 
 scalar_t__ init_opal_dev (struct scsi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct scsi_disk*) ; 
 struct scsi_disk* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 
 int /*<<< orphan*/  scsi_autopm_get_device (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_autopm_put_device (struct scsi_device*) ; 
 int /*<<< orphan*/  sd_dif_config_host (struct scsi_disk*) ; 
 int /*<<< orphan*/  sd_disk_class ; 
 int /*<<< orphan*/  sd_fops ; 
 int sd_format_disk_name (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_index_ida ; 
 int /*<<< orphan*/  sd_major (int) ; 
 int /*<<< orphan*/  sd_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*,...) ; 
 int /*<<< orphan*/  sd_revalidate_disk (struct gendisk*) ; 
 int /*<<< orphan*/  sd_sec_submit ; 
 int /*<<< orphan*/  sd_template ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static int sd_probe(struct device *dev)
{
	struct scsi_device *sdp = to_scsi_device(dev);
	struct scsi_disk *sdkp;
	struct gendisk *gd;
	int index;
	int error;

	scsi_autopm_get_device(sdp);
	error = -ENODEV;
	if (sdp->type != TYPE_DISK &&
	    sdp->type != TYPE_ZBC &&
	    sdp->type != TYPE_MOD &&
	    sdp->type != TYPE_RBC)
		goto out;

#ifndef CONFIG_BLK_DEV_ZONED
	if (sdp->type == TYPE_ZBC)
		goto out;
#endif
	SCSI_LOG_HLQUEUE(3, sdev_printk(KERN_INFO, sdp,
					"sd_probe\n"));

	error = -ENOMEM;
	sdkp = kzalloc(sizeof(*sdkp), GFP_KERNEL);
	if (!sdkp)
		goto out;

	gd = alloc_disk(SD_MINORS);
	if (!gd)
		goto out_free;

	index = ida_alloc(&sd_index_ida, GFP_KERNEL);
	if (index < 0) {
		sdev_printk(KERN_WARNING, sdp, "sd_probe: memory exhausted.\n");
		goto out_put;
	}

	error = sd_format_disk_name("sd", index, gd->disk_name, DISK_NAME_LEN);
	if (error) {
		sdev_printk(KERN_WARNING, sdp, "SCSI disk (sd) name length exceeded.\n");
		goto out_free_index;
	}

	sdkp->device = sdp;
	sdkp->driver = &sd_template;
	sdkp->disk = gd;
	sdkp->index = index;
	atomic_set(&sdkp->openers, 0);
	atomic_set(&sdkp->device->ioerr_cnt, 0);

	if (!sdp->request_queue->rq_timeout) {
		if (sdp->type != TYPE_MOD)
			blk_queue_rq_timeout(sdp->request_queue, SD_TIMEOUT);
		else
			blk_queue_rq_timeout(sdp->request_queue,
					     SD_MOD_TIMEOUT);
	}

	device_initialize(&sdkp->dev);
	sdkp->dev.parent = dev;
	sdkp->dev.class = &sd_disk_class;
	dev_set_name(&sdkp->dev, "%s", dev_name(dev));

	error = device_add(&sdkp->dev);
	if (error)
		goto out_free_index;

	get_device(dev);
	dev_set_drvdata(dev, sdkp);

	gd->major = sd_major((index & 0xf0) >> 4);
	gd->first_minor = ((index & 0xf) << 4) | (index & 0xfff00);

	gd->fops = &sd_fops;
	gd->private_data = &sdkp->driver;
	gd->queue = sdkp->device->request_queue;

	/* defaults, until the device tells us otherwise */
	sdp->sector_size = 512;
	sdkp->capacity = 0;
	sdkp->media_present = 1;
	sdkp->write_prot = 0;
	sdkp->cache_override = 0;
	sdkp->WCE = 0;
	sdkp->RCD = 0;
	sdkp->ATO = 0;
	sdkp->first_scan = 1;
	sdkp->max_medium_access_timeouts = SD_MAX_MEDIUM_TIMEOUTS;

	sd_revalidate_disk(gd);

	gd->flags = GENHD_FL_EXT_DEVT;
	if (sdp->removable) {
		gd->flags |= GENHD_FL_REMOVABLE;
		gd->events |= DISK_EVENT_MEDIA_CHANGE;
		gd->event_flags = DISK_EVENT_FLAG_POLL | DISK_EVENT_FLAG_UEVENT;
	}

	blk_pm_runtime_init(sdp->request_queue, dev);
	device_add_disk(dev, gd, NULL);
	if (sdkp->capacity)
		sd_dif_config_host(sdkp);

	sd_revalidate_disk(gd);

	if (sdkp->security) {
		sdkp->opal_dev = init_opal_dev(sdp, &sd_sec_submit);
		if (sdkp->opal_dev)
			sd_printk(KERN_NOTICE, sdkp, "supports TCG Opal\n");
	}

	sd_printk(KERN_NOTICE, sdkp, "Attached SCSI %sdisk\n",
		  sdp->removable ? "removable " : "");
	scsi_autopm_put_device(sdp);

	return 0;

 out_free_index:
	ida_free(&sd_index_ida, index);
 out_put:
	put_disk(gd);
 out_free:
	kfree(sdkp);
 out:
	scsi_autopm_put_device(sdp);
	return error;
}