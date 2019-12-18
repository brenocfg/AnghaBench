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
struct phy_device {int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_FIBRE_BIT ; 
 int NB_FIBER_STATS ; 
 scalar_t__ linkmode_test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  marvell_hw_stats ; 

__attribute__((used)) static int marvell_get_sset_count(struct phy_device *phydev)
{
	if (linkmode_test_bit(ETHTOOL_LINK_MODE_FIBRE_BIT,
			      phydev->supported))
		return ARRAY_SIZE(marvell_hw_stats);
	else
		return ARRAY_SIZE(marvell_hw_stats) - NB_FIBER_STATS;
}