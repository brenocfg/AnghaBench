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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  dev_attr_core_id ; 
 int device_create_file (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int malidp_init_sysfs(struct device *dev)
{
	int ret = device_create_file(dev, &dev_attr_core_id);

	if (ret)
		DRM_ERROR("failed to create device file for core_id\n");

	return ret;
}