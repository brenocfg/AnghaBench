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
struct hbm_version {int major_version; int minor_version; } ;
struct mei_device {int /*<<< orphan*/  device_lock; struct hbm_version version; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct mei_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

__attribute__((used)) static ssize_t hbm_ver_show(struct device *device,
			    struct device_attribute *attr, char *buf)
{
	struct mei_device *dev = dev_get_drvdata(device);
	struct hbm_version ver;

	mutex_lock(&dev->device_lock);
	ver = dev->version;
	mutex_unlock(&dev->device_lock);

	return sprintf(buf, "%u.%u\n", ver.major_version, ver.minor_version);
}