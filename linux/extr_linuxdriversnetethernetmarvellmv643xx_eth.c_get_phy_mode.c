#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mv643xx_eth_private {TYPE_2__* dev; } ;
struct device {scalar_t__ of_node; } ;
struct TYPE_3__ {struct device* parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int PHY_INTERFACE_MODE_GMII ; 
 int of_get_phy_mode (scalar_t__) ; 

__attribute__((used)) static int get_phy_mode(struct mv643xx_eth_private *mp)
{
	struct device *dev = mp->dev->dev.parent;
	int iface = -1;

	if (dev->of_node)
		iface = of_get_phy_mode(dev->of_node);

	/* Historical default if unspecified. We could also read/write
	 * the interface state in the PSC1
	 */
	if (iface < 0)
		iface = PHY_INTERFACE_MODE_GMII;
	return iface;
}