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
struct phy_device {int interface; } ;

/* Variables and functions */
 int BMCR_ANENABLE ; 
 int BMCR_ISOLATE ; 
 int EINVAL ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_DM9161_10BTCSR ; 
 int MII_DM9161_10BTCSR_INIT ; 
 int /*<<< orphan*/  MII_DM9161_SCR ; 
 int MII_DM9161_SCR_INIT ; 
 int MII_DM9161_SCR_RMII ; 
#define  PHY_INTERFACE_MODE_MII 129 
#define  PHY_INTERFACE_MODE_RMII 128 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dm9161_config_init(struct phy_device *phydev)
{
	int err, temp;

	/* Isolate the PHY */
	err = phy_write(phydev, MII_BMCR, BMCR_ISOLATE);

	if (err < 0)
		return err;

	switch (phydev->interface) {
	case PHY_INTERFACE_MODE_MII:
		temp = MII_DM9161_SCR_INIT;
		break;
	case PHY_INTERFACE_MODE_RMII:
		temp =  MII_DM9161_SCR_INIT | MII_DM9161_SCR_RMII;
		break;
	default:
		return -EINVAL;
	}

	/* Do not bypass the scrambler/descrambler */
	err = phy_write(phydev, MII_DM9161_SCR, temp);
	if (err < 0)
		return err;

	/* Clear 10BTCSR to default */
	err = phy_write(phydev, MII_DM9161_10BTCSR, MII_DM9161_10BTCSR_INIT);

	if (err < 0)
		return err;

	/* Reconnect the PHY, and enable Autonegotiation */
	return phy_write(phydev, MII_BMCR, BMCR_ANENABLE);
}