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

__attribute__((used)) static void wlc_lcnphy_set_rx_iq_comp(struct brcms_phy *pi, u16 a, u16 b)
{
	mod_phy_reg(pi, 0x645, (0x3ff << 0), (a) << 0);

	mod_phy_reg(pi, 0x646, (0x3ff << 0), (b) << 0);

	mod_phy_reg(pi, 0x647, (0x3ff << 0), (a) << 0);

	mod_phy_reg(pi, 0x648, (0x3ff << 0), (b) << 0);

	mod_phy_reg(pi, 0x649, (0x3ff << 0), (a) << 0);

	mod_phy_reg(pi, 0x64a, (0x3ff << 0), (b) << 0);

}