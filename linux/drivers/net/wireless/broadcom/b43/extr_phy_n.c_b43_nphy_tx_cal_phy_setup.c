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
struct b43_phy {int rev; struct b43_phy_n* n; } ;
struct b43_wldev {int /*<<< orphan*/  wl; struct b43_phy phy; } ;
struct b43_phy_n {int* tx_rx_cal_phy_saveregs; scalar_t__ use_int_tx_iq_lo_cal; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_NPHY_AFECTL_C1 ; 
 int /*<<< orphan*/  B43_NPHY_AFECTL_C2 ; 
 int /*<<< orphan*/  B43_NPHY_AFECTL_OVER ; 
 int /*<<< orphan*/  B43_NPHY_AFECTL_OVER1 ; 
 int /*<<< orphan*/  B43_NPHY_BBCFG ; 
 int B43_NPHY_BBCFG_RSTRX ; 
 int /*<<< orphan*/  B43_NPHY_PAPD_EN0 ; 
 int /*<<< orphan*/  B43_NPHY_PAPD_EN1 ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_INTC1 ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_INTC2 ; 
 int /*<<< orphan*/  B43_NTAB16 (int,int) ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  N_INTC_OVERRIDE_PA ; 
 int /*<<< orphan*/  N_INTC_OVERRIDE_TRSW ; 
 int /*<<< orphan*/  R2057_IPA5G_CASCOFFV_PU_CORE0 ; 
 int /*<<< orphan*/  R2057_IPA5G_CASCOFFV_PU_CORE1 ; 
 int /*<<< orphan*/  R2057_OVR_REG0 ; 
 int /*<<< orphan*/  R2057_PAD2G_TUNE_PUS_CORE0 ; 
 int /*<<< orphan*/  R2057_PAD2G_TUNE_PUS_CORE1 ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int b43_nphy_read_lpf_ctl (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_nphy_rf_ctl_intc_override (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  b43_nphy_rf_ctl_override_rev19 (struct b43_wldev*,int,int,int,int,int) ; 
 int /*<<< orphan*/  b43_nphy_rf_ctl_override_rev7 (struct b43_wldev*,int,int,int,int,int) ; 
 int b43_ntab_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_ntab_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void b43_nphy_tx_cal_phy_setup(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_n *nphy = dev->phy.n;
	u16 *regs = dev->phy.n->tx_rx_cal_phy_saveregs;
	u16 tmp;

	regs[0] = b43_phy_read(dev, B43_NPHY_AFECTL_C1);
	regs[1] = b43_phy_read(dev, B43_NPHY_AFECTL_C2);
	if (dev->phy.rev >= 3) {
		b43_phy_maskset(dev, B43_NPHY_AFECTL_C1, 0xF0FF, 0x0A00);
		b43_phy_maskset(dev, B43_NPHY_AFECTL_C2, 0xF0FF, 0x0A00);

		tmp = b43_phy_read(dev, B43_NPHY_AFECTL_OVER1);
		regs[2] = tmp;
		b43_phy_write(dev, B43_NPHY_AFECTL_OVER1, tmp | 0x0600);

		tmp = b43_phy_read(dev, B43_NPHY_AFECTL_OVER);
		regs[3] = tmp;
		b43_phy_write(dev, B43_NPHY_AFECTL_OVER, tmp | 0x0600);

		regs[4] = b43_phy_read(dev, B43_NPHY_BBCFG);
		b43_phy_mask(dev, B43_NPHY_BBCFG,
			     ~B43_NPHY_BBCFG_RSTRX & 0xFFFF);

		tmp = b43_ntab_read(dev, B43_NTAB16(8, 3));
		regs[5] = tmp;
		b43_ntab_write(dev, B43_NTAB16(8, 3), 0);

		tmp = b43_ntab_read(dev, B43_NTAB16(8, 19));
		regs[6] = tmp;
		b43_ntab_write(dev, B43_NTAB16(8, 19), 0);
		regs[7] = b43_phy_read(dev, B43_NPHY_RFCTL_INTC1);
		regs[8] = b43_phy_read(dev, B43_NPHY_RFCTL_INTC2);

		if (!nphy->use_int_tx_iq_lo_cal)
			b43_nphy_rf_ctl_intc_override(dev, N_INTC_OVERRIDE_PA,
						      1, 3);
		else
			b43_nphy_rf_ctl_intc_override(dev, N_INTC_OVERRIDE_PA,
						      0, 3);
		b43_nphy_rf_ctl_intc_override(dev, N_INTC_OVERRIDE_TRSW, 2, 1);
		b43_nphy_rf_ctl_intc_override(dev, N_INTC_OVERRIDE_TRSW, 8, 2);

		regs[9] = b43_phy_read(dev, B43_NPHY_PAPD_EN0);
		regs[10] = b43_phy_read(dev, B43_NPHY_PAPD_EN1);
		b43_phy_mask(dev, B43_NPHY_PAPD_EN0, ~0x0001);
		b43_phy_mask(dev, B43_NPHY_PAPD_EN1, ~0x0001);

		tmp = b43_nphy_read_lpf_ctl(dev, 0);
		if (phy->rev >= 19)
			b43_nphy_rf_ctl_override_rev19(dev, 0x80, tmp, 0, false,
						       1);
		else if (phy->rev >= 7)
			b43_nphy_rf_ctl_override_rev7(dev, 0x80, tmp, 0, false,
						      1);

		if (nphy->use_int_tx_iq_lo_cal && true /* FIXME */) {
			if (phy->rev >= 19) {
				b43_nphy_rf_ctl_override_rev19(dev, 0x8, 0, 0x3,
							       false, 0);
			} else if (phy->rev >= 8) {
				b43_nphy_rf_ctl_override_rev7(dev, 0x8, 0, 0x3,
							      false, 0);
			} else if (phy->rev == 7) {
				b43_radio_maskset(dev, R2057_OVR_REG0, 1 << 4, 1 << 4);
				if (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) {
					b43_radio_maskset(dev, R2057_PAD2G_TUNE_PUS_CORE0, ~1, 0);
					b43_radio_maskset(dev, R2057_PAD2G_TUNE_PUS_CORE1, ~1, 0);
				} else {
					b43_radio_maskset(dev, R2057_IPA5G_CASCOFFV_PU_CORE0, ~1, 0);
					b43_radio_maskset(dev, R2057_IPA5G_CASCOFFV_PU_CORE1, ~1, 0);
				}
			}
		}
	} else {
		b43_phy_maskset(dev, B43_NPHY_AFECTL_C1, 0x0FFF, 0xA000);
		b43_phy_maskset(dev, B43_NPHY_AFECTL_C2, 0x0FFF, 0xA000);
		tmp = b43_phy_read(dev, B43_NPHY_AFECTL_OVER);
		regs[2] = tmp;
		b43_phy_write(dev, B43_NPHY_AFECTL_OVER, tmp | 0x3000);
		tmp = b43_ntab_read(dev, B43_NTAB16(8, 2));
		regs[3] = tmp;
		tmp |= 0x2000;
		b43_ntab_write(dev, B43_NTAB16(8, 2), tmp);
		tmp = b43_ntab_read(dev, B43_NTAB16(8, 18));
		regs[4] = tmp;
		tmp |= 0x2000;
		b43_ntab_write(dev, B43_NTAB16(8, 18), tmp);
		regs[5] = b43_phy_read(dev, B43_NPHY_RFCTL_INTC1);
		regs[6] = b43_phy_read(dev, B43_NPHY_RFCTL_INTC2);
		if (b43_current_band(dev->wl) == NL80211_BAND_5GHZ)
			tmp = 0x0180;
		else
			tmp = 0x0120;
		b43_phy_write(dev, B43_NPHY_RFCTL_INTC1, tmp);
		b43_phy_write(dev, B43_NPHY_RFCTL_INTC2, tmp);
	}
}