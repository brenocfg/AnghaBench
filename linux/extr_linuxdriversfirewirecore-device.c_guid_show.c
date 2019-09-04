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
struct fw_device {int* config_rom; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct fw_device* fw_device (struct device*) ; 
 int /*<<< orphan*/  fw_device_rwsem ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t guid_show(struct device *dev,
			 struct device_attribute *attr, char *buf)
{
	struct fw_device *device = fw_device(dev);
	int ret;

	down_read(&fw_device_rwsem);
	ret = snprintf(buf, PAGE_SIZE, "0x%08x%08x\n",
		       device->config_rom[3], device->config_rom[4]);
	up_read(&fw_device_rwsem);

	return ret;
}