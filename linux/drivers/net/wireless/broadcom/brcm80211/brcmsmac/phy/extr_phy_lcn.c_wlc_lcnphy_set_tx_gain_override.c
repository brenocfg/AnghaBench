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
typedef  int u16 ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 

__attribute__((used)) static void wlc_lcnphy_set_tx_gain_override(struct brcms_phy *pi, bool bEnable)
{
	u16 bit = bEnable ? 1 : 0;

	mod_phy_reg(pi, 0x4b0, (0x1 << 7), bit << 7);

	mod_phy_reg(pi, 0x4b0, (0x1 << 14), bit << 14);

	mod_phy_reg(pi, 0x43b, (0x1 << 6), bit << 6);
}