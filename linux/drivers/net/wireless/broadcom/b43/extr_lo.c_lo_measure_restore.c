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
struct lo_g_saved_values {int phy_pgactl; int phy_cck_2A; int phy_syncctl; int phy_dacctl; int radio_52; int phy_cck_30; int phy_cck_06; int phy_analogover; int phy_analogoverval; int phy_classctl; int phy_rfover; int phy_rfoverval; int phy_cck_3E; int phy_crs0; int phy_lo_mask; int phy_extg_01; int phy_dacctl_hwpctl; int phy_cck_14; int phy_hpwr_tssictl; int /*<<< orphan*/  old_channel; int /*<<< orphan*/  reg_3E2; int /*<<< orphan*/  radio_7A; int /*<<< orphan*/  radio_43; int /*<<< orphan*/  reg_3F4; } ;
struct b43_phy {int rev; scalar_t__ type; int radio_ver; int radio_rev; struct b43_phy_g* g; } ;
struct b43_wldev {struct b43_phy phy; } ;
struct b43_phy_g {int pga_gain; } ;

/* Variables and functions */
 scalar_t__ B43_PHYTYPE_B ; 
 scalar_t__ B43_PHYTYPE_G ; 
 int /*<<< orphan*/  B43_PHY_ANALOGOVER ; 
 int /*<<< orphan*/  B43_PHY_ANALOGOVERVAL ; 
 int /*<<< orphan*/  B43_PHY_CCK (int) ; 
 int /*<<< orphan*/  B43_PHY_CLASSCTL ; 
 int /*<<< orphan*/  B43_PHY_CRS0 ; 
 int /*<<< orphan*/  B43_PHY_DACCTL ; 
 int /*<<< orphan*/  B43_PHY_EXTG (int) ; 
 int /*<<< orphan*/  B43_PHY_HPWR_TSSICTL ; 
 int /*<<< orphan*/  B43_PHY_LO_MASK ; 
 int /*<<< orphan*/  B43_PHY_PGACTL ; 
 int /*<<< orphan*/  B43_PHY_RFOVER ; 
 int /*<<< orphan*/  B43_PHY_RFOVERVAL ; 
 int /*<<< orphan*/  B43_PHY_SYNCCTL ; 
 int /*<<< orphan*/  b43_gphy_channel_switch (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ b43_has_hardware_pctl (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_maskset (struct b43_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43_radio_write16 (struct b43_wldev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_write16 (struct b43_wldev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  has_tx_magnification (struct b43_phy*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void lo_measure_restore(struct b43_wldev *dev,
			       struct lo_g_saved_values *sav)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_g *gphy = phy->g;
	u16 tmp;

	if (phy->rev >= 2) {
		b43_phy_write(dev, B43_PHY_PGACTL, 0xE300);
		tmp = (gphy->pga_gain << 8);
		b43_phy_write(dev, B43_PHY_RFOVERVAL, tmp | 0xA0);
		udelay(5);
		b43_phy_write(dev, B43_PHY_RFOVERVAL, tmp | 0xA2);
		udelay(2);
		b43_phy_write(dev, B43_PHY_RFOVERVAL, tmp | 0xA3);
	} else {
		tmp = (gphy->pga_gain | 0xEFA0);
		b43_phy_write(dev, B43_PHY_PGACTL, tmp);
	}
	if (phy->type == B43_PHYTYPE_G) {
		if (phy->rev >= 3)
			b43_phy_write(dev, B43_PHY_CCK(0x2E), 0xC078);
		else
			b43_phy_write(dev, B43_PHY_CCK(0x2E), 0x8078);
		if (phy->rev >= 2)
			b43_phy_write(dev, B43_PHY_CCK(0x2F), 0x0202);
		else
			b43_phy_write(dev, B43_PHY_CCK(0x2F), 0x0101);
	}
	b43_write16(dev, 0x3F4, sav->reg_3F4);
	b43_phy_write(dev, B43_PHY_PGACTL, sav->phy_pgactl);
	b43_phy_write(dev, B43_PHY_CCK(0x2A), sav->phy_cck_2A);
	b43_phy_write(dev, B43_PHY_SYNCCTL, sav->phy_syncctl);
	b43_phy_write(dev, B43_PHY_DACCTL, sav->phy_dacctl);
	b43_radio_write16(dev, 0x43, sav->radio_43);
	b43_radio_write16(dev, 0x7A, sav->radio_7A);
	if (!has_tx_magnification(phy)) {
		tmp = sav->radio_52;
		b43_radio_maskset(dev, 0x52, 0xFF0F, tmp);
	}
	b43_write16(dev, 0x3E2, sav->reg_3E2);
	if (phy->type == B43_PHYTYPE_B &&
	    phy->radio_ver == 0x2050 && phy->radio_rev <= 5) {
		b43_phy_write(dev, B43_PHY_CCK(0x30), sav->phy_cck_30);
		b43_phy_write(dev, B43_PHY_CCK(0x06), sav->phy_cck_06);
	}
	if (phy->rev >= 2) {
		b43_phy_write(dev, B43_PHY_ANALOGOVER, sav->phy_analogover);
		b43_phy_write(dev, B43_PHY_ANALOGOVERVAL,
			      sav->phy_analogoverval);
		b43_phy_write(dev, B43_PHY_CLASSCTL, sav->phy_classctl);
		b43_phy_write(dev, B43_PHY_RFOVER, sav->phy_rfover);
		b43_phy_write(dev, B43_PHY_RFOVERVAL, sav->phy_rfoverval);
		b43_phy_write(dev, B43_PHY_CCK(0x3E), sav->phy_cck_3E);
		b43_phy_write(dev, B43_PHY_CRS0, sav->phy_crs0);
	}
	if (b43_has_hardware_pctl(dev)) {
		tmp = (sav->phy_lo_mask & 0xBFFF);
		b43_phy_write(dev, B43_PHY_LO_MASK, tmp);
		b43_phy_write(dev, B43_PHY_EXTG(0x01), sav->phy_extg_01);
		b43_phy_write(dev, B43_PHY_DACCTL, sav->phy_dacctl_hwpctl);
		b43_phy_write(dev, B43_PHY_CCK(0x14), sav->phy_cck_14);
		b43_phy_write(dev, B43_PHY_HPWR_TSSICTL, sav->phy_hpwr_tssictl);
	}
	b43_gphy_channel_switch(dev, sav->old_channel, 1);
}