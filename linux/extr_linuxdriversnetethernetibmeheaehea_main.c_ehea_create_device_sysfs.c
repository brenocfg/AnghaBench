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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_probe_port ; 
 int /*<<< orphan*/  dev_attr_remove_port ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ehea_create_device_sysfs(struct platform_device *dev)
{
	int ret = device_create_file(&dev->dev, &dev_attr_probe_port);
	if (ret)
		goto out;

	ret = device_create_file(&dev->dev, &dev_attr_remove_port);
out:
	return ret;
}