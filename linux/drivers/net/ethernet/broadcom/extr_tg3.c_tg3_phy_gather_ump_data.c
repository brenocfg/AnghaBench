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
struct tg3 {int phy_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 int /*<<< orphan*/  MII_LPA ; 
 int /*<<< orphan*/  MII_PHYADDR ; 
 int /*<<< orphan*/  MII_STAT1000 ; 
 int TG3_PHYFLG_MII_SERDES ; 
 int /*<<< orphan*/  tg3_readphy (struct tg3*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void tg3_phy_gather_ump_data(struct tg3 *tp, u32 *data)
{
	u32 reg, val;

	val = 0;
	if (!tg3_readphy(tp, MII_BMCR, &reg))
		val = reg << 16;
	if (!tg3_readphy(tp, MII_BMSR, &reg))
		val |= (reg & 0xffff);
	*data++ = val;

	val = 0;
	if (!tg3_readphy(tp, MII_ADVERTISE, &reg))
		val = reg << 16;
	if (!tg3_readphy(tp, MII_LPA, &reg))
		val |= (reg & 0xffff);
	*data++ = val;

	val = 0;
	if (!(tp->phy_flags & TG3_PHYFLG_MII_SERDES)) {
		if (!tg3_readphy(tp, MII_CTRL1000, &reg))
			val = reg << 16;
		if (!tg3_readphy(tp, MII_STAT1000, &reg))
			val |= (reg & 0xffff);
	}
	*data++ = val;

	if (!tg3_readphy(tp, MII_PHYADDR, &reg))
		val = reg << 16;
	else
		val = 0;
	*data++ = val;
}