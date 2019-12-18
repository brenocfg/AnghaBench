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
 int MDIO_AN_CTRL1_ENABLE ; 
 int MDIO_AN_CTRL1_RESTART ; 
 int /*<<< orphan*/  MDIO_CTRL1 ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int phy_set_bits_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int genphy_c45_restart_aneg(struct phy_device *phydev)
{
	return phy_set_bits_mmd(phydev, MDIO_MMD_AN, MDIO_CTRL1,
				MDIO_AN_CTRL1_ENABLE | MDIO_AN_CTRL1_RESTART);
}