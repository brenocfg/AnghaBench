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
struct phy_fixup {int phy_uid; int phy_uid_mask; int /*<<< orphan*/  bus_id; } ;
struct phy_device {int phy_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_ANY_ID ; 
 int PHY_ANY_UID ; 
 int /*<<< orphan*/  phydev_name (struct phy_device*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int phy_needs_fixup(struct phy_device *phydev, struct phy_fixup *fixup)
{
	if (strcmp(fixup->bus_id, phydev_name(phydev)) != 0)
		if (strcmp(fixup->bus_id, PHY_ANY_ID) != 0)
			return 0;

	if ((fixup->phy_uid & fixup->phy_uid_mask) !=
	    (phydev->phy_id & fixup->phy_uid_mask))
		if (fixup->phy_uid != PHY_ANY_UID)
			return 0;

	return 1;
}