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
struct hl_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct hl_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ hl_device_disabled_or_in_reset (struct hl_device*) ; 
 long hl_get_max_power (struct hl_device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 

__attribute__((used)) static ssize_t max_power_show(struct device *dev, struct device_attribute *attr,
				char *buf)
{
	struct hl_device *hdev = dev_get_drvdata(dev);
	long val;

	if (hl_device_disabled_or_in_reset(hdev))
		return -ENODEV;

	val = hl_get_max_power(hdev);

	return sprintf(buf, "%lu\n", val);
}