#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_12__ {scalar_t__ tssipos; } ;
struct TYPE_13__ {TYPE_5__ ghz2; } ;
struct ssb_sprom {int revision; TYPE_6__ fem; TYPE_3__* core_pwr_info; } ;
struct b43_phy {int rev; TYPE_2__* chandef; struct b43_phy_n* n; } ;
struct b43_wldev {struct b43_phy phy; TYPE_7__* dev; int /*<<< orphan*/  wl; } ;
struct b43_phy_n {int* adj_pwr_tbl; scalar_t__ hang_avoid; int /*<<< orphan*/  tx_pwr_max_ppr; TYPE_4__* pwr_ctl_info; } ;
typedef  int s8 ;
typedef  int s32 ;
typedef  int s16 ;
struct TYPE_14__ {int core_rev; struct ssb_sprom* bus_sprom; } ;
struct TYPE_11__ {int idle_tssi_2g; int idle_tssi_5g; } ;
struct TYPE_10__ {int maxpwr_2g; int* pa_2g; int maxpwr_5gl; int* pa_5gl; int maxpwr_5g; int* pa_5g; int maxpwr_5gh; int* pa_5gh; } ;
struct TYPE_9__ {TYPE_1__* chan; } ;
struct TYPE_8__ {int center_freq; } ;

