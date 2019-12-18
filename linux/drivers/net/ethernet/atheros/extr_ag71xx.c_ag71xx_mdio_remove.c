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
struct ag71xx {int /*<<< orphan*/  clk_mdio; scalar_t__ mii_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (scalar_t__) ; 

__attribute__((used)) static void ag71xx_mdio_remove(struct ag71xx *ag)
{
	if (ag->mii_bus)
		mdiobus_unregister(ag->mii_bus);
	clk_disable_unprepare(ag->clk_mdio);
}