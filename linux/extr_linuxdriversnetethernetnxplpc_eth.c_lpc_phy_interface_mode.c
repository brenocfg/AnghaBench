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
typedef  int /*<<< orphan*/  phy_interface_t ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_INTERFACE_MODE_MII ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_RMII ; 
 char* of_get_property (scalar_t__,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static phy_interface_t lpc_phy_interface_mode(struct device *dev)
{
	if (dev && dev->of_node) {
		const char *mode = of_get_property(dev->of_node,
						   "phy-mode", NULL);
		if (mode && !strcmp(mode, "mii"))
			return PHY_INTERFACE_MODE_MII;
	}
	return PHY_INTERFACE_MODE_RMII;
}