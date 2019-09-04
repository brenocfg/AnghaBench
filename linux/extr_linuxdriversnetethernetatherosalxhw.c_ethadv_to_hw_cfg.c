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
struct alx_hw {int dummy; } ;

/* Variables and functions */
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_1000baseT_Half ; 
#define  ADVERTISED_100baseT_Full 131 
#define  ADVERTISED_100baseT_Half 130 
#define  ADVERTISED_10baseT_Full 129 
#define  ADVERTISED_10baseT_Half 128 
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_Pause ; 
 int ADVERTISE_PAUSE_ASYM ; 
 int ADVERTISE_PAUSE_CAP ; 
 int ALX_DRV_PHY_10 ; 
 int ALX_DRV_PHY_100 ; 
 int ALX_DRV_PHY_1000 ; 
 int ALX_DRV_PHY_AUTO ; 
 int ALX_DRV_PHY_DUPLEX ; 

__attribute__((used)) static u32 ethadv_to_hw_cfg(struct alx_hw *hw, u32 ethadv_cfg)
{
	u32 cfg = 0;

	if (ethadv_cfg & ADVERTISED_Autoneg) {
		cfg |= ALX_DRV_PHY_AUTO;
		if (ethadv_cfg & ADVERTISED_10baseT_Half)
			cfg |= ALX_DRV_PHY_10;
		if (ethadv_cfg & ADVERTISED_10baseT_Full)
			cfg |= ALX_DRV_PHY_10 | ALX_DRV_PHY_DUPLEX;
		if (ethadv_cfg & ADVERTISED_100baseT_Half)
			cfg |= ALX_DRV_PHY_100;
		if (ethadv_cfg & ADVERTISED_100baseT_Full)
			cfg |= ALX_DRV_PHY_100 | ALX_DRV_PHY_DUPLEX;
		if (ethadv_cfg & ADVERTISED_1000baseT_Half)
			cfg |= ALX_DRV_PHY_1000;
		if (ethadv_cfg & ADVERTISED_1000baseT_Full)
			cfg |= ALX_DRV_PHY_100 | ALX_DRV_PHY_DUPLEX;
		if (ethadv_cfg & ADVERTISED_Pause)
			cfg |= ADVERTISE_PAUSE_CAP;
		if (ethadv_cfg & ADVERTISED_Asym_Pause)
			cfg |= ADVERTISE_PAUSE_ASYM;
	} else {
		switch (ethadv_cfg) {
		case ADVERTISED_10baseT_Half:
			cfg |= ALX_DRV_PHY_10;
			break;
		case ADVERTISED_100baseT_Half:
			cfg |= ALX_DRV_PHY_100;
			break;
		case ADVERTISED_10baseT_Full:
			cfg |= ALX_DRV_PHY_10 | ALX_DRV_PHY_DUPLEX;
			break;
		case ADVERTISED_100baseT_Full:
			cfg |= ALX_DRV_PHY_100 | ALX_DRV_PHY_DUPLEX;
			break;
		}
	}

	return cfg;
}