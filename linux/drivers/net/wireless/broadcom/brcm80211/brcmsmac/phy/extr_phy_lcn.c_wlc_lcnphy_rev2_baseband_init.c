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
struct brcms_phy {int /*<<< orphan*/  radio_chanspec; } ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS5G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 

__attribute__((used)) static void wlc_lcnphy_rev2_baseband_init(struct brcms_phy *pi)
{
	if (CHSPEC_IS5G(pi->radio_chanspec)) {
		mod_phy_reg(pi, 0x416, (0xff << 0), 80 << 0);
		mod_phy_reg(pi, 0x416, (0xff << 8), 80 << 8);
	}
}