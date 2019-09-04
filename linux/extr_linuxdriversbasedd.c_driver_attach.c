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
struct device_driver {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  __driver_attach ; 
 int bus_for_each_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct device_driver*,int /*<<< orphan*/ ) ; 

int driver_attach(struct device_driver *drv)
{
	return bus_for_each_dev(drv->bus, NULL, drv, __driver_attach);
}