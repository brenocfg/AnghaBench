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
struct hwicap_drvdata {int /*<<< orphan*/  mem_size; int /*<<< orphan*/  mem_start; int /*<<< orphan*/  base_address; int /*<<< orphan*/  cdev; int /*<<< orphan*/  devt; } ;
struct device {int /*<<< orphan*/  devt; } ;

/* Variables and functions */
 size_t MINOR (int /*<<< orphan*/ ) ; 
 size_t XHWICAP_MINOR ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 struct hwicap_drvdata* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icap_class ; 
 int /*<<< orphan*/  icap_sem ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hwicap_drvdata*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__* probed_devices ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hwicap_remove(struct device *dev)
{
	struct hwicap_drvdata *drvdata;

	drvdata = dev_get_drvdata(dev);

	if (!drvdata)
		return 0;

	device_destroy(icap_class, drvdata->devt);
	cdev_del(&drvdata->cdev);
	iounmap(drvdata->base_address);
	release_mem_region(drvdata->mem_start, drvdata->mem_size);
	kfree(drvdata);

	mutex_lock(&icap_sem);
	probed_devices[MINOR(dev->devt)-XHWICAP_MINOR] = 0;
	mutex_unlock(&icap_sem);
	return 0;		/* success */
}