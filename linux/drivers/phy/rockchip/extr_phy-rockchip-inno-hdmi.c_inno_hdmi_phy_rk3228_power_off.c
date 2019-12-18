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
struct inno_hdmi_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RK3228_BANDGAP_ENABLE ; 
 int /*<<< orphan*/  RK3228_POST_PLL_POWER_DOWN ; 
 int /*<<< orphan*/  RK3228_TMDS_DRIVER_ENABLE ; 
 int /*<<< orphan*/  inno_update_bits (struct inno_hdmi_phy*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void inno_hdmi_phy_rk3228_power_off(struct inno_hdmi_phy *inno)
{
	inno_update_bits(inno, 0xe1, RK3228_TMDS_DRIVER_ENABLE, 0);
	inno_update_bits(inno, 0xe1, RK3228_BANDGAP_ENABLE, 0);
	inno_update_bits(inno, 0xe0, RK3228_POST_PLL_POWER_DOWN,
			 RK3228_POST_PLL_POWER_DOWN);
}