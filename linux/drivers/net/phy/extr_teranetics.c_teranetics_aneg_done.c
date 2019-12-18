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
 int /*<<< orphan*/  MDIO_MMD_VEND1 ; 
 int genphy_c45_aneg_done (struct phy_device*) ; 
 int /*<<< orphan*/  phy_read_mmd (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int teranetics_aneg_done(struct phy_device *phydev)
{
	/* auto negotiation state can only be checked when using copper
	 * port, if using fiber port, just lie it's done.
	 */
	if (!phy_read_mmd(phydev, MDIO_MMD_VEND1, 93))
		return genphy_c45_aneg_done(phydev);

	return 1;
}