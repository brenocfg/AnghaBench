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
struct dasd_devmap {int features; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dasd_devmap*) ; 
 int PTR_ERR (struct dasd_devmap*) ; 
 struct dasd_devmap* dasd_find_busid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 

int
dasd_get_feature(struct ccw_device *cdev, int feature)
{
	struct dasd_devmap *devmap;

	devmap = dasd_find_busid(dev_name(&cdev->dev));
	if (IS_ERR(devmap))
		return PTR_ERR(devmap);

	return ((devmap->features & feature) != 0);
}