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
struct device {scalar_t__ of_node; } ;

/* Variables and functions */
 int of_property_read_bool (scalar_t__,char*) ; 

__attribute__((used)) static bool use_iram_for_net(struct device *dev)
{
	if (dev && dev->of_node)
		return of_property_read_bool(dev->of_node, "use-iram");
	return false;
}