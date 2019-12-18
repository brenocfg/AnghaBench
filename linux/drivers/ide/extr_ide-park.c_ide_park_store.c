#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int dev_flags; scalar_t__ media; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EOVERFLOW ; 
 int IDE_DFLAG_NO_UNLOAD ; 
 int IDE_DFLAG_PARKED ; 
 long MAX_PARK_TIMEOUT ; 
 scalar_t__ ide_disk ; 
 int /*<<< orphan*/  ide_setting_mtx ; 
 int /*<<< orphan*/  issue_park_cmd (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_ide_device (struct device*) ; 

ssize_t ide_park_store(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t len)
{
#define MAX_PARK_TIMEOUT 30000
	ide_drive_t *drive = to_ide_device(dev);
	long int input;
	int rc;

	rc = kstrtol(buf, 10, &input);
	if (rc)
		return rc;
	if (input < -2)
		return -EINVAL;
	if (input > MAX_PARK_TIMEOUT) {
		input = MAX_PARK_TIMEOUT;
		rc = -EOVERFLOW;
	}

	mutex_lock(&ide_setting_mtx);
	if (input >= 0) {
		if (drive->dev_flags & IDE_DFLAG_NO_UNLOAD)
			rc = -EOPNOTSUPP;
		else if (input || drive->dev_flags & IDE_DFLAG_PARKED)
			issue_park_cmd(drive, msecs_to_jiffies(input));
	} else {
		if (drive->media == ide_disk)
			switch (input) {
			case -1:
				drive->dev_flags &= ~IDE_DFLAG_NO_UNLOAD;
				break;
			case -2:
				drive->dev_flags |= IDE_DFLAG_NO_UNLOAD;
				break;
			}
		else
			rc = -EOPNOTSUPP;
	}
	mutex_unlock(&ide_setting_mtx);

	return rc ? rc : len;
}