#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {int phy_5g_pwrgain; TYPE_1__* sh; void* nphy_txpwrctrl; TYPE_2__ pubpi; } ;
struct TYPE_3__ {int boardflags2; int sromrev; } ;

/* Variables and functions */
 int BFL2_5G_PWRGAIN ; 
 int BFL2_TXPWRCTRL_EN ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 void* PHY_TPC_HW_OFF ; 
 void* PHY_TPC_HW_ON ; 

__attribute__((used)) static void wlc_phy_txpwrctrl_config_nphy(struct brcms_phy *pi)
{

	if (NREV_GE(pi->pubpi.phy_rev, 3)) {
		pi->nphy_txpwrctrl = PHY_TPC_HW_ON;
		pi->phy_5g_pwrgain = true;
		return;
	}

	pi->nphy_txpwrctrl = PHY_TPC_HW_OFF;
	pi->phy_5g_pwrgain = false;

	if ((pi->sh->boardflags2 & BFL2_TXPWRCTRL_EN) &&
	    NREV_GE(pi->pubpi.phy_rev, 2) && (pi->sh->sromrev >= 4))
		pi->nphy_txpwrctrl = PHY_TPC_HW_ON;
	else if ((pi->sh->sromrev >= 4)
		 && (pi->sh->boardflags2 & BFL2_5G_PWRGAIN))
		pi->phy_5g_pwrgain = true;
}