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
 int /*<<< orphan*/  MII_CIS8201_AUXCONSTAT_INIT ; 
 int /*<<< orphan*/  MII_CIS8201_AUX_CONSTAT ; 
 int /*<<< orphan*/  MII_CIS8201_EXTCON1_INIT ; 
 int /*<<< orphan*/  MII_CIS8201_EXT_CON1 ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cis820x_config_init(struct phy_device *phydev)
{
	int err;

	err = phy_write(phydev, MII_CIS8201_AUX_CONSTAT,
			MII_CIS8201_AUXCONSTAT_INIT);

	if (err < 0)
		return err;

	err = phy_write(phydev, MII_CIS8201_EXT_CON1,
			MII_CIS8201_EXTCON1_INIT);

	return err;
}