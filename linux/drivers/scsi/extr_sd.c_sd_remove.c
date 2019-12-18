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
struct scsi_disk {int /*<<< orphan*/  dev; int /*<<< orphan*/  opal_dev; int /*<<< orphan*/  disk; int /*<<< orphan*/  device; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  SD_MINORS ; 
 int /*<<< orphan*/  async_synchronize_full_domain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_register_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_gendisk (int /*<<< orphan*/ ) ; 
 struct scsi_disk* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disk_devt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_opal_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_autopm_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_sd_pm_domain ; 
 int /*<<< orphan*/  sd_default_probe ; 
 int /*<<< orphan*/  sd_ref_mutex ; 
 int /*<<< orphan*/  sd_shutdown (struct device*) ; 

__attribute__((used)) static int sd_remove(struct device *dev)
{
	struct scsi_disk *sdkp;
	dev_t devt;

	sdkp = dev_get_drvdata(dev);
	devt = disk_devt(sdkp->disk);
	scsi_autopm_get_device(sdkp->device);

	async_synchronize_full_domain(&scsi_sd_pm_domain);
	device_del(&sdkp->dev);
	del_gendisk(sdkp->disk);
	sd_shutdown(dev);

	free_opal_dev(sdkp->opal_dev);

	blk_register_region(devt, SD_MINORS, NULL,
			    sd_default_probe, NULL, NULL);

	mutex_lock(&sd_ref_mutex);
	dev_set_drvdata(dev, NULL);
	put_device(&sdkp->dev);
	mutex_unlock(&sd_ref_mutex);

	return 0;
}