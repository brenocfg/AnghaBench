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
struct dasd_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dasd_alias_disconnect_device_from_lcu (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_alias_remove_device (struct dasd_device*) ; 

__attribute__((used)) static int dasd_eckd_pm_freeze(struct dasd_device *device)
{
	/*
	 * the device should be disconnected from our LCU structure
	 * on restore we will reconnect it and reread LCU specific
	 * information like PAV support that might have changed
	 */
	dasd_alias_remove_device(device);
	dasd_alias_disconnect_device_from_lcu(device);

	return 0;
}