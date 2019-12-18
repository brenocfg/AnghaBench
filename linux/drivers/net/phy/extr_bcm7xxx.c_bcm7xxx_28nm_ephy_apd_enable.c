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
 int /*<<< orphan*/  MII_BRCM_FET_BRCMTEST ; 
 int /*<<< orphan*/  MII_BRCM_FET_BT_SRE ; 
 int /*<<< orphan*/  MII_BRCM_FET_SHDW_AS2_APDE ; 
 int /*<<< orphan*/  MII_BRCM_FET_SHDW_AUXSTAT2 ; 
 int phy_set_clr_bits (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm7xxx_28nm_ephy_apd_enable(struct phy_device *phydev)
{
	int ret;

	/* set shadow mode 1 */
	ret = phy_set_clr_bits(phydev, MII_BRCM_FET_BRCMTEST,
			       MII_BRCM_FET_BT_SRE, 0);
	if (ret < 0)
		return ret;

	/* Enable auto-power down */
	ret = phy_set_clr_bits(phydev, MII_BRCM_FET_SHDW_AUXSTAT2,
			       MII_BRCM_FET_SHDW_AS2_APDE, 0);
	if (ret < 0)
		return ret;

	/* reset shadow mode 1 */
	ret = phy_set_clr_bits(phydev, MII_BRCM_FET_BRCMTEST, 0,
			       MII_BRCM_FET_BT_SRE);
	if (ret < 0)
		return ret;

	return 0;
}