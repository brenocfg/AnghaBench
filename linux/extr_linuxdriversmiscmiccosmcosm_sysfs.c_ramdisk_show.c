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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cosm_device {char* ramdisk; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct cosm_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static ssize_t
ramdisk_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct cosm_device *cdev = dev_get_drvdata(dev);
	char *ramdisk;

	if (!cdev)
		return -EINVAL;

	ramdisk = cdev->ramdisk;

	if (ramdisk)
		return scnprintf(buf, PAGE_SIZE, "%s\n", ramdisk);
	return 0;
}