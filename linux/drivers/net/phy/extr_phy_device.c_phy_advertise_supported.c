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
struct phy_device {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ETHTOOL_DECLARE_LINK_MODE_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new ; 
 int /*<<< orphan*/  phy_copy_pause_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void phy_advertise_supported(struct phy_device *phydev)
{
	__ETHTOOL_DECLARE_LINK_MODE_MASK(new);

	linkmode_copy(new, phydev->supported);
	phy_copy_pause_bits(new, phydev->advertising);
	linkmode_copy(phydev->advertising, new);
}