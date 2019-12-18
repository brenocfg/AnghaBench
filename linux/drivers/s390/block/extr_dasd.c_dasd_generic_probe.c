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
struct dasd_discipline {int dummy; } ;
struct ccw_device {int /*<<< orphan*/  dev; int /*<<< orphan*/ * handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_FEATURE_INITIAL_ONLINE ; 
 int /*<<< orphan*/  DBF_EVENT_DEVID (int /*<<< orphan*/ ,struct ccw_device*,char*,char*) ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 int /*<<< orphan*/  async_schedule (int /*<<< orphan*/ ,struct ccw_device*) ; 
 int dasd_add_sysfs_files (struct ccw_device*) ; 
 scalar_t__ dasd_autodetect ; 
 scalar_t__ dasd_busid_known (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_generic_auto_online ; 
 scalar_t__ dasd_get_feature (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_int_handler ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 

int dasd_generic_probe(struct ccw_device *cdev,
		       struct dasd_discipline *discipline)
{
	int ret;

	ret = dasd_add_sysfs_files(cdev);
	if (ret) {
		DBF_EVENT_DEVID(DBF_WARNING, cdev, "%s",
				"dasd_generic_probe: could not add "
				"sysfs entries");
		return ret;
	}
	cdev->handler = &dasd_int_handler;

	/*
	 * Automatically online either all dasd devices (dasd_autodetect)
	 * or all devices specified with dasd= parameters during
	 * initial probe.
	 */
	if ((dasd_get_feature(cdev, DASD_FEATURE_INITIAL_ONLINE) > 0 ) ||
	    (dasd_autodetect && dasd_busid_known(dev_name(&cdev->dev)) != 0))
		async_schedule(dasd_generic_auto_online, cdev);
	return 0;
}