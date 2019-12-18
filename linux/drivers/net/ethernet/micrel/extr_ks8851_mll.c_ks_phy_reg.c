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

/* Variables and functions */
 int KS_P1ANAR ; 
 int KS_P1ANLPR ; 
 int KS_P1MBCR ; 
 int KS_P1MBSR ; 
 int KS_PHY1IHR ; 
 int KS_PHY1ILR ; 
#define  MII_ADVERTISE 133 
#define  MII_BMCR 132 
#define  MII_BMSR 131 
#define  MII_LPA 130 
#define  MII_PHYSID1 129 
#define  MII_PHYSID2 128 

__attribute__((used)) static int ks_phy_reg(int reg)
{
	switch (reg) {
	case MII_BMCR:
		return KS_P1MBCR;
	case MII_BMSR:
		return KS_P1MBSR;
	case MII_PHYSID1:
		return KS_PHY1ILR;
	case MII_PHYSID2:
		return KS_PHY1IHR;
	case MII_ADVERTISE:
		return KS_P1ANAR;
	case MII_LPA:
		return KS_P1ANLPR;
	}

	return 0x0;
}