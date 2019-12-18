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
struct phy_device {int /*<<< orphan*/  advertising; int /*<<< orphan*/  lp_advertising; } ;
struct TYPE_3__ {scalar_t__ duplex; int speed; int /*<<< orphan*/  bit; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ DUPLEX_FULL ; 
 int SPEED_UNKNOWN ; 
 int /*<<< orphan*/  __ETHTOOL_DECLARE_LINK_MODE_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  common ; 
 int /*<<< orphan*/  linkmode_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* settings ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int phy_resolve_min_speed(struct phy_device *phydev, bool fdx_only)
{
	__ETHTOOL_DECLARE_LINK_MODE_MASK(common);
	int i = ARRAY_SIZE(settings);

	linkmode_and(common, phydev->lp_advertising, phydev->advertising);

	while (--i >= 0) {
		if (test_bit(settings[i].bit, common)) {
			if (fdx_only && settings[i].duplex != DUPLEX_FULL)
				continue;
			return settings[i].speed;
		}
	}

	return SPEED_UNKNOWN;
}