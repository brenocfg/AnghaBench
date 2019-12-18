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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KSZPHY_OMSO_FACTORY_TEST ; 
 int /*<<< orphan*/  MII_KSZPHY_OMSO ; 
 int kszphy_config_init (struct phy_device*) ; 
 int /*<<< orphan*/  phy_clear_bits (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ksz8081_config_init(struct phy_device *phydev)
{
	/* KSZPHY_OMSO_FACTORY_TEST is set at de-assertion of the reset line
	 * based on the RXER (KSZ8081RNA/RND) or TXC (KSZ8081MNX/RNB) pin. If a
	 * pull-down is missing, the factory test mode should be cleared by
	 * manually writing a 0.
	 */
	phy_clear_bits(phydev, MII_KSZPHY_OMSO, KSZPHY_OMSO_FACTORY_TEST);

	return kszphy_config_init(phydev);
}