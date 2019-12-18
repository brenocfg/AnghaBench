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
struct scsi_device {scalar_t__ channel; struct myrb_ldev_info* hostdata; int /*<<< orphan*/  host; } ;
struct myrb_ldev_info {int state; int /*<<< orphan*/  raid_level; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 scalar_t__ myrb_logical_channel (int /*<<< orphan*/ ) ; 
 char* myrb_raidlevel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static ssize_t raid_level_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct scsi_device *sdev = to_scsi_device(dev);

	if (sdev->channel == myrb_logical_channel(sdev->host)) {
		struct myrb_ldev_info *ldev_info = sdev->hostdata;
		const char *name;

		if (!ldev_info)
			return -ENXIO;

		name = myrb_raidlevel_name(ldev_info->raid_level);
		if (!name)
			return snprintf(buf, 32, "Invalid (%02X)\n",
					ldev_info->state);
		return snprintf(buf, 32, "%s\n", name);
	}
	return snprintf(buf, 32, "Physical Drive\n");
}