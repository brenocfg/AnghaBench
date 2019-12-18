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
typedef  scalar_t__ u8 ;
struct nphy_txgains {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {TYPE_1__ pubpi; } ;

/* Variables and functions */
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 int wlc_phy_cal_rxiq_nphy_rev2 (struct brcms_phy*,struct nphy_txgains,int) ; 
 int wlc_phy_cal_rxiq_nphy_rev3 (struct brcms_phy*,struct nphy_txgains,scalar_t__,int) ; 

int
wlc_phy_cal_rxiq_nphy(struct brcms_phy *pi, struct nphy_txgains target_gain,
		      u8 cal_type, bool debug)
{
	if (NREV_GE(pi->pubpi.phy_rev, 7))
		cal_type = 0;

	if (NREV_GE(pi->pubpi.phy_rev, 3))
		return wlc_phy_cal_rxiq_nphy_rev3(pi, target_gain, cal_type,
						  debug);
	else
		return wlc_phy_cal_rxiq_nphy_rev2(pi, target_gain, debug);
}