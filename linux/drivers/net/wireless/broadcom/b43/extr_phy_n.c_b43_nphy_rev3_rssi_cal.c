#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct b43_phy {int rev; TYPE_5__* chandef; struct b43_phy_n* n; } ;
struct b43_wldev {int /*<<< orphan*/  wl; struct b43_phy phy; } ;
struct TYPE_8__ {int /*<<< orphan*/  center_freq; } ;
struct TYPE_7__ {int /*<<< orphan*/  center_freq; } ;
struct TYPE_6__ {int* rssical_radio_regs_2G; int* rssical_phy_regs_2G; int* rssical_radio_regs_5G; int* rssical_phy_regs_5G; } ;
struct b43_phy_n {TYPE_3__ rssical_chanspec_5G; TYPE_2__ rssical_chanspec_2G; TYPE_1__ rssical_cache; } ;
typedef  int s32 ;
struct TYPE_10__ {TYPE_4__* chan; } ;
struct TYPE_9__ {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int B2056_RX0 ; 
 int B2056_RX1 ; 
 int B2056_RX_RSSI_MISC ; 
 int B43_NPHY_AFECTL_C1 ; 
 int B43_NPHY_AFECTL_C2 ; 
 int B43_NPHY_AFECTL_OVER ; 
 int B43_NPHY_AFECTL_OVER1 ; 
 int B43_NPHY_REV7_RF_CTL_MISC_REG3 ; 
 int B43_NPHY_REV7_RF_CTL_MISC_REG4 ; 
 int B43_NPHY_REV7_RF_CTL_MISC_REG5 ; 
 int B43_NPHY_REV7_RF_CTL_MISC_REG6 ; 
 int B43_NPHY_REV7_RF_CTL_OVER3 ; 
 int B43_NPHY_REV7_RF_CTL_OVER4 ; 
 int B43_NPHY_REV7_RF_CTL_OVER5 ; 
 int B43_NPHY_REV7_RF_CTL_OVER6 ; 
 int B43_NPHY_RFCTL_CMD ; 
 int B43_NPHY_RFCTL_CMD_RXTX ; 
 int B43_NPHY_RFCTL_CMD_START ; 
 int B43_NPHY_RFCTL_INTC1 ; 
 int B43_NPHY_RFCTL_INTC2 ; 
 int B43_NPHY_RFCTL_LUT_TRSW_UP1 ; 
 int B43_NPHY_RFCTL_LUT_TRSW_UP2 ; 
 int B43_NPHY_RFCTL_OVER ; 
 int B43_NPHY_RFCTL_RSSIO1 ; 
 int B43_NPHY_RFCTL_RSSIO2 ; 
 int B43_NPHY_RSSIMC_0I_RSSI_X ; 
 int B43_NPHY_RSSIMC_0I_RSSI_Y ; 
 int B43_NPHY_RSSIMC_0I_RSSI_Z ; 
 int B43_NPHY_RSSIMC_0Q_RSSI_X ; 
 int B43_NPHY_RSSIMC_0Q_RSSI_Y ; 
 int B43_NPHY_RSSIMC_0Q_RSSI_Z ; 
 int B43_NPHY_RSSIMC_1I_RSSI_X ; 
 int B43_NPHY_RSSIMC_1I_RSSI_Y ; 
 int B43_NPHY_RSSIMC_1I_RSSI_Z ; 
 int B43_NPHY_RSSIMC_1Q_RSSI_X ; 
 int B43_NPHY_RSSIMC_1Q_RSSI_Y ; 
 int B43_NPHY_RSSIMC_1Q_RSSI_Z ; 
 int B43_NPHY_TXF_40CO_B1S0 ; 
 int B43_NPHY_TXF_40CO_B1S1 ; 
 int B43_NPHY_TXF_40CO_B32S1 ; 
 int /*<<< orphan*/  B43_RFSEQ_RESET2RX ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  N_INTC_OVERRIDE_OFF ; 
 int /*<<< orphan*/  N_INTC_OVERRIDE_TRSW ; 
 int N_RAIL_I ; 
 int N_RAIL_Q ; 
 int /*<<< orphan*/  N_RF_CTL_OVER_CMD_RXRF_PU ; 
 int /*<<< orphan*/  N_RF_CTL_OVER_CMD_RX_PU ; 
 int N_RSSI_NB ; 
 int R2057_NB_MASTER_CORE0 ; 
 int R2057_NB_MASTER_CORE1 ; 
 int R2057_VCM_MASK ; 
 int abs (int) ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int b43_nphy_classifier (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_nphy_force_rf_sequence (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int b43_nphy_get_rx_core_state (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_poll_rssi (struct b43_wldev*,int,int*,int) ; 
 int /*<<< orphan*/  b43_nphy_read_clip_detection (struct b43_wldev*,int*) ; 
 int /*<<< orphan*/  b43_nphy_rf_ctl_intc_override (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  b43_nphy_rf_ctl_override (struct b43_wldev*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_nphy_rf_ctl_override_one_to_many (struct b43_wldev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_nphy_rf_ctl_override_rev7 (struct b43_wldev*,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_nphy_scale_offset_rssi (struct b43_wldev*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  b43_nphy_write_clip_detection (struct b43_wldev*,int*) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int,int) ; 
 int b43_phy_read (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_maskset (struct b43_wldev*,int,int,int) ; 
 int b43_radio_read (struct b43_wldev*,int) ; 

__attribute__((used)) static void b43_nphy_rev3_rssi_cal(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_n *nphy = dev->phy.n;

	u16 saved_regs_phy_rfctl[2];
	u16 saved_regs_phy[22];
	u16 regs_to_store_rev3[] = {
		B43_NPHY_AFECTL_OVER1, B43_NPHY_AFECTL_OVER,
		B43_NPHY_AFECTL_C1, B43_NPHY_AFECTL_C2,
		B43_NPHY_TXF_40CO_B1S1, B43_NPHY_RFCTL_OVER,
		B43_NPHY_TXF_40CO_B1S0, B43_NPHY_TXF_40CO_B32S1,
		B43_NPHY_RFCTL_CMD,
		B43_NPHY_RFCTL_LUT_TRSW_UP1, B43_NPHY_RFCTL_LUT_TRSW_UP2,
		B43_NPHY_RFCTL_RSSIO1, B43_NPHY_RFCTL_RSSIO2
	};
	u16 regs_to_store_rev7[] = {
		B43_NPHY_AFECTL_OVER1, B43_NPHY_AFECTL_OVER,
		B43_NPHY_AFECTL_C1, B43_NPHY_AFECTL_C2,
		B43_NPHY_TXF_40CO_B1S1, B43_NPHY_RFCTL_OVER,
		B43_NPHY_REV7_RF_CTL_OVER3, B43_NPHY_REV7_RF_CTL_OVER4,
		B43_NPHY_REV7_RF_CTL_OVER5, B43_NPHY_REV7_RF_CTL_OVER6,
		0x2ff,
		B43_NPHY_TXF_40CO_B1S0, B43_NPHY_TXF_40CO_B32S1,
		B43_NPHY_RFCTL_CMD,
		B43_NPHY_RFCTL_LUT_TRSW_UP1, B43_NPHY_RFCTL_LUT_TRSW_UP2,
		B43_NPHY_REV7_RF_CTL_MISC_REG3, B43_NPHY_REV7_RF_CTL_MISC_REG4,
		B43_NPHY_REV7_RF_CTL_MISC_REG5, B43_NPHY_REV7_RF_CTL_MISC_REG6,
		B43_NPHY_RFCTL_RSSIO1, B43_NPHY_RFCTL_RSSIO2
	};
	u16 *regs_to_store;
	int regs_amount;

	u16 class;

	u16 clip_state[2];
	u16 clip_off[2] = { 0xFFFF, 0xFFFF };

	u8 vcm_final = 0;
	s32 offset[4];
	s32 results[8][4] = { };
	s32 results_min[4] = { };
	s32 poll_results[4] = { };

	u16 *rssical_radio_regs = NULL;
	u16 *rssical_phy_regs = NULL;

	u16 r; /* routing */
	u8 rx_core_state;
	int core, i, j, vcm;

	if (dev->phy.rev >= 7) {
		regs_to_store = regs_to_store_rev7;
		regs_amount = ARRAY_SIZE(regs_to_store_rev7);
	} else {
		regs_to_store = regs_to_store_rev3;
		regs_amount = ARRAY_SIZE(regs_to_store_rev3);
	}
	BUG_ON(regs_amount > ARRAY_SIZE(saved_regs_phy));

	class = b43_nphy_classifier(dev, 0, 0);
	b43_nphy_classifier(dev, 7, 4);
	b43_nphy_read_clip_detection(dev, clip_state);
	b43_nphy_write_clip_detection(dev, clip_off);

	saved_regs_phy_rfctl[0] = b43_phy_read(dev, B43_NPHY_RFCTL_INTC1);
	saved_regs_phy_rfctl[1] = b43_phy_read(dev, B43_NPHY_RFCTL_INTC2);
	for (i = 0; i < regs_amount; i++)
		saved_regs_phy[i] = b43_phy_read(dev, regs_to_store[i]);

	b43_nphy_rf_ctl_intc_override(dev, N_INTC_OVERRIDE_OFF, 0, 7);
	b43_nphy_rf_ctl_intc_override(dev, N_INTC_OVERRIDE_TRSW, 1, 7);

	if (dev->phy.rev >= 7) {
		b43_nphy_rf_ctl_override_one_to_many(dev,
						     N_RF_CTL_OVER_CMD_RXRF_PU,
						     0, 0, false);
		b43_nphy_rf_ctl_override_one_to_many(dev,
						     N_RF_CTL_OVER_CMD_RX_PU,
						     1, 0, false);
		b43_nphy_rf_ctl_override_rev7(dev, 0x80, 1, 0, false, 0);
		b43_nphy_rf_ctl_override_rev7(dev, 0x40, 1, 0, false, 0);
		if (b43_current_band(dev->wl) == NL80211_BAND_5GHZ) {
			b43_nphy_rf_ctl_override_rev7(dev, 0x20, 0, 0, false,
						      0);
			b43_nphy_rf_ctl_override_rev7(dev, 0x10, 1, 0, false,
						      0);
		} else {
			b43_nphy_rf_ctl_override_rev7(dev, 0x10, 0, 0, false,
						      0);
			b43_nphy_rf_ctl_override_rev7(dev, 0x20, 1, 0, false,
						      0);
		}
	} else {
		b43_nphy_rf_ctl_override(dev, 0x1, 0, 0, false);
		b43_nphy_rf_ctl_override(dev, 0x2, 1, 0, false);
		b43_nphy_rf_ctl_override(dev, 0x80, 1, 0, false);
		b43_nphy_rf_ctl_override(dev, 0x40, 1, 0, false);
		if (b43_current_band(dev->wl) == NL80211_BAND_5GHZ) {
			b43_nphy_rf_ctl_override(dev, 0x20, 0, 0, false);
			b43_nphy_rf_ctl_override(dev, 0x10, 1, 0, false);
		} else {
			b43_nphy_rf_ctl_override(dev, 0x10, 0, 0, false);
			b43_nphy_rf_ctl_override(dev, 0x20, 1, 0, false);
		}
	}

	rx_core_state = b43_nphy_get_rx_core_state(dev);
	for (core = 0; core < 2; core++) {
		if (!(rx_core_state & (1 << core)))
			continue;
		r = core ? B2056_RX1 : B2056_RX0;
		b43_nphy_scale_offset_rssi(dev, 0, 0, core + 1, N_RAIL_I,
					   N_RSSI_NB);
		b43_nphy_scale_offset_rssi(dev, 0, 0, core + 1, N_RAIL_Q,
					   N_RSSI_NB);

		/* Grab RSSI results for every possible VCM */
		for (vcm = 0; vcm < 8; vcm++) {
			if (dev->phy.rev >= 7)
				b43_radio_maskset(dev,
						  core ? R2057_NB_MASTER_CORE1 :
							 R2057_NB_MASTER_CORE0,
						  ~R2057_VCM_MASK, vcm);
			else
				b43_radio_maskset(dev, r | B2056_RX_RSSI_MISC,
						  0xE3, vcm << 2);
			b43_nphy_poll_rssi(dev, N_RSSI_NB, results[vcm], 8);
		}

		/* Find out which VCM got the best results */
		for (i = 0; i < 4; i += 2) {
			s32 currd;
			s32 mind = 0x100000;
			s32 minpoll = 249;
			u8 minvcm = 0;
			if (2 * core != i)
				continue;
			for (vcm = 0; vcm < 8; vcm++) {
				currd = results[vcm][i] * results[vcm][i] +
					results[vcm][i + 1] * results[vcm][i];
				if (currd < mind) {
					mind = currd;
					minvcm = vcm;
				}
				if (results[vcm][i] < minpoll)
					minpoll = results[vcm][i];
			}
			vcm_final = minvcm;
			results_min[i] = minpoll;
		}

		/* Select the best VCM */
		if (dev->phy.rev >= 7)
			b43_radio_maskset(dev,
					  core ? R2057_NB_MASTER_CORE1 :
						 R2057_NB_MASTER_CORE0,
					  ~R2057_VCM_MASK, vcm);
		else
			b43_radio_maskset(dev, r | B2056_RX_RSSI_MISC,
					  0xE3, vcm_final << 2);

		for (i = 0; i < 4; i++) {
			if (core != i / 2)
				continue;
			offset[i] = -results[vcm_final][i];
			if (offset[i] < 0)
				offset[i] = -((abs(offset[i]) + 4) / 8);
			else
				offset[i] = (offset[i] + 4) / 8;
			if (results_min[i] == 248)
				offset[i] = -32;
			b43_nphy_scale_offset_rssi(dev, 0, offset[i],
						   (i / 2 == 0) ? 1 : 2,
						   (i % 2 == 0) ? N_RAIL_I : N_RAIL_Q,
						   N_RSSI_NB);
		}
	}

	for (core = 0; core < 2; core++) {
		if (!(rx_core_state & (1 << core)))
			continue;
		for (i = 0; i < 2; i++) {
			b43_nphy_scale_offset_rssi(dev, 0, 0, core + 1,
						   N_RAIL_I, i);
			b43_nphy_scale_offset_rssi(dev, 0, 0, core + 1,
						   N_RAIL_Q, i);
			b43_nphy_poll_rssi(dev, i, poll_results, 8);
			for (j = 0; j < 4; j++) {
				if (j / 2 == core) {
					offset[j] = 232 - poll_results[j];
					if (offset[j] < 0)
						offset[j] = -(abs(offset[j] + 4) / 8);
					else
						offset[j] = (offset[j] + 4) / 8;
					b43_nphy_scale_offset_rssi(dev, 0,
						offset[2 * core], core + 1, j % 2, i);
				}
			}
		}
	}

	b43_phy_write(dev, B43_NPHY_RFCTL_INTC1, saved_regs_phy_rfctl[0]);
	b43_phy_write(dev, B43_NPHY_RFCTL_INTC2, saved_regs_phy_rfctl[1]);

	b43_nphy_force_rf_sequence(dev, B43_RFSEQ_RESET2RX);

	b43_phy_set(dev, B43_NPHY_TXF_40CO_B1S1, 0x1);
	b43_phy_set(dev, B43_NPHY_RFCTL_CMD, B43_NPHY_RFCTL_CMD_START);
	b43_phy_mask(dev, B43_NPHY_TXF_40CO_B1S1, ~0x1);

	b43_phy_set(dev, B43_NPHY_RFCTL_OVER, 0x1);
	b43_phy_set(dev, B43_NPHY_RFCTL_CMD, B43_NPHY_RFCTL_CMD_RXTX);
	b43_phy_mask(dev, B43_NPHY_RFCTL_OVER, ~0x1);

	for (i = 0; i < regs_amount; i++)
		b43_phy_write(dev, regs_to_store[i], saved_regs_phy[i]);

	/* Store for future configuration */
	if (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) {
		rssical_radio_regs = nphy->rssical_cache.rssical_radio_regs_2G;
		rssical_phy_regs = nphy->rssical_cache.rssical_phy_regs_2G;
	} else {
		rssical_radio_regs = nphy->rssical_cache.rssical_radio_regs_5G;
		rssical_phy_regs = nphy->rssical_cache.rssical_phy_regs_5G;
	}
	if (dev->phy.rev >= 7) {
		rssical_radio_regs[0] = b43_radio_read(dev,
						       R2057_NB_MASTER_CORE0);
		rssical_radio_regs[1] = b43_radio_read(dev,
						       R2057_NB_MASTER_CORE1);
	} else {
		rssical_radio_regs[0] = b43_radio_read(dev, B2056_RX0 |
						       B2056_RX_RSSI_MISC);
		rssical_radio_regs[1] = b43_radio_read(dev, B2056_RX1 |
						       B2056_RX_RSSI_MISC);
	}
	rssical_phy_regs[0] = b43_phy_read(dev, B43_NPHY_RSSIMC_0I_RSSI_Z);
	rssical_phy_regs[1] = b43_phy_read(dev, B43_NPHY_RSSIMC_0Q_RSSI_Z);
	rssical_phy_regs[2] = b43_phy_read(dev, B43_NPHY_RSSIMC_1I_RSSI_Z);
	rssical_phy_regs[3] = b43_phy_read(dev, B43_NPHY_RSSIMC_1Q_RSSI_Z);
	rssical_phy_regs[4] = b43_phy_read(dev, B43_NPHY_RSSIMC_0I_RSSI_X);
	rssical_phy_regs[5] = b43_phy_read(dev, B43_NPHY_RSSIMC_0Q_RSSI_X);
	rssical_phy_regs[6] = b43_phy_read(dev, B43_NPHY_RSSIMC_1I_RSSI_X);
	rssical_phy_regs[7] = b43_phy_read(dev, B43_NPHY_RSSIMC_1Q_RSSI_X);
	rssical_phy_regs[8] = b43_phy_read(dev, B43_NPHY_RSSIMC_0I_RSSI_Y);
	rssical_phy_regs[9] = b43_phy_read(dev, B43_NPHY_RSSIMC_0Q_RSSI_Y);
	rssical_phy_regs[10] = b43_phy_read(dev, B43_NPHY_RSSIMC_1I_RSSI_Y);
	rssical_phy_regs[11] = b43_phy_read(dev, B43_NPHY_RSSIMC_1Q_RSSI_Y);

	/* Remember for which channel we store configuration */
	if (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
		nphy->rssical_chanspec_2G.center_freq = phy->chandef->chan->center_freq;
	else
		nphy->rssical_chanspec_5G.center_freq = phy->chandef->chan->center_freq;

	/* End of calibration, restore configuration */
	b43_nphy_classifier(dev, 7, class);
	b43_nphy_write_clip_detection(dev, clip_state);
}