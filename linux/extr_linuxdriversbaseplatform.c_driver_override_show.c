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
struct platform_device {char* driver_override; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static ssize_t driver_override_show(struct device *dev,
				    struct device_attribute *attr, char *buf)
{
	struct platform_device *pdev = to_platform_device(dev);
	ssize_t len;

	device_lock(dev);
	len = sprintf(buf, "%s\n", pdev->driver_override);
	device_unlock(dev);
	return len;
}