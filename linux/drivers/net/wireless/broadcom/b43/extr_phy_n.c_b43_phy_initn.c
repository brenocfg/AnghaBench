#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct ssb_sprom {int boardflags_lo; int boardflags2_hi; int boardflags2_lo; } ;
struct nphy_txgains {int dummy; } ;
struct b43_phy {int rev; struct b43_phy_n* n; } ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_10__* dev; struct b43_phy phy; } ;
struct TYPE_15__ {int /*<<< orphan*/  center_freq; } ;
struct TYPE_14__ {int /*<<< orphan*/  center_freq; } ;
struct TYPE_13__ {int /*<<< orphan*/  center_freq; } ;
struct TYPE_12__ {int /*<<< orphan*/  center_freq; } ;
struct b43_phy_n {int use_int_tx_iq_lo_cal; int crsminpwr_adjusted; int noisevars_adjusted; int* papd_epsilon_offset; int txpwrctrl; int phyrxchain; scalar_t__ mphase_cal_phase_id; int measure_hold; int antsel_type; int perical; TYPE_5__* txpwrindex; int /*<<< orphan*/ * cal_orig_pwr_idx; scalar_t__ mute; TYPE_4__ iqcal_chanspec_5G; TYPE_3__ iqcal_chanspec_2G; TYPE_2__ rssical_chanspec_5G; TYPE_1__ rssical_chanspec_2G; int /*<<< orphan*/  preamble_override; scalar_t__ deaf_count; } ;
struct TYPE_20__ {TYPE_8__* bus; } ;
struct TYPE_19__ {int /*<<< orphan*/  chipco; } ;
struct TYPE_18__ {TYPE_6__* bus; } ;
struct TYPE_17__ {int /*<<< orphan*/  drv_cc; } ;
struct TYPE_16__ {int /*<<< orphan*/  index_internal; } ;
struct TYPE_11__ {int bus_type; scalar_t__ board_vendor; scalar_t__ board_type; TYPE_9__* sdev; TYPE_7__* bdev; struct ssb_sprom* bus_sprom; } ;

/* Variables and functions */
 int B43_BFH2_INTERNDET_TXIQCAL ; 
 int B43_BFL2_SKWRKFEM_BRD ; 
 int B43_BFL_EXTLNA ; 
