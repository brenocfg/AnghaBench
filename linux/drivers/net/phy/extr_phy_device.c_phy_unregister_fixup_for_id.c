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

/* Variables and functions */
 int /*<<< orphan*/  PHY_ANY_UID ; 
 int phy_unregister_fixup (char const*,int /*<<< orphan*/ ,int) ; 

int phy_unregister_fixup_for_id(const char *bus_id)
{
	return phy_unregister_fixup(bus_id, PHY_ANY_UID, 0xffffffff);
}