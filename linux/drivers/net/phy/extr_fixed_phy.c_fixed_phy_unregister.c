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
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; TYPE_1__ dev; } ;
struct phy_device {TYPE_2__ mdio; } ;

/* Variables and functions */
 int /*<<< orphan*/  fixed_phy_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_device_remove (struct phy_device*) ; 

void fixed_phy_unregister(struct phy_device *phy)
{
	phy_device_remove(phy);
	of_node_put(phy->mdio.dev.of_node);
	fixed_phy_del(phy->mdio.addr);
}