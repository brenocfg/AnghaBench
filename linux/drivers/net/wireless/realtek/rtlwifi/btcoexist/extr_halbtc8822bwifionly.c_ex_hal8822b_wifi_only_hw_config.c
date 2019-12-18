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
struct wifi_only_cfg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  halwifionly_phy_set_bb_reg (struct wifi_only_cfg*,int,int,int) ; 

void ex_hal8822b_wifi_only_hw_config(struct wifi_only_cfg *wifionlycfg)
{
	/*BB control*/
	halwifionly_phy_set_bb_reg(wifionlycfg, 0x4c, 0x01800000, 0x2);
	/*SW control*/
	halwifionly_phy_set_bb_reg(wifionlycfg, 0xcb4, 0xff, 0x77);
	/*antenna mux switch */
	halwifionly_phy_set_bb_reg(wifionlycfg, 0x974, 0x300, 0x3);

	halwifionly_phy_set_bb_reg(wifionlycfg, 0x1990, 0x300, 0x0);

	halwifionly_phy_set_bb_reg(wifionlycfg, 0xcbc, 0x80000, 0x0);
	/*switch to WL side controller and gnt_wl gnt_bt debug signal */
	halwifionly_phy_set_bb_reg(wifionlycfg, 0x70, 0xff000000, 0x0e);
	/*gnt_wl=1 , gnt_bt=0*/
	halwifionly_phy_set_bb_reg(wifionlycfg, 0x1704, 0xffffffff, 0x7700);
	halwifionly_phy_set_bb_reg(wifionlycfg, 0x1700, 0xffffffff, 0xc00f0038);
}