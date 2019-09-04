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
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_platform_device (struct device*) ; 

__attribute__((used)) static int usbhs_omap_remove_child(struct device *dev, void *data)
{
	dev_info(dev, "unregistering\n");
	platform_device_unregister(to_platform_device(dev));
	return 0;
}