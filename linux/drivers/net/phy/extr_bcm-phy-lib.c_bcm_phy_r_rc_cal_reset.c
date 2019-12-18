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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_phy_write_exp_sel (struct phy_device*,int,int) ; 

void bcm_phy_r_rc_cal_reset(struct phy_device *phydev)
{
	/* Reset R_CAL/RC_CAL Engine */
	bcm_phy_write_exp_sel(phydev, 0x00b0, 0x0010);

	/* Disable Reset R_AL/RC_CAL Engine */
	bcm_phy_write_exp_sel(phydev, 0x00b0, 0x0000);
}