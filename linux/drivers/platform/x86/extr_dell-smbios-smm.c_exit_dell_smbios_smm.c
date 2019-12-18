#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ buffer ; 
 int /*<<< orphan*/  dell_smbios_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 TYPE_1__* platform_device ; 
 int /*<<< orphan*/  platform_device_unregister (TYPE_1__*) ; 

void exit_dell_smbios_smm(void)
{
	if (platform_device) {
		dell_smbios_unregister_device(&platform_device->dev);
		platform_device_unregister(platform_device);
		free_page((unsigned long)buffer);
	}
}