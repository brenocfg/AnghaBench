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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct lpphy_tx_gains {int dummy; } ;
struct lpphy_iq_est {int i_pwr; int q_pwr; } ;
struct TYPE_2__ {struct b43_phy_lp* lp; } ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_1__ phy; } ;
struct b43_phy_lp {int txpctl_mode; int rc_cap; } ;
typedef  int /*<<< orphan*/  iq_est ;
typedef  enum b43_lpphy_txpctl_mode { ____Placeholder_b43_lpphy_txpctl_mode } b43_lpphy_txpctl_mode ;

/* Variables and functions */
 int /*<<< orphan*/  B2062_N_RXBB_CALIB2 ; 
 int /*<<< orphan*/  B43_LPPHY_AFE_CTL_OVR ; 
 int /*<<< orphan*/  B43_LPPHY_AFE_CTL_OVRVAL ; 
 int /*<<< orphan*/  B43_LPPHY_LP_PHY_CTL ; 
 int /*<<< orphan*/  B43_LPPHY_RF_OVERRIDE_0 ; 
 int /*<<< orphan*/  B43_LPPHY_RF_OVERRIDE_2 ; 
 int /*<<< orphan*/  B43_LPPHY_RF_OVERRIDE_2_VAL ; 
 int /*<<< orphan*/  B43_LPPHY_RF_OVERRIDE_VAL_0 ; 
 int B43_LPPHY_TXPCTL_OFF ; 
 int b43_lpphy_op_switch_channel (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lpphy_disable_crs (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  lpphy_get_bb_mult (struct b43_wldev*) ; 
 struct lpphy_tx_gains lpphy_get_tx_gains (struct b43_wldev*) ; 
 int lpphy_loopback (struct b43_wldev*) ; 
 int lpphy_qdiv_roundup (int,int,int) ; 
 int /*<<< orphan*/  lpphy_read_tx_pctl_mode_from_hardware (struct b43_wldev*) ; 
 int /*<<< orphan*/  lpphy_restore_crs (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  lpphy_run_ddfs (struct b43_wldev*,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpphy_rx_iq_est (struct b43_wldev*,int,int,struct lpphy_iq_est*) ; 
 int /*<<< orphan*/  lpphy_set_bb_mult (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpphy_set_rc_cap (struct b43_wldev*) ; 
 int /*<<< orphan*/  lpphy_set_rx_gain_by_index (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  lpphy_set_tx_gains (struct b43_wldev*,struct lpphy_tx_gains) ; 
 int /*<<< orphan*/  lpphy_set_tx_power_control (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  lpphy_stop_ddfs (struct b43_wldev*) ; 
 int /*<<< orphan*/  memset (struct lpphy_iq_est*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lpphy_rev0_1_rc_calib(struct b43_wldev *dev)
{
	struct b43_phy_lp *lpphy = dev->phy.lp;
	struct lpphy_iq_est iq_est;
	struct lpphy_tx_gains tx_gains;
	static const u32 ideal_pwr_table[21] = {
		0x10000, 0x10557, 0x10e2d, 0x113e0, 0x10f22, 0x0ff64,
		0x0eda2, 0x0e5d4, 0x0efd1, 0x0fbe8, 0x0b7b8, 0x04b35,
		0x01a5e, 0x00a0b, 0x00444, 0x001fd, 0x000ff, 0x00088,
		0x0004c, 0x0002c, 0x0001a,
	};
	bool old_txg_ovr;
	u8 old_bbmult;
	u16 old_rf_ovr, old_rf_ovrval, old_afe_ovr, old_afe_ovrval,
	    old_rf2_ovr, old_rf2_ovrval, old_phy_ctl;
	enum b43_lpphy_txpctl_mode old_txpctl;
	u32 normal_pwr, ideal_pwr, mean_sq_pwr, tmp = 0, mean_sq_pwr_min = 0;
	int loopback, i, j, inner_sum, err;

	memset(&iq_est, 0, sizeof(iq_est));

	err = b43_lpphy_op_switch_channel(dev, 7);
	if (err) {
		b43dbg(dev->wl,
		       "RC calib: Failed to switch to channel 7, error = %d\n",
		       err);
	}
	old_txg_ovr = !!(b43_phy_read(dev, B43_LPPHY_AFE_CTL_OVR) & 0x40);
	old_bbmult = lpphy_get_bb_mult(dev);
	if (old_txg_ovr)
		tx_gains = lpphy_get_tx_gains(dev);
	old_rf_ovr = b43_phy_read(dev, B43_LPPHY_RF_OVERRIDE_0);
	old_rf_ovrval = b43_phy_read(dev, B43_LPPHY_RF_OVERRIDE_VAL_0);
	old_afe_ovr = b43_phy_read(dev, B43_LPPHY_AFE_CTL_OVR);
	old_afe_ovrval = b43_phy_read(dev, B43_LPPHY_AFE_CTL_OVRVAL);
	old_rf2_ovr = b43_phy_read(dev, B43_LPPHY_RF_OVERRIDE_2);
	old_rf2_ovrval = b43_phy_read(dev, B43_LPPHY_RF_OVERRIDE_2_VAL);
	old_phy_ctl = b43_phy_read(dev, B43_LPPHY_LP_PHY_CTL);
	lpphy_read_tx_pctl_mode_from_hardware(dev);
	old_txpctl = lpphy->txpctl_mode;

	lpphy_set_tx_power_control(dev, B43_LPPHY_TXPCTL_OFF);
	lpphy_disable_crs(dev, true);
	loopback = lpphy_loopback(dev);
	if (loopback == -1)
		goto finish;
	lpphy_set_rx_gain_by_index(dev, loopback);
	b43_phy_maskset(dev, B43_LPPHY_LP_PHY_CTL, 0xFFBF, 0x40);
	b43_phy_maskset(dev, B43_LPPHY_RF_OVERRIDE_2_VAL, 0xFFF8, 0x1);
	b43_phy_maskset(dev, B43_LPPHY_RF_OVERRIDE_2_VAL, 0xFFC7, 0x8);
	b43_phy_maskset(dev, B43_LPPHY_RF_OVERRIDE_2_VAL, 0xFF3F, 0xC0);
	for (i = 128; i <= 159; i++) {
		b43_radio_write(dev, B2062_N_RXBB_CALIB2, i);
		inner_sum = 0;
		for (j = 5; j <= 25; j++) {
			lpphy_run_ddfs(dev, 1, 1, j, j, 0);
			if (!(lpphy_rx_iq_est(dev, 1000, 32, &iq_est)))
				goto finish;
			mean_sq_pwr = iq_est.i_pwr + iq_est.q_pwr;
			if (j == 5)
				tmp = mean_sq_pwr;
			ideal_pwr = ((ideal_pwr_table[j-5] >> 3) + 1) >> 1;
			normal_pwr = lpphy_qdiv_roundup(mean_sq_pwr, tmp, 12);
			mean_sq_pwr = ideal_pwr - normal_pwr;
			mean_sq_pwr *= mean_sq_pwr;
			inner_sum += mean_sq_pwr;
			if ((i == 128) || (inner_sum < mean_sq_pwr_min)) {
				lpphy->rc_cap = i;
				mean_sq_pwr_min = inner_sum;
			}
		}
	}
	lpphy_stop_ddfs(dev);

finish:
	lpphy_restore_crs(dev, true);
	b43_phy_write(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, old_rf_ovrval);
	b43_phy_write(dev, B43_LPPHY_RF_OVERRIDE_0, old_rf_ovr);
	b43_phy_write(dev, B43_LPPHY_AFE_CTL_OVRVAL, old_afe_ovrval);
	b43_phy_write(dev, B43_LPPHY_AFE_CTL_OVR, old_afe_ovr);
	b43_phy_write(dev, B43_LPPHY_RF_OVERRIDE_2_VAL, old_rf2_ovrval);
	b43_phy_write(dev, B43_LPPHY_RF_OVERRIDE_2, old_rf2_ovr);
	b43_phy_write(dev, B43_LPPHY_LP_PHY_CTL, old_phy_ctl);

	lpphy_set_bb_mult(dev, old_bbmult);
	if (old_txg_ovr) {
		/*
		 * SPEC FIXME: The specs say "get_tx_gains" here, which is
		 * illogical. According to lwfinger, vendor driver v4.150.10.5
		 * has a Set here, while v4.174.64.19 has a Get - regression in
		 * the vendor driver? This should be tested this once the code
		 * is testable.
		 */
		lpphy_set_tx_gains(dev, tx_gains);
	}
	lpphy_set_tx_power_control(dev, old_txpctl);
	if (lpphy->rc_cap)
		lpphy_set_rc_cap(dev);
}