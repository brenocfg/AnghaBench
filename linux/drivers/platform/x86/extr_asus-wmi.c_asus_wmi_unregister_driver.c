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
struct asus_wmi_driver {int /*<<< orphan*/  platform_driver; int /*<<< orphan*/  platform_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_driver_unregister (int /*<<< orphan*/ *) ; 
 int used ; 

void asus_wmi_unregister_driver(struct asus_wmi_driver *driver)
{
	platform_device_unregister(driver->platform_device);
	platform_driver_unregister(&driver->platform_driver);
	used = false;
}