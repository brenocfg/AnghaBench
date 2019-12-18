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
typedef  scalar_t__ u8 ;
struct brcms_phy {int /*<<< orphan*/  radio_chanspec; } ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 scalar_t__ PHY_CORE_0 ; 
 scalar_t__ PHY_CORE_1 ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void
wlc_phy_war_force_trsw_to_R_cliplo_nphy(struct brcms_phy *pi, u8 core)
{
	if (core == PHY_CORE_0) {
		write_phy_reg(pi, 0x38, 0x4);
		if (CHSPEC_IS2G(pi->radio_chanspec))
			write_phy_reg(pi, 0x37, 0x0060);
		else
			write_phy_reg(pi, 0x37, 0x1080);
	} else if (core == PHY_CORE_1) {
		write_phy_reg(pi, 0x2ae, 0x4);
		if (CHSPEC_IS2G(pi->radio_chanspec))
			write_phy_reg(pi, 0x2ad, 0x0060);
		else
			write_phy_reg(pi, 0x2ad, 0x1080);
	}
}