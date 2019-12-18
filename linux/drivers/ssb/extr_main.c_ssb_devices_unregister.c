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
struct ssb_device {scalar_t__ dev; } ;
struct ssb_bus {int nr_devices; scalar_t__ bustype; int /*<<< orphan*/  watchdog; struct ssb_device* devices; } ;

/* Variables and functions */
 scalar_t__ SSB_BUSTYPE_SSB ; 
 int /*<<< orphan*/  device_unregister (scalar_t__) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ssb_devices_unregister(struct ssb_bus *bus)
{
	struct ssb_device *sdev;
	int i;

	for (i = bus->nr_devices - 1; i >= 0; i--) {
		sdev = &(bus->devices[i]);
		if (sdev->dev)
			device_unregister(sdev->dev);
	}

#ifdef CONFIG_SSB_EMBEDDED
	if (bus->bustype == SSB_BUSTYPE_SSB)
		platform_device_unregister(bus->watchdog);
#endif
}