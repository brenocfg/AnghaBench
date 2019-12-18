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
typedef  int u8 ;
typedef  int u16 ;
struct ieee80211_channel {int hw_value; scalar_t__ band; } ;
struct b43_phy {int rev; struct b43_phy_n* n; } ;
struct b43_wldev {struct b43_phy phy; TYPE_1__* dev; } ;
struct b43_phy_n_sfo_cfg {int dummy; } ;
struct b43_phy_n {scalar_t__ spur_avoid; scalar_t__ aband_spurwar_en; int /*<<< orphan*/  txpwrctrl; } ;
struct TYPE_2__ {int chip_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_MMIO_PSM_PHY_HDR ; 
 int /*<<< orphan*/  B43_NPHY_BANDCTL ; 
 int B43_NPHY_BANDCTL_5GHZ ; 
 int /*<<< orphan*/  B43_NPHY_BBCFG ; 
 int B43_NPHY_BBCFG_RSTRX ; 
 int /*<<< orphan*/  B43_NPHY_NDATAT_DUP40 ; 
 int /*<<< orphan*/  B43_PHY_B_BBCFG ; 
 int B43_PHY_B_BBCFG_RSTCCA ; 
 int B43_PHY_B_BBCFG_RSTRX ; 
 int /*<<< orphan*/  B43_PHY_B_TEST ; 
 scalar_t__ B43_SPUR_AVOID_DISABLE ; 
 scalar_t__ B43_SPUR_AVOID_FORCE ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  b43_chantab_phy_upload (struct b43_wldev*,struct b43_phy_n_sfo_cfg const*) ; 
 int /*<<< orphan*/  b43_is_40mhz (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_mac_switch_freq (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_nphy_adjust_lna_gain_table (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_classifier (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_nphy_pmu_spur_avoid (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_nphy_reset_cca (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_spur_workaround (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_tx_lpf_bw (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_tx_power_fix (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int b43_read16 (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_wireless_core_phy_pll_reset (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43_nphy_channel_setup(struct b43_wldev *dev,
				const struct b43_phy_n_sfo_cfg *e,
				struct ieee80211_channel *new_channel)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_n *nphy = dev->phy.n;
	int ch = new_channel->hw_value;
	u16 tmp16;

	if (new_channel->band == NL80211_BAND_5GHZ) {
		/* Switch to 2 GHz for a moment to access B43_PHY_B_BBCFG */
		b43_phy_mask(dev, B43_NPHY_BANDCTL, ~B43_NPHY_BANDCTL_5GHZ);

		tmp16 = b43_read16(dev, B43_MMIO_PSM_PHY_HDR);
		b43_write16(dev, B43_MMIO_PSM_PHY_HDR, tmp16 | 4);
		/* Put BPHY in the reset */
		b43_phy_set(dev, B43_PHY_B_BBCFG,
			    B43_PHY_B_BBCFG_RSTCCA | B43_PHY_B_BBCFG_RSTRX);
		b43_write16(dev, B43_MMIO_PSM_PHY_HDR, tmp16);
		b43_phy_set(dev, B43_NPHY_BANDCTL, B43_NPHY_BANDCTL_5GHZ);
	} else if (new_channel->band == NL80211_BAND_2GHZ) {
		b43_phy_mask(dev, B43_NPHY_BANDCTL, ~B43_NPHY_BANDCTL_5GHZ);
		tmp16 = b43_read16(dev, B43_MMIO_PSM_PHY_HDR);
		b43_write16(dev, B43_MMIO_PSM_PHY_HDR, tmp16 | 4);
		/* Take BPHY out of the reset */
		b43_phy_mask(dev, B43_PHY_B_BBCFG,
			     (u16)~(B43_PHY_B_BBCFG_RSTCCA | B43_PHY_B_BBCFG_RSTRX));
		b43_write16(dev, B43_MMIO_PSM_PHY_HDR, tmp16);
	}

	b43_chantab_phy_upload(dev, e);

	if (new_channel->hw_value == 14) {
		b43_nphy_classifier(dev, 2, 0);
		b43_phy_set(dev, B43_PHY_B_TEST, 0x0800);
	} else {
		b43_nphy_classifier(dev, 2, 2);
		if (new_channel->band == NL80211_BAND_2GHZ)
			b43_phy_mask(dev, B43_PHY_B_TEST, ~0x840);
	}

	if (!nphy->txpwrctrl)
		b43_nphy_tx_power_fix(dev);

	if (dev->phy.rev < 3)
		b43_nphy_adjust_lna_gain_table(dev);

	b43_nphy_tx_lpf_bw(dev);

	if (dev->phy.rev >= 3 &&
	    dev->phy.n->spur_avoid != B43_SPUR_AVOID_DISABLE) {
		u8 spuravoid = 0;

		if (dev->phy.n->spur_avoid == B43_SPUR_AVOID_FORCE) {
			spuravoid = 1;
		} else if (phy->rev >= 19) {
			/* TODO */
		} else if (phy->rev >= 18) {
			/* TODO */
		} else if (phy->rev >= 17) {
			/* TODO: Off for channels 1-11, but check 12-14! */
		} else if (phy->rev >= 16) {
			/* TODO: Off for 2 GHz, but check 5 GHz! */
		} else if (phy->rev >= 7) {
			if (!b43_is_40mhz(dev)) { /* 20MHz */
				if (ch == 13 || ch == 14 || ch == 153)
					spuravoid = 1;
			} else { /* 40 MHz */
				if (ch == 54)
					spuravoid = 1;
			}
		} else {
			if (!b43_is_40mhz(dev)) { /* 20MHz */
				if ((ch >= 5 && ch <= 8) || ch == 13 || ch == 14)
					spuravoid = 1;
			} else { /* 40MHz */
				if (nphy->aband_spurwar_en &&
				    (ch == 38 || ch == 102 || ch == 118))
					spuravoid = dev->dev->chip_id == 0x4716;
			}
		}

		b43_nphy_pmu_spur_avoid(dev, spuravoid);

		b43_mac_switch_freq(dev, spuravoid);

		if (dev->phy.rev == 3 || dev->phy.rev == 4)
			b43_wireless_core_phy_pll_reset(dev);

		if (spuravoid)
			b43_phy_set(dev, B43_NPHY_BBCFG, B43_NPHY_BBCFG_RSTRX);
		else
			b43_phy_mask(dev, B43_NPHY_BBCFG,
				     ~B43_NPHY_BBCFG_RSTRX & 0xFFFF);

		b43_nphy_reset_cca(dev);

		/* wl sets useless phy_isspuravoid here */
	}

	b43_phy_write(dev, B43_NPHY_NDATAT_DUP40, 0x3830);

	if (phy->rev >= 3)
		b43_nphy_spur_workaround(dev);
}