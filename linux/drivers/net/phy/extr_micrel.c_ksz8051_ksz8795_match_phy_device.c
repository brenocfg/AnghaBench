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
typedef  int u32 ;
struct phy_device {int const phy_id; } ;

/* Variables and functions */
 int BMSR_ERCAP ; 
 int const MICREL_PHY_ID_MASK ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int const PHY_ID_KSZ8051 ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ksz8051_ksz8795_match_phy_device(struct phy_device *phydev,
					    const u32 ksz_phy_id)
{
	int ret;

	if ((phydev->phy_id & MICREL_PHY_ID_MASK) != ksz_phy_id)
		return 0;

	ret = phy_read(phydev, MII_BMSR);
	if (ret < 0)
		return ret;

	/* KSZ8051 PHY and KSZ8794/KSZ8795/KSZ8765 switch share the same
	 * exact PHY ID. However, they can be told apart by the extended
	 * capability registers presence. The KSZ8051 PHY has them while
	 * the switch does not.
	 */
	ret &= BMSR_ERCAP;
	if (ksz_phy_id == PHY_ID_KSZ8051)
		return ret;
	else
		return !ret;
}