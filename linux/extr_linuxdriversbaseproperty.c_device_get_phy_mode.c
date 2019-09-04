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
 int fwnode_get_phy_mode (int /*<<< orphan*/ ) ; 

int device_get_phy_mode(struct device *dev)
{
	return fwnode_get_phy_mode(dev_fwnode(dev));
}