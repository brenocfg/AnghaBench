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
struct mei_fw_status {int count; int /*<<< orphan*/ * status; } ;
struct mei_device {int /*<<< orphan*/  device_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct mei_device* dev_get_drvdata (struct device*) ; 
 int mei_fw_status (struct mei_device*,struct mei_fw_status*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int scnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t fw_status_show(struct device *device,
		struct device_attribute *attr, char *buf)
{
	struct mei_device *dev = dev_get_drvdata(device);
	struct mei_fw_status fw_status;
	int err, i;
	ssize_t cnt = 0;

	mutex_lock(&dev->device_lock);
	err = mei_fw_status(dev, &fw_status);
	mutex_unlock(&dev->device_lock);
	if (err) {
		dev_err(device, "read fw_status error = %d\n", err);
		return err;
	}

	for (i = 0; i < fw_status.count; i++)
		cnt += scnprintf(buf + cnt, PAGE_SIZE - cnt, "%08X\n",
				fw_status.status[i]);
	return cnt;
}