/* Variables and functions */
 int B2056_TX0 ; 
 int B2056_TX1 ; 
 int B2056_TX_TX_SSI_MUX ; 
 int /*<<< orphan*/  B43_MMIO_MACCTL ; 
 int /*<<< orphan*/  B43_NPHY_TSSIMODE ; 
 int B43_NPHY_TSSIMODE_EN ; 
 int /*<<< orphan*/  B43_NPHY_TXPCTL_CMD ; 
 int /*<<< orphan*/  B43_NPHY_TXPCTL_CMD_INIT ; 
 int B43_NPHY_TXPCTL_CMD_PCTLEN ; 
 int /*<<< orphan*/  B43_NPHY_TXPCTL_INIT ; 
 int /*<<< orphan*/  B43_NPHY_TXPCTL_INIT_PIDXI1 ; 
 int /*<<< orphan*/  B43_NPHY_TXPCTL_ITSSI ; 
 int B43_NPHY_TXPCTL_ITSSI_0_SHIFT ; 
 int B43_NPHY_TXPCTL_ITSSI_1_SHIFT ; 
 int B43_NPHY_TXPCTL_ITSSI_BINF ; 
 int /*<<< orphan*/  B43_NPHY_TXPCTL_N ; 
 int B43_NPHY_TXPCTL_N_NPTIL2_SHIFT ; 
 int B43_NPHY_TXPCTL_N_TSSID_SHIFT ; 
 int /*<<< orphan*/  B43_NPHY_TXPCTL_TPWR ; 
 int B43_NPHY_TXPCTL_TPWR_0_SHIFT ; 
 int B43_NPHY_TXPCTL_TPWR_1_SHIFT ; 
 int /*<<< orphan*/  B43_NTAB16 (int,int) ; 
 int /*<<< orphan*/  B43_NTAB32 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_maskset32 (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ b43_nphy_ipa (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_stay_in_carrier_search (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_nphy_tx_prepare_adjusted_power_table (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_ntab_write_bulk (struct b43_wldev*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int b43_ppr_get_max (struct b43_wldev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_read32 (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void b43_nphy_tx_power_ctl_setup(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_n *nphy = dev->phy.n;
	struct ssb_sprom *sprom = dev->dev->bus_sprom;

	s16 a1[2], b0[2], b1[2];
	u8 idle[2];
	u8 ppr_max;
	s8 target[2];
	s32 num, den, pwr;
	u32 regval[64];

	u16 freq = phy->chandef->chan->center_freq;
	u16 tmp;
	u16 r; /* routing */
	u8 i, c;

	if (dev->dev->core_rev == 11 || dev->dev->core_rev == 12) {
		b43_maskset32(dev, B43_MMIO_MACCTL, ~0, 0x200000);
		b43_read32(dev, B43_MMIO_MACCTL);
		udelay(1);
	}

	if (nphy->hang_avoid)
		b43_nphy_stay_in_carrier_search(dev, true);

	b43_phy_set(dev, B43_NPHY_TSSIMODE, B43_NPHY_TSSIMODE_EN);
	if (dev->phy.rev >= 3)
		b43_phy_mask(dev, B43_NPHY_TXPCTL_CMD,
			     ~B43_NPHY_TXPCTL_CMD_PCTLEN & 0xFFFF);
	else
		b43_phy_set(dev, B43_NPHY_TXPCTL_CMD,
			    B43_NPHY_TXPCTL_CMD_PCTLEN);

	if (dev->dev->core_rev == 11 || dev->dev->core_rev == 12)
		b43_maskset32(dev, B43_MMIO_MACCTL, ~0x200000, 0);

	if (sprom->revision < 4) {
		idle[0] = nphy->pwr_ctl_info[0].idle_tssi_2g;
		idle[1] = nphy->pwr_ctl_info[1].idle_tssi_2g;
		target[0] = target[1] = 52;
		a1[0] = a1[1] = -424;
		b0[0] = b0[1] = 5612;
		b1[0] = b1[1] = -1393;
	} else {
		if (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) {
			for (c = 0; c < 2; c++) {
				idle[c] = nphy->pwr_ctl_info[c].idle_tssi_2g;
				target[c] = sprom->core_pwr_info[c].maxpwr_2g;
				a1[c] = sprom->core_pwr_info[c].pa_2g[0];
				b0[c] = sprom->core_pwr_info[c].pa_2g[1];
				b1[c] = sprom->core_pwr_info[c].pa_2g[2];
			}
		} else if (freq >= 4900 && freq < 5100) {
			for (c = 0; c < 2; c++) {
				idle[c] = nphy->pwr_ctl_info[c].idle_tssi_5g;
				target[c] = sprom->core_pwr_info[c].maxpwr_5gl;
				a1[c] = sprom->core_pwr_info[c].pa_5gl[0];
				b0[c] = sprom->core_pwr_info[c].pa_5gl[1];
				b1[c] = sprom->core_pwr_info[c].pa_5gl[2];
			}
		} else if (freq >= 5100 && freq < 5500) {
			for (c = 0; c < 2; c++) {
				idle[c] = nphy->pwr_ctl_info[c].idle_tssi_5g;
				target[c] = sprom->core_pwr_info[c].maxpwr_5g;
				a1[c] = sprom->core_pwr_info[c].pa_5g[0];
				b0[c] = sprom->core_pwr_info[c].pa_5g[1];
				b1[c] = sprom->core_pwr_info[c].pa_5g[2];
			}
		} else if (freq >= 5500) {
			for (c = 0; c < 2; c++) {
				idle[c] = nphy->pwr_ctl_info[c].idle_tssi_5g;
				target[c] = sprom->core_pwr_info[c].maxpwr_5gh;
				a1[c] = sprom->core_pwr_info[c].pa_5gh[0];
				b0[c] = sprom->core_pwr_info[c].pa_5gh[1];
				b1[c] = sprom->core_pwr_info[c].pa_5gh[2];
			}
		} else {
			idle[0] = nphy->pwr_ctl_info[0].idle_tssi_5g;
			idle[1] = nphy->pwr_ctl_info[1].idle_tssi_5g;
			target[0] = target[1] = 52;
			a1[0] = a1[1] = -424;
			b0[0] = b0[1] = 5612;
			b1[0] = b1[1] = -1393;
		}
	}

	ppr_max = b43_ppr_get_max(dev, &nphy->tx_pwr_max_ppr);
	if (ppr_max) {
		target[0] = ppr_max;
		target[1] = ppr_max;
	}

	if (dev->phy.rev >= 3) {
		if (sprom->fem.ghz2.tssipos)
			b43_phy_set(dev, B43_NPHY_TXPCTL_ITSSI, 0x4000);
		if (dev->phy.rev >= 7) {
			for (c = 0; c < 2; c++) {
				r = c ? 0x190 : 0x170;
				if (b43_nphy_ipa(dev))
					b43_radio_write(dev, r + 0x9, (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) ? 0xE : 0xC);
			}
		} else {
			if (b43_nphy_ipa(dev)) {
				tmp = (b43_current_band(dev->wl) == NL80211_BAND_5GHZ) ? 0xC : 0xE;
				b43_radio_write(dev,
					B2056_TX0 | B2056_TX_TX_SSI_MUX, tmp);
				b43_radio_write(dev,
					B2056_TX1 | B2056_TX_TX_SSI_MUX, tmp);
			} else {
				b43_radio_write(dev,
					B2056_TX0 | B2056_TX_TX_SSI_MUX, 0x11);
				b43_radio_write(dev,
					B2056_TX1 | B2056_TX_TX_SSI_MUX, 0x11);
			}
		}
	}

	if (dev->dev->core_rev == 11 || dev->dev->core_rev == 12) {
		b43_maskset32(dev, B43_MMIO_MACCTL, ~0, 0x200000);
		b43_read32(dev, B43_MMIO_MACCTL);
		udelay(1);
	}

	if (phy->rev >= 19) {
		/* TODO */
	} else if (phy->rev >= 7) {
		b43_phy_maskset(dev, B43_NPHY_TXPCTL_CMD,
				~B43_NPHY_TXPCTL_CMD_INIT, 0x19);
		b43_phy_maskset(dev, B43_NPHY_TXPCTL_INIT,
				~B43_NPHY_TXPCTL_INIT_PIDXI1, 0x19);
	} else {
		b43_phy_maskset(dev, B43_NPHY_TXPCTL_CMD,
				~B43_NPHY_TXPCTL_CMD_INIT, 0x40);
		if (dev->phy.rev > 1)
			b43_phy_maskset(dev, B43_NPHY_TXPCTL_INIT,
				~B43_NPHY_TXPCTL_INIT_PIDXI1, 0x40);
	}

	if (dev->dev->core_rev == 11 || dev->dev->core_rev == 12)
		b43_maskset32(dev, B43_MMIO_MACCTL, ~0x200000, 0);

	b43_phy_write(dev, B43_NPHY_TXPCTL_N,
		      0xF0 << B43_NPHY_TXPCTL_N_TSSID_SHIFT |
		      3 << B43_NPHY_TXPCTL_N_NPTIL2_SHIFT);
	b43_phy_write(dev, B43_NPHY_TXPCTL_ITSSI,
		      idle[0] << B43_NPHY_TXPCTL_ITSSI_0_SHIFT |
		      idle[1] << B43_NPHY_TXPCTL_ITSSI_1_SHIFT |
		      B43_NPHY_TXPCTL_ITSSI_BINF);
	b43_phy_write(dev, B43_NPHY_TXPCTL_TPWR,
		      target[0] << B43_NPHY_TXPCTL_TPWR_0_SHIFT |
		      target[1] << B43_NPHY_TXPCTL_TPWR_1_SHIFT);

	for (c = 0; c < 2; c++) {
		for (i = 0; i < 64; i++) {
			num = 8 * (16 * b0[c] + b1[c] * i);
			den = 32768 + a1[c] * i;
			pwr = max((4 * num + den / 2) / den, -8);
			if (dev->phy.rev < 3 && (i <= (31 - idle[c] + 1)))
				pwr = max(pwr, target[c] + 1);
			regval[i] = pwr;
		}
		b43_ntab_write_bulk(dev, B43_NTAB32(26 + c, 0), 64, regval);
	}

	b43_nphy_tx_prepare_adjusted_power_table(dev);
	b43_ntab_write_bulk(dev, B43_NTAB16(26, 64), 84, nphy->adj_pwr_tbl);
	b43_ntab_write_bulk(dev, B43_NTAB16(27, 64), 84, nphy->adj_pwr_tbl);

	if (nphy->hang_avoid)
		b43_nphy_stay_in_carrier_search(dev, false);
}