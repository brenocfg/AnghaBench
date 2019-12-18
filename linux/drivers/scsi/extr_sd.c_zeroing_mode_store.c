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
struct scsi_disk {int zeroing_mode; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 size_t EACCES ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int sysfs_match_string (int /*<<< orphan*/ ,char const*) ; 
 struct scsi_disk* to_scsi_disk (struct device*) ; 
 int /*<<< orphan*/  zeroing_mode ; 

__attribute__((used)) static ssize_t
zeroing_mode_store(struct device *dev, struct device_attribute *attr,
		   const char *buf, size_t count)
{
	struct scsi_disk *sdkp = to_scsi_disk(dev);
	int mode;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	mode = sysfs_match_string(zeroing_mode, buf);
	if (mode < 0)
		return -EINVAL;

	sdkp->zeroing_mode = mode;

	return count;
}