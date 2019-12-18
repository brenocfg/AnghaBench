#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct b43_phy {int rev; int radio_rev; scalar_t__ gmode; struct b43_phy_g* g; } ;
struct b43_wldev {TYPE_3__* dev; struct b43_phy phy; } ;
struct b43_phy_g {int initval; int* nrssi; TYPE_1__* lo_control; } ;
struct TYPE_6__ {int chip_id; int chip_pkg; TYPE_2__* bus_sprom; } ;
struct TYPE_5__ {int boardflags_lo; } ;
struct TYPE_4__ {int tx_bias; int tx_magn; } ;

/* Variables and functions */
 int B43_BFL_PACTRL ; 
 int B43_BFL_RSSI ; 
 int B43_PHYVER_VERSION ; 
 int /*<<< orphan*/  B43_PHY_ANALOGOVER ; 
 int /*<<< orphan*/  B43_PHY_ANALOGOVERVAL ; 
 int /*<<< orphan*/  B43_PHY_CCK (int) ; 
 int /*<<< orphan*/  B43_PHY_CRS0 ; 
 int /*<<< orphan*/  B43_PHY_EXTG (int) ; 
 int /*<<< orphan*/  B43_PHY_LO_MASK ; 
 int /*<<< orphan*/  B43_PHY_OFDM (int) ; 
 int /*<<< orphan*/  B43_PHY_PGACTL ; 
 int /*<<< orphan*/  B43_PHY_RFOVER ; 
 int /*<<< orphan*/  B43_PHY_VERSION_OFDM ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  b43_calc_loopback_gain (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_calc_nrssi_slope (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_calc_nrssi_threshold (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_lo_g_adjust (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_lo_g_init (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nrssi_hw_update (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_phy_init_pctl (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_inita (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_initb5 (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_initb6 (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int b43_radio_init2050 (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_radio_maskset (struct b43_wldev*,int,int,int) ; 
 int b43_radio_read16 (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_radio_write16 (struct b43_wldev*,int,int) ; 
 scalar_t__ has_loopback_gain (struct b43_phy*) ; 
 scalar_t__ has_tx_magnification (struct b43_phy*) ; 

__attribute__((used)) static void b43_phy_initg(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_g *gphy = phy->g;
	u16 tmp;

	if (phy->rev == 1)
		b43_phy_initb5(dev);
	else
		b43_phy_initb6(dev);

	if (phy->rev >= 2 || phy->gmode)
		b43_phy_inita(dev);

	if (phy->rev >= 2) {
		b43_phy_write(dev, B43_PHY_ANALOGOVER, 0);
		b43_phy_write(dev, B43_PHY_ANALOGOVERVAL, 0);
	}
	if (phy->rev == 2) {
		b43_phy_write(dev, B43_PHY_RFOVER, 0);
		b43_phy_write(dev, B43_PHY_PGACTL, 0xC0);
	}
	if (phy->rev > 5) {
		b43_phy_write(dev, B43_PHY_RFOVER, 0x400);
		b43_phy_write(dev, B43_PHY_PGACTL, 0xC0);
	}
	if (phy->gmode || phy->rev >= 2) {
		tmp = b43_phy_read(dev, B43_PHY_VERSION_OFDM);
		tmp &= B43_PHYVER_VERSION;
		if (tmp == 3 || tmp == 5) {
			b43_phy_write(dev, B43_PHY_OFDM(0xC2), 0x1816);
			b43_phy_write(dev, B43_PHY_OFDM(0xC3), 0x8006);
		}
		if (tmp == 5) {
			b43_phy_maskset(dev, B43_PHY_OFDM(0xCC), 0x00FF, 0x1F00);
		}
	}
	if ((phy->rev <= 2 && phy->gmode) || phy->rev >= 2)
		b43_phy_write(dev, B43_PHY_OFDM(0x7E), 0x78);
	if (phy->radio_rev == 8) {
		b43_phy_set(dev, B43_PHY_EXTG(0x01), 0x80);
		b43_phy_set(dev, B43_PHY_OFDM(0x3E), 0x4);
	}
	if (has_loopback_gain(phy))
		b43_calc_loopback_gain(dev);

	if (phy->radio_rev != 8) {
		if (gphy->initval == 0xFFFF)
			gphy->initval = b43_radio_init2050(dev);
		else
			b43_radio_write16(dev, 0x0078, gphy->initval);
	}
	b43_lo_g_init(dev);
	if (has_tx_magnification(phy)) {
		b43_radio_write16(dev, 0x52,
				  (b43_radio_read16(dev, 0x52) & 0xFF00)
				  | gphy->lo_control->tx_bias | gphy->
				  lo_control->tx_magn);
	} else {
		b43_radio_maskset(dev, 0x52, 0xFFF0, gphy->lo_control->tx_bias);
	}
	if (phy->rev >= 6) {
		b43_phy_maskset(dev, B43_PHY_CCK(0x36), 0x0FFF, (gphy->lo_control->tx_bias << 12));
	}
	if (dev->dev->bus_sprom->boardflags_lo & B43_BFL_PACTRL)
		b43_phy_write(dev, B43_PHY_CCK(0x2E), 0x8075);
	else
		b43_phy_write(dev, B43_PHY_CCK(0x2E), 0x807F);
	if (phy->rev < 2)
		b43_phy_write(dev, B43_PHY_CCK(0x2F), 0x101);
	else
		b43_phy_write(dev, B43_PHY_CCK(0x2F), 0x202);
	if (phy->gmode || phy->rev >= 2) {
		b43_lo_g_adjust(dev);
		b43_phy_write(dev, B43_PHY_LO_MASK, 0x8078);
	}

	if (!(dev->dev->bus_sprom->boardflags_lo & B43_BFL_RSSI)) {
		/* The specs state to update the NRSSI LT with
		 * the value 0x7FFFFFFF here. I think that is some weird
		 * compiler optimization in the original driver.
		 * Essentially, what we do here is resetting all NRSSI LT
		 * entries to -32 (see the clamp_val() in nrssi_hw_update())
		 */
		b43_nrssi_hw_update(dev, 0xFFFF);	//FIXME?
		b43_calc_nrssi_threshold(dev);
	} else if (phy->gmode || phy->rev >= 2) {
		if (gphy->nrssi[0] == -1000) {
			B43_WARN_ON(gphy->nrssi[1] != -1000);
			b43_calc_nrssi_slope(dev);
		} else
			b43_calc_nrssi_threshold(dev);
	}
	if (phy->radio_rev == 8)
		b43_phy_write(dev, B43_PHY_EXTG(0x05), 0x3230);
	b43_phy_init_pctl(dev);
	/* FIXME: The spec says in the following if, the 0 should be replaced
	   'if OFDM may not be used in the current locale'
	   but OFDM is legal everywhere */
	if ((dev->dev->chip_id == 0x4306
	     && dev->dev->chip_pkg == 2) || 0) {
		b43_phy_mask(dev, B43_PHY_CRS0, 0xBFFF);
		b43_phy_mask(dev, B43_PHY_OFDM(0xC3), 0x7FFF);
	}
}