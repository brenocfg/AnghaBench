#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct phy_device {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  advertising; int /*<<< orphan*/  lp_advertising; } ;
struct TYPE_3__ {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  bit; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  __ETHTOOL_DECLARE_LINK_MODE_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  common ; 
 int /*<<< orphan*/  linkmode_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_resolve_aneg_pause (struct phy_device*) ; 
 TYPE_1__* settings ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void phy_resolve_aneg_linkmode(struct phy_device *phydev)
{
	__ETHTOOL_DECLARE_LINK_MODE_MASK(common);
	int i;

	linkmode_and(common, phydev->lp_advertising, phydev->advertising);

	for (i = 0; i < ARRAY_SIZE(settings); i++)
		if (test_bit(settings[i].bit, common)) {
			phydev->speed = settings[i].speed;
			phydev->duplex = settings[i].duplex;
			break;
		}

	phy_resolve_aneg_pause(phydev);
}