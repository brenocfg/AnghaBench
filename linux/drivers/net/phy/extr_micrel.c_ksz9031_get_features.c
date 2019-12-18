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
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Asym_Pause_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Pause_BIT ; 
 int genphy_read_abilities (struct phy_device*) ; 
 int /*<<< orphan*/  linkmode_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ksz9031_get_features(struct phy_device *phydev)
{
	int ret;

	ret = genphy_read_abilities(phydev);
	if (ret < 0)
		return ret;

	/* Silicon Errata Sheet (DS80000691D or DS80000692D):
	 * Whenever the device's Asymmetric Pause capability is set to 1,
	 * link-up may fail after a link-up to link-down transition.
	 *
	 * The Errata Sheet is for ksz9031, but ksz9021 has the same issue
	 *
	 * Workaround:
	 * Do not enable the Asymmetric Pause capability bit.
	 */
	linkmode_clear_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT, phydev->supported);

	/* We force setting the Pause capability as the core will force the
	 * Asymmetric Pause capability to 1 otherwise.
	 */
	linkmode_set_bit(ETHTOOL_LINK_MODE_Pause_BIT, phydev->supported);

	return 0;
}