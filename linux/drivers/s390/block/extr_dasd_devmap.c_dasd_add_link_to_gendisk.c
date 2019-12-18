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
struct gendisk {struct dasd_devmap* private_data; } ;
struct dasd_devmap {int dummy; } ;
struct dasd_device {TYPE_1__* cdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dasd_devmap*) ; 
 int /*<<< orphan*/  dasd_devmap_lock ; 
 struct dasd_devmap* dasd_find_busid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void dasd_add_link_to_gendisk(struct gendisk *gdp, struct dasd_device *device)
{
	struct dasd_devmap *devmap;

	devmap = dasd_find_busid(dev_name(&device->cdev->dev));
	if (IS_ERR(devmap))
		return;
	spin_lock(&dasd_devmap_lock);
	gdp->private_data = devmap;
	spin_unlock(&dasd_devmap_lock);
}