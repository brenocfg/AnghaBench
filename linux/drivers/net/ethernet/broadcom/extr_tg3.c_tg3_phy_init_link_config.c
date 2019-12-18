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
typedef  int u32 ;
struct TYPE_2__ {int advertising; void* active_duplex; void* active_speed; int /*<<< orphan*/  autoneg; void* duplex; void* speed; } ;
struct tg3 {int phy_flags; int old_link; TYPE_1__ link_config; } ;

/* Variables and functions */
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_1000baseT_Half ; 
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_FIBRE ; 
 int ADVERTISED_TP ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 void* DUPLEX_UNKNOWN ; 
 void* SPEED_UNKNOWN ; 
 int TG3_PHYFLG_10_100_ONLY ; 
 int TG3_PHYFLG_ANY_SERDES ; 
 int TG3_PHYFLG_DISABLE_1G_HD_ADV ; 

__attribute__((used)) static void tg3_phy_init_link_config(struct tg3 *tp)
{
	u32 adv = ADVERTISED_Autoneg;

	if (!(tp->phy_flags & TG3_PHYFLG_10_100_ONLY)) {
		if (!(tp->phy_flags & TG3_PHYFLG_DISABLE_1G_HD_ADV))
			adv |= ADVERTISED_1000baseT_Half;
		adv |= ADVERTISED_1000baseT_Full;
	}

	if (!(tp->phy_flags & TG3_PHYFLG_ANY_SERDES))
		adv |= ADVERTISED_100baseT_Half |
		       ADVERTISED_100baseT_Full |
		       ADVERTISED_10baseT_Half |
		       ADVERTISED_10baseT_Full |
		       ADVERTISED_TP;
	else
		adv |= ADVERTISED_FIBRE;

	tp->link_config.advertising = adv;
	tp->link_config.speed = SPEED_UNKNOWN;
	tp->link_config.duplex = DUPLEX_UNKNOWN;
	tp->link_config.autoneg = AUTONEG_ENABLE;
	tp->link_config.active_speed = SPEED_UNKNOWN;
	tp->link_config.active_duplex = DUPLEX_UNKNOWN;

	tp->old_link = -1;
}