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
typedef  int u16 ;
struct brcms_phy {TYPE_1__* sh; int /*<<< orphan*/  d11core; } ;
typedef  int s16 ;
struct TYPE_2__ {int /*<<< orphan*/  physhim; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int MCTL_EN_MAC ; 
 int /*<<< orphan*/  TEMPSENSE ; 
 int bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maccontrol ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wlapi_enable_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlapi_suspend_mac_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_vbat_temp_sense_setup (struct brcms_phy*,int /*<<< orphan*/ ) ; 

s16 wlc_lcnphy_tempsense_new(struct brcms_phy *pi, bool mode)
{
	u16 tempsenseval1, tempsenseval2;
	s16 avg = 0;
	bool suspend = false;

	if (mode == 1) {
		suspend = (0 == (bcma_read32(pi->d11core,
					     D11REGOFFS(maccontrol)) &
				 MCTL_EN_MAC));
		if (!suspend)
			wlapi_suspend_mac_and_wait(pi->sh->physhim);
		wlc_lcnphy_vbat_temp_sense_setup(pi, TEMPSENSE);
	}
	tempsenseval1 = read_phy_reg(pi, 0x476) & 0x1FF;
	tempsenseval2 = read_phy_reg(pi, 0x477) & 0x1FF;

	if (tempsenseval1 > 255)
		avg = (s16) (tempsenseval1 - 512);
	else
		avg = (s16) tempsenseval1;

	if (tempsenseval2 > 255)
		avg += (s16) (tempsenseval2 - 512);
	else
		avg += (s16) tempsenseval2;

	avg /= 2;

	if (mode == 1) {

		mod_phy_reg(pi, 0x448, (0x1 << 14), (1) << 14);

		udelay(100);
		mod_phy_reg(pi, 0x448, (0x1 << 14), (0) << 14);

		if (!suspend)
			wlapi_enable_mac(pi->sh->physhim);
	}
	return avg;
}