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
struct inno_hdmi_phy {int chip_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  RK3228_BYPASS_PDATA_EN ; 
 int RK3228_BYPASS_PLLPD_EN ; 
 int RK3228_BYPASS_PWRON_EN ; 
 int RK3228_BYPASS_RXSENSE_EN ; 
 int /*<<< orphan*/  RK3228_POST_PLL_CTRL_MANUAL ; 
 int /*<<< orphan*/  inno_update_bits (struct inno_hdmi_phy*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inno_write (struct inno_hdmi_phy*,int,int) ; 

__attribute__((used)) static int inno_hdmi_phy_rk3228_init(struct inno_hdmi_phy *inno)
{
	/*
	 * Use phy internal register control
	 * rxsense/poweron/pllpd/pdataen signal.
	 */
	inno_write(inno, 0x01, RK3228_BYPASS_RXSENSE_EN |
		   RK3228_BYPASS_PWRON_EN |
		   RK3228_BYPASS_PLLPD_EN);
	inno_update_bits(inno, 0x02, RK3228_BYPASS_PDATA_EN,
			 RK3228_BYPASS_PDATA_EN);

	/* manual power down post-PLL */
	inno_update_bits(inno, 0xaa, RK3228_POST_PLL_CTRL_MANUAL,
			 RK3228_POST_PLL_CTRL_MANUAL);

	inno->chip_version = 1;

	return 0;
}