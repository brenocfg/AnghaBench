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
struct pmac_i2c_bus {struct device_node* controller; } ;
struct device_node {int dummy; } ;

/* Variables and functions */

struct device_node *pmac_i2c_get_controller(struct pmac_i2c_bus *bus)
{
	return bus->controller;
}