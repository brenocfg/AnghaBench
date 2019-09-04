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
struct tg3 {int phy_flags; int /*<<< orphan*/  pci_fn; } ;

/* Variables and functions */
#define  ASIC_REV_5700 133 
#define  ASIC_REV_5704 132 
#define  ASIC_REV_5717 131 
#define  ASIC_REV_5719 130 
#define  ASIC_REV_5720 129 
#define  ASIC_REV_5780 128 
 int TG3_PHYFLG_MII_SERDES ; 
 int TG3_PHYFLG_PHY_SERDES ; 
 int tg3_asic_rev (struct tg3*) ; 

__attribute__((used)) static bool tg3_phy_power_bug(struct tg3 *tp)
{
	switch (tg3_asic_rev(tp)) {
	case ASIC_REV_5700:
	case ASIC_REV_5704:
		return true;
	case ASIC_REV_5780:
		if (tp->phy_flags & TG3_PHYFLG_MII_SERDES)
			return true;
		return false;
	case ASIC_REV_5717:
		if (!tp->pci_fn)
			return true;
		return false;
	case ASIC_REV_5719:
	case ASIC_REV_5720:
		if ((tp->phy_flags & TG3_PHYFLG_PHY_SERDES) &&
		    !tp->pci_fn)
			return true;
		return false;
	}

	return false;
}