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
typedef  void* u8 ;
typedef  int u32 ;
typedef  void* u16 ;
struct ssb_sprom {int ofdm2gpo; int ofdm5glpo; int ofdm5gpo; int ofdm5ghpo; void* maxpwr_ah; void* maxpwr_a; void* maxpwr_al; int /*<<< orphan*/  pa1hib2; int /*<<< orphan*/  pa1hib1; int /*<<< orphan*/  pa1hib0; int /*<<< orphan*/  pa1lob2; int /*<<< orphan*/  pa1lob1; int /*<<< orphan*/  pa1lob0; int /*<<< orphan*/  pa1b2; int /*<<< orphan*/  pa1b1; int /*<<< orphan*/  pa1b0; int /*<<< orphan*/  rssisav5g; int /*<<< orphan*/  rssismc5g; int /*<<< orphan*/  rssismf5g; int /*<<< orphan*/  rxpo5g; int /*<<< orphan*/  bxa5g; int /*<<< orphan*/  tri5gh; int /*<<< orphan*/  tri5g; int /*<<< orphan*/  tri5gl; void* opo; void* cck2gpo; void* maxpwr_bg; int /*<<< orphan*/  pa0b2; int /*<<< orphan*/  pa0b1; int /*<<< orphan*/  pa0b0; int /*<<< orphan*/  rssisav2g; int /*<<< orphan*/  rssismc2g; int /*<<< orphan*/  rssismf2g; int /*<<< orphan*/  rxpo2g; int /*<<< orphan*/  bxa2g; int /*<<< orphan*/  tri2g; } ;
struct TYPE_4__ {struct b43_phy_lp* lp; } ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_2__ phy; TYPE_1__* dev; } ;
struct b43_phy_lp {void** tx_max_rateh; void* max_tx_pwr_hi_band; void** tx_max_rate; void* max_tx_pwr_med_band; void** tx_max_ratel; void* max_tx_pwr_low_band; int /*<<< orphan*/ * txpah; int /*<<< orphan*/ * txpal; int /*<<< orphan*/ * txpa; int /*<<< orphan*/  rssi_gs; int /*<<< orphan*/  rssi_vc; int /*<<< orphan*/  rssi_vf; int /*<<< orphan*/  rx_pwr_offset; int /*<<< orphan*/  bx_arch; int /*<<< orphan*/  tx_isolation_hi_band; int /*<<< orphan*/  tx_isolation_med_band; int /*<<< orphan*/  tx_isolation_low_band; } ;
struct TYPE_3__ {struct ssb_sprom* bus_sprom; } ;

/* Variables and functions */
 scalar_t__ NL80211_BAND_2GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lpphy_read_band_sprom(struct b43_wldev *dev)
{
	struct ssb_sprom *sprom = dev->dev->bus_sprom;
	struct b43_phy_lp *lpphy = dev->phy.lp;
	u16 cckpo, maxpwr;
	u32 ofdmpo;
	int i;

	if (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) {
		lpphy->tx_isolation_med_band = sprom->tri2g;
		lpphy->bx_arch = sprom->bxa2g;
		lpphy->rx_pwr_offset = sprom->rxpo2g;
		lpphy->rssi_vf = sprom->rssismf2g;
		lpphy->rssi_vc = sprom->rssismc2g;
		lpphy->rssi_gs = sprom->rssisav2g;
		lpphy->txpa[0] = sprom->pa0b0;
		lpphy->txpa[1] = sprom->pa0b1;
		lpphy->txpa[2] = sprom->pa0b2;
		maxpwr = sprom->maxpwr_bg;
		lpphy->max_tx_pwr_med_band = maxpwr;
		cckpo = sprom->cck2gpo;
		if (cckpo) {
			ofdmpo = sprom->ofdm2gpo;
			for (i = 0; i < 4; i++) {
				lpphy->tx_max_rate[i] =
					maxpwr - (ofdmpo & 0xF) * 2;
				ofdmpo >>= 4;
			}
			ofdmpo = sprom->ofdm2gpo;
			for (i = 4; i < 15; i++) {
				lpphy->tx_max_rate[i] =
					maxpwr - (ofdmpo & 0xF) * 2;
				ofdmpo >>= 4;
			}
		} else {
			u8 opo = sprom->opo;
			for (i = 0; i < 4; i++)
				lpphy->tx_max_rate[i] = maxpwr;
			for (i = 4; i < 15; i++)
				lpphy->tx_max_rate[i] = maxpwr - opo;
		}
	} else { /* 5GHz */
		lpphy->tx_isolation_low_band = sprom->tri5gl;
		lpphy->tx_isolation_med_band = sprom->tri5g;
		lpphy->tx_isolation_hi_band = sprom->tri5gh;
		lpphy->bx_arch = sprom->bxa5g;
		lpphy->rx_pwr_offset = sprom->rxpo5g;
		lpphy->rssi_vf = sprom->rssismf5g;
		lpphy->rssi_vc = sprom->rssismc5g;
		lpphy->rssi_gs = sprom->rssisav5g;
		lpphy->txpa[0] = sprom->pa1b0;
		lpphy->txpa[1] = sprom->pa1b1;
		lpphy->txpa[2] = sprom->pa1b2;
		lpphy->txpal[0] = sprom->pa1lob0;
		lpphy->txpal[1] = sprom->pa1lob1;
		lpphy->txpal[2] = sprom->pa1lob2;
		lpphy->txpah[0] = sprom->pa1hib0;
		lpphy->txpah[1] = sprom->pa1hib1;
		lpphy->txpah[2] = sprom->pa1hib2;
		maxpwr = sprom->maxpwr_al;
		ofdmpo = sprom->ofdm5glpo;
		lpphy->max_tx_pwr_low_band = maxpwr;
		for (i = 4; i < 12; i++) {
			lpphy->tx_max_ratel[i] = maxpwr - (ofdmpo & 0xF) * 2;
			ofdmpo >>= 4;
		}
		maxpwr = sprom->maxpwr_a;
		ofdmpo = sprom->ofdm5gpo;
		lpphy->max_tx_pwr_med_band = maxpwr;
		for (i = 4; i < 12; i++) {
			lpphy->tx_max_rate[i] = maxpwr - (ofdmpo & 0xF) * 2;
			ofdmpo >>= 4;
		}
		maxpwr = sprom->maxpwr_ah;
		ofdmpo = sprom->ofdm5ghpo;
		lpphy->max_tx_pwr_hi_band = maxpwr;
		for (i = 4; i < 12; i++) {
			lpphy->tx_max_rateh[i] = maxpwr - (ofdmpo & 0xF) * 2;
			ofdmpo >>= 4;
		}
	}
}