#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct lpphy_tx_gains {int dummy; } ;
struct lpphy_rx_iq_comp {scalar_t__ chan; int c1; int c0; } ;
struct TYPE_4__ {int rev; struct b43_phy_lp* lp; } ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_2__ phy; TYPE_1__* dev; } ;
struct b43_phy_lp {scalar_t__ channel; } ;
typedef  int /*<<< orphan*/  oldgains ;
typedef  int /*<<< orphan*/  nogains ;
struct TYPE_3__ {int chip_id; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct lpphy_rx_iq_comp*) ; 
 int /*<<< orphan*/  B43_LPPHY_AFE_CTL_OVR ; 
 int /*<<< orphan*/  B43_LPPHY_AFE_CTL_OVRVAL ; 
 int /*<<< orphan*/  B43_LPPHY_RF_OVERRIDE_0 ; 
 int /*<<< orphan*/  B43_LPPHY_RF_OVERRIDE_VAL_0 ; 
 int /*<<< orphan*/  B43_LPPHY_RX_COMP_COEFF_S ; 
 scalar_t__ B43_WARN_ON (int) ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 struct lpphy_rx_iq_comp* lpphy_5354_iq_table ; 
 int lpphy_calc_rx_iq_comp (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  lpphy_clear_deaf (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  lpphy_disable_rx_gain_override (struct b43_wldev*) ; 
 int /*<<< orphan*/  lpphy_disable_tx_gain_override (struct b43_wldev*) ; 
 struct lpphy_tx_gains lpphy_get_tx_gains (struct b43_wldev*) ; 
 struct lpphy_rx_iq_comp* lpphy_rev0_1_iq_table ; 
 struct lpphy_rx_iq_comp lpphy_rev2plus_iq_comp ; 
 int /*<<< orphan*/  lpphy_set_deaf (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  lpphy_set_rx_gain (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  lpphy_set_trsw_over (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  lpphy_set_tx_gains (struct b43_wldev*,struct lpphy_tx_gains) ; 
 int /*<<< orphan*/  lpphy_start_tx_tone (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  lpphy_stop_tx_tone (struct b43_wldev*) ; 
 int /*<<< orphan*/  memset (struct lpphy_tx_gains*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lpphy_rx_iq_cal(struct b43_wldev *dev, bool noise, bool tx,
			    bool rx, bool pa, struct lpphy_tx_gains *gains)
{
	struct b43_phy_lp *lpphy = dev->phy.lp;
	const struct lpphy_rx_iq_comp *iqcomp = NULL;
	struct lpphy_tx_gains nogains, oldgains;
	u16 tmp;
	int i, ret;

	memset(&nogains, 0, sizeof(nogains));
	memset(&oldgains, 0, sizeof(oldgains));

	if (dev->dev->chip_id == 0x5354) {
		for (i = 0; i < ARRAY_SIZE(lpphy_5354_iq_table); i++) {
			if (lpphy_5354_iq_table[i].chan == lpphy->channel) {
				iqcomp = &lpphy_5354_iq_table[i];
			}
		}
	} else if (dev->phy.rev >= 2) {
		iqcomp = &lpphy_rev2plus_iq_comp;
	} else {
		for (i = 0; i < ARRAY_SIZE(lpphy_rev0_1_iq_table); i++) {
			if (lpphy_rev0_1_iq_table[i].chan == lpphy->channel) {
				iqcomp = &lpphy_rev0_1_iq_table[i];
			}
		}
	}

	if (B43_WARN_ON(!iqcomp))
		return 0;

	b43_phy_maskset(dev, B43_LPPHY_RX_COMP_COEFF_S, 0xFF00, iqcomp->c1);
	b43_phy_maskset(dev, B43_LPPHY_RX_COMP_COEFF_S,
			0x00FF, iqcomp->c0 << 8);

	if (noise) {
		tx = true;
		rx = false;
		pa = false;
	}

	lpphy_set_trsw_over(dev, tx, rx);

	if (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) {
		b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x8);
		b43_phy_maskset(dev, B43_LPPHY_RF_OVERRIDE_VAL_0,
				0xFFF7, pa << 3);
	} else {
		b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x20);
		b43_phy_maskset(dev, B43_LPPHY_RF_OVERRIDE_VAL_0,
				0xFFDF, pa << 5);
	}

	tmp = b43_phy_read(dev, B43_LPPHY_AFE_CTL_OVR) & 0x40;

	if (noise)
		lpphy_set_rx_gain(dev, 0x2D5D);
	else {
		if (tmp)
			oldgains = lpphy_get_tx_gains(dev);
		if (!gains)
			gains = &nogains;
		lpphy_set_tx_gains(dev, *gains);
	}

	b43_phy_mask(dev, B43_LPPHY_AFE_CTL_OVR, 0xFFFE);
	b43_phy_mask(dev, B43_LPPHY_AFE_CTL_OVRVAL, 0xFFFE);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x800);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0x800);
	lpphy_set_deaf(dev, false);
	if (noise)
		ret = lpphy_calc_rx_iq_comp(dev, 0xFFF0);
	else {
		lpphy_start_tx_tone(dev, 4000, 100);
		ret = lpphy_calc_rx_iq_comp(dev, 0x4000);
		lpphy_stop_tx_tone(dev);
	}
	lpphy_clear_deaf(dev, false);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_0, 0xFFFC);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_0, 0xFFF7);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_0, 0xFFDF);
	if (!noise) {
		if (tmp)
			lpphy_set_tx_gains(dev, oldgains);
		else
			lpphy_disable_tx_gain_override(dev);
	}
	lpphy_disable_rx_gain_override(dev);
	b43_phy_mask(dev, B43_LPPHY_AFE_CTL_OVR, 0xFFFE);
	b43_phy_mask(dev, B43_LPPHY_AFE_CTL_OVRVAL, 0xF7FF);
	return ret;
}