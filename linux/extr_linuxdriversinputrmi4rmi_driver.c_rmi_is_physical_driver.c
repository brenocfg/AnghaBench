#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device_driver {int dummy; } ;
struct TYPE_2__ {struct device_driver driver; } ;

/* Variables and functions */
 TYPE_1__ rmi_physical_driver ; 

bool rmi_is_physical_driver(struct device_driver *drv)
{
	return drv == &rmi_physical_driver.driver;
}