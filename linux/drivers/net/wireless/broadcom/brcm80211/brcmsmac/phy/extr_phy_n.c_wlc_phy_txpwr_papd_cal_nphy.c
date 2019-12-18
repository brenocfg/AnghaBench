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
struct brcms_phy {scalar_t__* nphy_papd_tx_gain_at_last_cal; scalar_t__ nphy_force_papd_cal; } ;

/* Variables and functions */
 scalar_t__ PHY_IPA (struct brcms_phy*) ; 
 scalar_t__ abs (scalar_t__) ; 
 int /*<<< orphan*/  wlc_phy_a4 (struct brcms_phy*,int) ; 
 scalar_t__ wlc_phy_txpwr_idx_cur_get_nphy (struct brcms_phy*,int) ; 
 scalar_t__ wlc_phy_txpwr_ison_nphy (struct brcms_phy*) ; 

void wlc_phy_txpwr_papd_cal_nphy(struct brcms_phy *pi)
{
	if (PHY_IPA(pi)
	    && (pi->nphy_force_papd_cal
		|| (wlc_phy_txpwr_ison_nphy(pi)
		    &&
		    (((u32)
		      abs(wlc_phy_txpwr_idx_cur_get_nphy(pi, 0) -
			  pi->nphy_papd_tx_gain_at_last_cal[0]) >= 4)
		     || ((u32)
			 abs(wlc_phy_txpwr_idx_cur_get_nphy(pi, 1) -
			     pi->nphy_papd_tx_gain_at_last_cal[1]) >= 4)))))
		wlc_phy_a4(pi, true);
}