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

/* Variables and functions */
 int bus_register (int /*<<< orphan*/ *) ; 
 int device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbd_bus_type ; 
 int /*<<< orphan*/  rbd_root_dev ; 

__attribute__((used)) static int rbd_sysfs_init(void)
{
	int ret;

	ret = device_register(&rbd_root_dev);
	if (ret < 0)
		return ret;

	ret = bus_register(&rbd_bus_type);
	if (ret < 0)
		device_unregister(&rbd_root_dev);

	return ret;
}