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
struct scsi_cd {int /*<<< orphan*/  kref; int /*<<< orphan*/  disk; int /*<<< orphan*/  device; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_gendisk (int /*<<< orphan*/ ) ; 
 struct scsi_cd* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_autopm_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sr_kref_release ; 
 int /*<<< orphan*/  sr_ref_mutex ; 

__attribute__((used)) static int sr_remove(struct device *dev)
{
	struct scsi_cd *cd = dev_get_drvdata(dev);

	scsi_autopm_get_device(cd->device);

	del_gendisk(cd->disk);
	dev_set_drvdata(dev, NULL);

	mutex_lock(&sr_ref_mutex);
	kref_put(&cd->kref, sr_kref_release);
	mutex_unlock(&sr_ref_mutex);

	return 0;
}