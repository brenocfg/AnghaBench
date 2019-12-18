#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dasd_uid {int base_unit_addr; char* vduit; char* vendor; char* serial; int ssid; } ;
struct TYPE_3__ {int base_unit_addr; } ;
struct dasd_eckd_private {TYPE_1__ uid; } ;
struct dasd_device {TYPE_2__* cdev; struct dasd_eckd_private* private; } ;
typedef  int /*<<< orphan*/  print_uid ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dasd_alias_remove_device (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_alias_update_add_device (struct dasd_device*) ; 
 int dasd_eckd_generate_uid (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_eckd_get_uid (struct dasd_device*,struct dasd_uid*) ; 
 int dasd_eckd_read_conf (struct dasd_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  get_ccwdev_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,int,int,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int dasd_eckd_reload_device(struct dasd_device *device)
{
	struct dasd_eckd_private *private = device->private;
	int rc, old_base;
	char print_uid[60];
	struct dasd_uid uid;
	unsigned long flags;

	/*
	 * remove device from alias handling to prevent new requests
	 * from being scheduled on the wrong alias device
	 */
	dasd_alias_remove_device(device);

	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	old_base = private->uid.base_unit_addr;
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);

	/* Read Configuration Data */
	rc = dasd_eckd_read_conf(device);
	if (rc)
		goto out_err;

	rc = dasd_eckd_generate_uid(device);
	if (rc)
		goto out_err;
	/*
	 * update unit address configuration and
	 * add device to alias management
	 */
	dasd_alias_update_add_device(device);

	dasd_eckd_get_uid(device, &uid);

	if (old_base != uid.base_unit_addr) {
		if (strlen(uid.vduit) > 0)
			snprintf(print_uid, sizeof(print_uid),
				 "%s.%s.%04x.%02x.%s", uid.vendor, uid.serial,
				 uid.ssid, uid.base_unit_addr, uid.vduit);
		else
			snprintf(print_uid, sizeof(print_uid),
				 "%s.%s.%04x.%02x", uid.vendor, uid.serial,
				 uid.ssid, uid.base_unit_addr);

		dev_info(&device->cdev->dev,
			 "An Alias device was reassigned to a new base device "
			 "with UID: %s\n", print_uid);
	}
	return 0;

out_err:
	return -1;
}