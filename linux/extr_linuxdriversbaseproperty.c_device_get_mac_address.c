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
 int /*<<< orphan*/  dev_fwnode (struct device*) ; 
 void* fwnode_get_mac_address (int /*<<< orphan*/ ,char*,int) ; 

void *device_get_mac_address(struct device *dev, char *addr, int alen)
{
	return fwnode_get_mac_address(dev_fwnode(dev), addr, alen);
}