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
 int /*<<< orphan*/  RK3328_BANDGAP_ENABLE ; 
 int /*<<< orphan*/  RK3328_POST_PLL_POWER_DOWN ; 
 int /*<<< orphan*/  RK3328_TMDS_DRIVER_ENABLE ; 
 int /*<<< orphan*/  inno_update_bits (struct inno_hdmi_phy*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inno_write (struct inno_hdmi_phy*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void inno_hdmi_phy_rk3328_power_off(struct inno_hdmi_phy *inno)
{
	inno_update_bits(inno, 0xb2, RK3328_TMDS_DRIVER_ENABLE, 0);
	inno_update_bits(inno, 0xb0, RK3328_BANDGAP_ENABLE, 0);
	inno_update_bits(inno, 0xaa, RK3328_POST_PLL_POWER_DOWN,
			 RK3328_POST_PLL_POWER_DOWN);

	/* Disable PHY IRQ */
	inno_write(inno, 0x05, 0);
	inno_write(inno, 0x07, 0);
}