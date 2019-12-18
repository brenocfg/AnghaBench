#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct phy_device {int phy_id; TYPE_1__* drv; } ;
struct TYPE_2__ {int phy_id_mask; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int DOWNSHIFT_DEV_DISABLE ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int bcm_phy_28nm_a0b0_afe_config_init (struct phy_device*) ; 
 int bcm_phy_downshift_get (struct phy_device*,int*) ; 
 int bcm_phy_enable_apd (struct phy_device*,int) ; 
 int bcm_phy_set_eee (struct phy_device*,int) ; 
 int /*<<< orphan*/  phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydev_name (struct phy_device*) ; 
 int /*<<< orphan*/  pr_info_once (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm_omega_config_init(struct phy_device *phydev)
{
	u8 count, rev;
	int ret = 0;

	rev = phydev->phy_id & ~phydev->drv->phy_id_mask;

	pr_info_once("%s: %s PHY revision: 0x%02x\n",
		     phydev_name(phydev), phydev->drv->name, rev);

	/* Dummy read to a register to workaround an issue upon reset where the
	 * internal inverter may not allow the first MDIO transaction to pass
	 * the MDIO management controller and make us return 0xffff for such
	 * reads.
	 */
	phy_read(phydev, MII_BMSR);

	switch (rev) {
	case 0x00:
		ret = bcm_phy_28nm_a0b0_afe_config_init(phydev);
		break;
	default:
		break;
	}

	if (ret)
		return ret;

	ret = bcm_phy_downshift_get(phydev, &count);
	if (ret)
		return ret;

	/* Only enable EEE if Wirespeed/downshift is disabled */
	ret = bcm_phy_set_eee(phydev, count == DOWNSHIFT_DEV_DISABLE);
	if (ret)
		return ret;

	return bcm_phy_enable_apd(phydev, true);
}