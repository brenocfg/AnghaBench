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
typedef  int u8 ;
struct mei_device {int tx_queue_limit; int /*<<< orphan*/  device_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct mei_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t tx_queue_limit_show(struct device *device,
				   struct device_attribute *attr, char *buf)
{
	struct mei_device *dev = dev_get_drvdata(device);
	u8 size = 0;

	mutex_lock(&dev->device_lock);
	size = dev->tx_queue_limit;
	mutex_unlock(&dev->device_lock);

	return snprintf(buf, PAGE_SIZE, "%u\n", size);
}