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
typedef  size_t u16 ;
struct nphy_txgains {int* tx_lpf; int* txgm; int* pga; int* pad; int* ipa; } ;
struct nphy_iqcal_params {int tx_lpf; int txgm; int pga; int pad; int ipa; int cal_gain; int* ncorr; } ;
struct b43_phy {int rev; } ;
struct b43_wldev {int /*<<< orphan*/  wl; struct b43_phy phy; } ;

/* Variables and functions */
 scalar_t__ NL80211_BAND_5GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 size_t*** tbl_iqcal_gainparams ; 

__attribute__((used)) static void b43_nphy_iq_cal_gain_params(struct b43_wldev *dev, u16 core,
					struct nphy_txgains target,
					struct nphy_iqcal_params *params)
{
	struct b43_phy *phy = &dev->phy;
	int i, j, indx;
	u16 gain;

	if (dev->phy.rev >= 3) {
		params->tx_lpf = target.tx_lpf[core]; /* Rev 7+ */
		params->txgm = target.txgm[core];
		params->pga = target.pga[core];
		params->pad = target.pad[core];
		params->ipa = target.ipa[core];
		if (phy->rev >= 19) {
			/* TODO */
		} else if (phy->rev >= 7) {
			params->cal_gain = (params->txgm << 12) | (params->pga << 8) | (params->pad << 3) | (params->ipa) | (params->tx_lpf << 15);
		} else {
			params->cal_gain = (params->txgm << 12) | (params->pga << 8) | (params->pad << 4) | (params->ipa);
		}
		for (j = 0; j < 5; j++)
			params->ncorr[j] = 0x79;
	} else {
		gain = (target.pad[core]) | (target.pga[core] << 4) |
			(target.txgm[core] << 8);

		indx = (b43_current_band(dev->wl) == NL80211_BAND_5GHZ) ?
			1 : 0;
		for (i = 0; i < 9; i++)
			if (tbl_iqcal_gainparams[indx][i][0] == gain)
				break;
		i = min(i, 8);

		params->txgm = tbl_iqcal_gainparams[indx][i][1];
		params->pga = tbl_iqcal_gainparams[indx][i][2];
		params->pad = tbl_iqcal_gainparams[indx][i][3];
		params->cal_gain = (params->txgm << 7) | (params->pga << 4) |
					(params->pad << 2);
		for (j = 0; j < 4; j++)
			params->ncorr[j] = tbl_iqcal_gainparams[indx][i][4 + j];
	}
}