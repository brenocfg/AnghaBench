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
struct tg3 {int phy_flags; int /*<<< orphan*/  phy_addr; int /*<<< orphan*/  mdio_bus; } ;

/* Variables and functions */
 int TG3_PHYFLG_IS_CONNECTED ; 
 int /*<<< orphan*/  mdiobus_get_phy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tg3_phy_stop(struct tg3 *tp)
{
	if (!(tp->phy_flags & TG3_PHYFLG_IS_CONNECTED))
		return;

	phy_stop(mdiobus_get_phy(tp->mdio_bus, tp->phy_addr));
}