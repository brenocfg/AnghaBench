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
struct platform_device {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* bus_find_device_by_of_node (int /*<<< orphan*/ *,struct device_node*) ; 
 int /*<<< orphan*/  platform_bus_type ; 
 struct platform_device* to_platform_device (struct device*) ; 

struct platform_device *of_find_device_by_node(struct device_node *np)
{
	struct device *dev;

	dev = bus_find_device_by_of_node(&platform_bus_type, np);
	return dev ? to_platform_device(dev) : NULL;
}