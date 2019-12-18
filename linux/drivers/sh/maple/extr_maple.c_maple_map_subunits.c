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
struct maple_device_specify {int unit; int /*<<< orphan*/  port; } ;
struct maple_device {int /*<<< orphan*/  busy; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAPLE_COMMAND_DEVINFO ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int bus_for_each_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct maple_device_specify*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_maple_device ; 
 int /*<<< orphan*/  maple_add_packet (struct maple_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct maple_device* maple_alloc_dev (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  maple_bus_type ; 
 int scanning ; 

__attribute__((used)) static void maple_map_subunits(struct maple_device *mdev, int submask)
{
	int retval, k, devcheck;
	struct maple_device *mdev_add;
	struct maple_device_specify ds;

	ds.port = mdev->port;
	for (k = 0; k < 5; k++) {
		ds.unit = k + 1;
		retval =
		    bus_for_each_dev(&maple_bus_type, NULL, &ds,
				     check_maple_device);
		if (retval) {
			submask = submask >> 1;
			continue;
		}
		devcheck = submask & 0x01;
		if (devcheck) {
			mdev_add = maple_alloc_dev(mdev->port, k + 1);
			if (!mdev_add)
				return;
			atomic_set(&mdev_add->busy, 1);
			maple_add_packet(mdev_add, 0, MAPLE_COMMAND_DEVINFO,
				0, NULL);
			/* mark that we are checking sub devices */
			scanning = 1;
		}
		submask = submask >> 1;
	}
}