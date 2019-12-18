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
struct b43_phy {int radio_rev; struct b43_phy_n* n; } ;
struct b43_wldev {int /*<<< orphan*/  wl; struct b43_phy phy; } ;
struct b43_phy_n {int* tx_rx_cal_radio_saveregs; scalar_t__ use_int_tx_iq_lo_cal; } ;

/* Variables and functions */
 scalar_t__ NL80211_BAND_5GHZ ; 
 scalar_t__ R2057_TX0_IQCAL_IDAC ; 
 scalar_t__ R2057_TX0_IQCAL_VCM_HG ; 
 scalar_t__ R2057_TX0_TSSIA ; 
 scalar_t__ R2057_TX0_TSSIG ; 
 scalar_t__ R2057_TX0_TSSI_MISC1 ; 
 scalar_t__ R2057_TX0_TSSI_VCM ; 
 scalar_t__ R2057_TX0_TX_SSI_MASTER ; 
 scalar_t__ R2057_TX0_TX_SSI_MUX ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int b43_radio_read (struct b43_wldev*,scalar_t__) ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,scalar_t__,int) ; 

__attribute__((used)) static void b43_nphy_tx_cal_radio_setup_rev7(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_n *nphy = dev->phy.n;
	u16 *save = nphy->tx_rx_cal_radio_saveregs;
	int core, off;
	u16 r, tmp;

	for (core = 0; core < 2; core++) {
		r = core ? 0x20 : 0;
		off = core * 11;

		save[off + 0] = b43_radio_read(dev, r + R2057_TX0_TX_SSI_MASTER);
		save[off + 1] = b43_radio_read(dev, r + R2057_TX0_IQCAL_VCM_HG);
		save[off + 2] = b43_radio_read(dev, r + R2057_TX0_IQCAL_IDAC);
		save[off + 3] = b43_radio_read(dev, r + R2057_TX0_TSSI_VCM);
		save[off + 4] = 0;
		save[off + 5] = b43_radio_read(dev, r + R2057_TX0_TX_SSI_MUX);
		if (phy->radio_rev != 5)
			save[off + 6] = b43_radio_read(dev, r + R2057_TX0_TSSIA);
		save[off + 7] = b43_radio_read(dev, r + R2057_TX0_TSSIG);
		save[off + 8] = b43_radio_read(dev, r + R2057_TX0_TSSI_MISC1);

		if (b43_current_band(dev->wl) == NL80211_BAND_5GHZ) {
			b43_radio_write(dev, r + R2057_TX0_TX_SSI_MASTER, 0xA);
			b43_radio_write(dev, r + R2057_TX0_IQCAL_VCM_HG, 0x43);
			b43_radio_write(dev, r + R2057_TX0_IQCAL_IDAC, 0x55);
			b43_radio_write(dev, r + R2057_TX0_TSSI_VCM, 0);
			b43_radio_write(dev, r + R2057_TX0_TSSIG, 0);
			if (nphy->use_int_tx_iq_lo_cal) {
				b43_radio_write(dev, r + R2057_TX0_TX_SSI_MUX, 0x4);
				tmp = true ? 0x31 : 0x21; /* TODO */
				b43_radio_write(dev, r + R2057_TX0_TSSIA, tmp);
			}
			b43_radio_write(dev, r + R2057_TX0_TSSI_MISC1, 0x00);
		} else {
			b43_radio_write(dev, r + R2057_TX0_TX_SSI_MASTER, 0x6);
			b43_radio_write(dev, r + R2057_TX0_IQCAL_VCM_HG, 0x43);
			b43_radio_write(dev, r + R2057_TX0_IQCAL_IDAC, 0x55);
			b43_radio_write(dev, r + R2057_TX0_TSSI_VCM, 0);

			if (phy->radio_rev != 5)
				b43_radio_write(dev, r + R2057_TX0_TSSIA, 0);
			if (nphy->use_int_tx_iq_lo_cal) {
				b43_radio_write(dev, r + R2057_TX0_TX_SSI_MUX, 0x6);
				tmp = true ? 0x31 : 0x21; /* TODO */
				b43_radio_write(dev, r + R2057_TX0_TSSIG, tmp);
			}
			b43_radio_write(dev, r + R2057_TX0_TSSI_MISC1, 0);
		}
	}
}