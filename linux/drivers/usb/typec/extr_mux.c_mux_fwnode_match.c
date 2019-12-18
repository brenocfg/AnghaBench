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
 void const* dev_fwnode (struct device*) ; 
 scalar_t__ dev_name_ends_with (struct device*,char*) ; 

__attribute__((used)) static int mux_fwnode_match(struct device *dev, const void *fwnode)
{
	return dev_fwnode(dev) == fwnode && dev_name_ends_with(dev, "-mux");
}