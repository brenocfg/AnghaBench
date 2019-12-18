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
typedef  int u8 ;
struct miphy28lp_phy {scalar_t__ type; scalar_t__ base; } ;

/* Variables and functions */
 int EBUSY ; 
 int HFC_PLL ; 
 int HFC_RDY ; 
 int HZ ; 
 scalar_t__ MIPHY_STATUS_1 ; 
 int PHY_RDY ; 
 scalar_t__ PHY_TYPE_SATA ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int jiffies ; 
 int readb_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  time_after_eq (int,unsigned long) ; 

__attribute__((used)) static inline int miphy_is_ready(struct miphy28lp_phy *miphy_phy)
{
	unsigned long finish = jiffies + 5 * HZ;
	u8 mask = HFC_PLL | HFC_RDY;
	u8 val;

	/*
	 * For PCIe and USB3 check only that PLL and HFC are ready
	 * For SATA check also that phy is ready!
	 */
	if (miphy_phy->type == PHY_TYPE_SATA)
		mask |= PHY_RDY;

	do {
		val = readb_relaxed(miphy_phy->base + MIPHY_STATUS_1);
		if ((val & mask) != mask)
			cpu_relax();
		else
			return 0;
	} while (!time_after_eq(jiffies, finish));

	return -EBUSY;
}