#define  B43_BUS_BCMA 129 
#define  B43_BUS_SSB 128 
 int /*<<< orphan*/  B43_NPHY_AFECTL_OVER ; 
 int /*<<< orphan*/  B43_NPHY_AFECTL_OVER1 ; 
 int /*<<< orphan*/  B43_NPHY_AFESEQ_TX2RX_PUD_20M ; 
 int /*<<< orphan*/  B43_NPHY_AFESEQ_TX2RX_PUD_40M ; 
 int /*<<< orphan*/  B43_NPHY_BBCFG ; 
 int B43_NPHY_BBCFG_RSTCCA ; 
 int /*<<< orphan*/  B43_NPHY_BPHY_CTL3 ; 
 int B43_NPHY_BPHY_CTL3_SCALE ; 
 int B43_NPHY_BPHY_CTL3_SCALE_SHIFT ; 
 int /*<<< orphan*/  B43_NPHY_DUP40_BL ; 
 int /*<<< orphan*/  B43_NPHY_DUP40_GFBL ; 
 int /*<<< orphan*/  B43_NPHY_EPS_TABLE_ADJ0 ; 
 int /*<<< orphan*/  B43_NPHY_EPS_TABLE_ADJ1 ; 
 int /*<<< orphan*/  B43_NPHY_MIMO_CRSTXEXT ; 
 int /*<<< orphan*/  B43_NPHY_PAPD_EN0 ; 
 int /*<<< orphan*/  B43_NPHY_PAPD_EN1 ; 
 int /*<<< orphan*/  B43_NPHY_PLOAD_CSENSE_EXTLEN ; 
 int /*<<< orphan*/  B43_NPHY_REV7_RF_CTL_OVER3 ; 
 int /*<<< orphan*/  B43_NPHY_REV7_RF_CTL_OVER4 ; 
 int /*<<< orphan*/  B43_NPHY_REV7_RF_CTL_OVER5 ; 
 int /*<<< orphan*/  B43_NPHY_REV7_RF_CTL_OVER6 ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_INTC1 ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_INTC2 ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_INTC3 ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_INTC4 ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_OVER ; 
 int /*<<< orphan*/  B43_NPHY_RFSEQMODE ; 
 int B43_NPHY_RFSEQMODE_CAOVER ; 
 int B43_NPHY_RFSEQMODE_TROVER ; 
 int /*<<< orphan*/  B43_NPHY_TXF_40CO_B1S0 ; 
 int /*<<< orphan*/  B43_NPHY_TXF_40CO_B1S1 ; 
 int /*<<< orphan*/  B43_NPHY_TXF_40CO_B32S1 ; 
 int /*<<< orphan*/  B43_NPHY_TXMACDELAY ; 
 int /*<<< orphan*/  B43_NPHY_TXMACIF_HOLDOFF ; 
 int /*<<< orphan*/  B43_NPHY_TXREALFD ; 
 int /*<<< orphan*/  B43_NPHY_TXRIFS_FRDEL ; 
 int /*<<< orphan*/  B43_RFSEQ_RESET2RX ; 
 int /*<<< orphan*/  B43_RFSEQ_RX2TX ; 
 scalar_t__ BCMA_BOARD_TYPE_BCM943224M93 ; 
 int /*<<< orphan*/  BCMA_CC_CHIPCTL ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 scalar_t__ PCI_VENDOR_ID_APPLE ; 
 int /*<<< orphan*/  SSB_CHIPCO_CHIPCTL ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_mac_phy_clock_set (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_nphy_bphy_init (struct b43_wldev*) ; 
 scalar_t__ b43_nphy_cal_rx_iq (struct b43_wldev*,struct nphy_txgains,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_nphy_cal_tx_iq_lo (struct b43_wldev*,struct nphy_txgains,int,int) ; 
 int /*<<< orphan*/  b43_nphy_classifier (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_nphy_ext_pa_set_tx_dig_filters (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_force_rf_sequence (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 struct nphy_txgains b43_nphy_get_tx_gains (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_int_pa_set_tx_dig_filters (struct b43_wldev*) ; 
 scalar_t__ b43_nphy_ipa (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_pa_override (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_nphy_read_clip_detection (struct b43_wldev*,int*) ; 
 int /*<<< orphan*/  b43_nphy_restore_cal (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_restore_rssi_cal (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_rssi_cal (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_save_cal (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_set_rx_core_state (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_nphy_spur_workaround (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_superswitch_init (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_nphy_tables_init (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_tx_gain_table_upload (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_tx_lpf_bw (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_tx_power_ctl_idle_tssi (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_tx_power_ctl_setup (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_tx_power_ctrl (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_nphy_tx_power_fix (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_tx_pwr_ctrl_coef_setup (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_update_mimo_config (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_nphy_update_txrx_chain (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_workarounds (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_force_clock (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcma_cc_set32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  chipco_set32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int b43_phy_initn(struct b43_wldev *dev)
{
	struct ssb_sprom *sprom = dev->dev->bus_sprom;
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_n *nphy = phy->n;
	u8 tx_pwr_state;
	struct nphy_txgains target;
	u16 tmp;
	bool do_rssi_cal;

	u16 clip[2];
	bool do_cal = false;

	if ((dev->phy.rev >= 3) &&
	   (sprom->boardflags_lo & B43_BFL_EXTLNA) &&
	   (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)) {
		switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
		case B43_BUS_BCMA:
			bcma_cc_set32(&dev->dev->bdev->bus->drv_cc,
				      BCMA_CC_CHIPCTL, 0x40);
			break;
#endif
#ifdef CONFIG_B43_SSB
		case B43_BUS_SSB:
			chipco_set32(&dev->dev->sdev->bus->chipco,
				     SSB_CHIPCO_CHIPCTL, 0x40);
			break;
#endif
		}
	}
	nphy->use_int_tx_iq_lo_cal = b43_nphy_ipa(dev) ||
		phy->rev >= 7 ||
		(phy->rev >= 5 &&
		 sprom->boardflags2_hi & B43_BFH2_INTERNDET_TXIQCAL);
	nphy->deaf_count = 0;
	b43_nphy_tables_init(dev);
	nphy->crsminpwr_adjusted = false;
	nphy->noisevars_adjusted = false;

	/* Clear all overrides */
	if (dev->phy.rev >= 3) {
		b43_phy_write(dev, B43_NPHY_TXF_40CO_B1S1, 0);
		b43_phy_write(dev, B43_NPHY_RFCTL_OVER, 0);
		if (phy->rev >= 7) {
			b43_phy_write(dev, B43_NPHY_REV7_RF_CTL_OVER3, 0);
			b43_phy_write(dev, B43_NPHY_REV7_RF_CTL_OVER4, 0);
			b43_phy_write(dev, B43_NPHY_REV7_RF_CTL_OVER5, 0);
			b43_phy_write(dev, B43_NPHY_REV7_RF_CTL_OVER6, 0);
		}
		if (phy->rev >= 19) {
			/* TODO */
		}

		b43_phy_write(dev, B43_NPHY_TXF_40CO_B1S0, 0);
		b43_phy_write(dev, B43_NPHY_TXF_40CO_B32S1, 0);
	} else {
		b43_phy_write(dev, B43_NPHY_RFCTL_OVER, 0);
	}
	b43_phy_write(dev, B43_NPHY_RFCTL_INTC1, 0);
	b43_phy_write(dev, B43_NPHY_RFCTL_INTC2, 0);
	if (dev->phy.rev < 6) {
		b43_phy_write(dev, B43_NPHY_RFCTL_INTC3, 0);
		b43_phy_write(dev, B43_NPHY_RFCTL_INTC4, 0);
	}
	b43_phy_mask(dev, B43_NPHY_RFSEQMODE,
		     ~(B43_NPHY_RFSEQMODE_CAOVER |
		       B43_NPHY_RFSEQMODE_TROVER));
	if (dev->phy.rev >= 3)
		b43_phy_write(dev, B43_NPHY_AFECTL_OVER1, 0);
	b43_phy_write(dev, B43_NPHY_AFECTL_OVER, 0);

	if (dev->phy.rev <= 2) {
		tmp = (dev->phy.rev == 2) ? 0x3B : 0x40;
		b43_phy_maskset(dev, B43_NPHY_BPHY_CTL3,
				~B43_NPHY_BPHY_CTL3_SCALE,
				tmp << B43_NPHY_BPHY_CTL3_SCALE_SHIFT);
	}
	b43_phy_write(dev, B43_NPHY_AFESEQ_TX2RX_PUD_20M, 0x20);
	b43_phy_write(dev, B43_NPHY_AFESEQ_TX2RX_PUD_40M, 0x20);

	if (sprom->boardflags2_lo & B43_BFL2_SKWRKFEM_BRD ||
	    (dev->dev->board_vendor == PCI_VENDOR_ID_APPLE &&
	     dev->dev->board_type == BCMA_BOARD_TYPE_BCM943224M93))
		b43_phy_write(dev, B43_NPHY_TXREALFD, 0xA0);
	else
		b43_phy_write(dev, B43_NPHY_TXREALFD, 0xB8);
	b43_phy_write(dev, B43_NPHY_MIMO_CRSTXEXT, 0xC8);
	b43_phy_write(dev, B43_NPHY_PLOAD_CSENSE_EXTLEN, 0x50);
	b43_phy_write(dev, B43_NPHY_TXRIFS_FRDEL, 0x30);

	if (phy->rev < 8)
		b43_nphy_update_mimo_config(dev, nphy->preamble_override);

	b43_nphy_update_txrx_chain(dev);

	if (phy->rev < 2) {
		b43_phy_write(dev, B43_NPHY_DUP40_GFBL, 0xAA8);
		b43_phy_write(dev, B43_NPHY_DUP40_BL, 0x9A4);
	}

	if (b43_nphy_ipa(dev)) {
		b43_phy_set(dev, B43_NPHY_PAPD_EN0, 0x1);
		b43_phy_maskset(dev, B43_NPHY_EPS_TABLE_ADJ0, 0x007F,
				nphy->papd_epsilon_offset[0] << 7);
		b43_phy_set(dev, B43_NPHY_PAPD_EN1, 0x1);
		b43_phy_maskset(dev, B43_NPHY_EPS_TABLE_ADJ1, 0x007F,
				nphy->papd_epsilon_offset[1] << 7);
		b43_nphy_int_pa_set_tx_dig_filters(dev);
	} else if (phy->rev >= 5) {
		b43_nphy_ext_pa_set_tx_dig_filters(dev);
	}

	b43_nphy_workarounds(dev);

	/* Reset CCA, in init code it differs a little from standard way */
	b43_phy_force_clock(dev, 1);
	tmp = b43_phy_read(dev, B43_NPHY_BBCFG);
	b43_phy_write(dev, B43_NPHY_BBCFG, tmp | B43_NPHY_BBCFG_RSTCCA);
	b43_phy_write(dev, B43_NPHY_BBCFG, tmp & ~B43_NPHY_BBCFG_RSTCCA);
	b43_phy_force_clock(dev, 0);

	b43_mac_phy_clock_set(dev, true);

	if (phy->rev < 7) {
		b43_nphy_pa_override(dev, false);
		b43_nphy_force_rf_sequence(dev, B43_RFSEQ_RX2TX);
		b43_nphy_force_rf_sequence(dev, B43_RFSEQ_RESET2RX);
		b43_nphy_pa_override(dev, true);
	}

	b43_nphy_classifier(dev, 0, 0);
	b43_nphy_read_clip_detection(dev, clip);
	if (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
		b43_nphy_bphy_init(dev);

	tx_pwr_state = nphy->txpwrctrl;
	b43_nphy_tx_power_ctrl(dev, false);
	b43_nphy_tx_power_fix(dev);
	b43_nphy_tx_power_ctl_idle_tssi(dev);
	b43_nphy_tx_power_ctl_setup(dev);
	b43_nphy_tx_gain_table_upload(dev);

	if (nphy->phyrxchain != 3)
		b43_nphy_set_rx_core_state(dev, nphy->phyrxchain);
	if (nphy->mphase_cal_phase_id > 0)
		;/* TODO PHY Periodic Calibration Multi-Phase Restart */

	do_rssi_cal = false;
	if (phy->rev >= 3) {
		if (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
			do_rssi_cal = !nphy->rssical_chanspec_2G.center_freq;
		else
			do_rssi_cal = !nphy->rssical_chanspec_5G.center_freq;

		if (do_rssi_cal)
			b43_nphy_rssi_cal(dev);
		else
			b43_nphy_restore_rssi_cal(dev);
	} else {
		b43_nphy_rssi_cal(dev);
	}

	if (!((nphy->measure_hold & 0x6) != 0)) {
		if (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
			do_cal = !nphy->iqcal_chanspec_2G.center_freq;
		else
			do_cal = !nphy->iqcal_chanspec_5G.center_freq;

		if (nphy->mute)
			do_cal = false;

		if (do_cal) {
			target = b43_nphy_get_tx_gains(dev);

			if (nphy->antsel_type == 2)
				b43_nphy_superswitch_init(dev, true);
			if (nphy->perical != 2) {
				b43_nphy_rssi_cal(dev);
				if (phy->rev >= 3) {
					nphy->cal_orig_pwr_idx[0] =
					    nphy->txpwrindex[0].index_internal;
					nphy->cal_orig_pwr_idx[1] =
					    nphy->txpwrindex[1].index_internal;
					/* TODO N PHY Pre Calibrate TX Gain */
					target = b43_nphy_get_tx_gains(dev);
				}
				if (!b43_nphy_cal_tx_iq_lo(dev, target, true, false))
					if (b43_nphy_cal_rx_iq(dev, target, 2, 0) == 0)
						b43_nphy_save_cal(dev);
			} else if (nphy->mphase_cal_phase_id == 0)
				;/* N PHY Periodic Calibration with arg 3 */
		} else {
			b43_nphy_restore_cal(dev);
		}
	}

	b43_nphy_tx_pwr_ctrl_coef_setup(dev);
	b43_nphy_tx_power_ctrl(dev, tx_pwr_state);
	b43_phy_write(dev, B43_NPHY_TXMACIF_HOLDOFF, 0x0015);
	b43_phy_write(dev, B43_NPHY_TXMACDELAY, 0x0320);
	if (phy->rev >= 3 && phy->rev <= 6)
		b43_phy_write(dev, B43_NPHY_PLOAD_CSENSE_EXTLEN, 0x0032);
	b43_nphy_tx_lpf_bw(dev);
	if (phy->rev >= 3)
		b43_nphy_spur_workaround(dev);

	return 0;
}