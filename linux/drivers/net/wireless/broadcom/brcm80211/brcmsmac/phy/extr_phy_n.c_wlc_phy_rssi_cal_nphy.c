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
struct TYPE_2__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {TYPE_1__ pubpi; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPHY_RSSI_SEL_NB ; 
 int /*<<< orphan*/  NPHY_RSSI_SEL_W1 ; 
 int /*<<< orphan*/  NPHY_RSSI_SEL_W2 ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlc_phy_rssi_cal_nphy_rev2 (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_rssi_cal_nphy_rev3 (struct brcms_phy*) ; 

void wlc_phy_rssi_cal_nphy(struct brcms_phy *pi)
{
	if (NREV_GE(pi->pubpi.phy_rev, 3)) {
		wlc_phy_rssi_cal_nphy_rev3(pi);
	} else {
		wlc_phy_rssi_cal_nphy_rev2(pi, NPHY_RSSI_SEL_NB);
		wlc_phy_rssi_cal_nphy_rev2(pi, NPHY_RSSI_SEL_W1);
		wlc_phy_rssi_cal_nphy_rev2(pi, NPHY_RSSI_SEL_W2);
	}
}