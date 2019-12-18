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
struct TYPE_2__ {int rev; } ;
struct b43_wldev {TYPE_1__ phy; int /*<<< orphan*/  wl; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
typedef  enum n_rssi_type { ____Placeholder_n_rssi_type } n_rssi_type ;

/* Variables and functions */
 int B2056_TX0 ; 
 int B2056_TX1 ; 
 int B2056_TX_TX_SSI_MUX ; 
 int B43_NPHY_AFECTL_C1 ; 
 int B43_NPHY_AFECTL_C2 ; 
 int B43_NPHY_AFECTL_OVER ; 
 int B43_NPHY_AFECTL_OVER1 ; 
 int B43_NPHY_RFCTL_LUT_TRSW_UP1 ; 
 int B43_NPHY_RFCTL_LUT_TRSW_UP2 ; 
 int B43_NPHY_TXF_40CO_B1S0 ; 
 int B43_NPHY_TXF_40CO_B32S1 ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 int N_RSSI_IQ ; 
 int N_RSSI_NB ; 
 int N_RSSI_TBD ; 
 int N_RSSI_W1 ; 
 int N_RSSI_W2 ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 scalar_t__ b43_nphy_ipa (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int,int) ; 

__attribute__((used)) static void b43_nphy_rev3_rssi_select(struct b43_wldev *dev, u8 code,
				      enum n_rssi_type rssi_type)
{
	u8 i;
	u16 reg, val;

	if (code == 0) {
		b43_phy_mask(dev, B43_NPHY_AFECTL_OVER1, 0xFDFF);
		b43_phy_mask(dev, B43_NPHY_AFECTL_OVER, 0xFDFF);
		b43_phy_mask(dev, B43_NPHY_AFECTL_C1, 0xFCFF);
		b43_phy_mask(dev, B43_NPHY_AFECTL_C2, 0xFCFF);
		b43_phy_mask(dev, B43_NPHY_TXF_40CO_B1S0, 0xFFDF);
		b43_phy_mask(dev, B43_NPHY_TXF_40CO_B32S1, 0xFFDF);
		b43_phy_mask(dev, B43_NPHY_RFCTL_LUT_TRSW_UP1, 0xFFC3);
		b43_phy_mask(dev, B43_NPHY_RFCTL_LUT_TRSW_UP2, 0xFFC3);
	} else {
		for (i = 0; i < 2; i++) {
			if ((code == 1 && i == 1) || (code == 2 && !i))
				continue;

			reg = (i == 0) ?
				B43_NPHY_AFECTL_OVER1 : B43_NPHY_AFECTL_OVER;
			b43_phy_maskset(dev, reg, 0xFDFF, 0x0200);

			if (rssi_type == N_RSSI_W1 ||
			    rssi_type == N_RSSI_W2 ||
			    rssi_type == N_RSSI_NB) {
				reg = (i == 0) ?
					B43_NPHY_AFECTL_C1 :
					B43_NPHY_AFECTL_C2;
				b43_phy_maskset(dev, reg, 0xFCFF, 0);

				reg = (i == 0) ?
					B43_NPHY_RFCTL_LUT_TRSW_UP1 :
					B43_NPHY_RFCTL_LUT_TRSW_UP2;
				b43_phy_maskset(dev, reg, 0xFFC3, 0);

				if (rssi_type == N_RSSI_W1)
					val = (b43_current_band(dev->wl) == NL80211_BAND_5GHZ) ? 4 : 8;
				else if (rssi_type == N_RSSI_W2)
					val = 16;
				else
					val = 32;
				b43_phy_set(dev, reg, val);

				reg = (i == 0) ?
					B43_NPHY_TXF_40CO_B1S0 :
					B43_NPHY_TXF_40CO_B32S1;
				b43_phy_set(dev, reg, 0x0020);
			} else {
				if (rssi_type == N_RSSI_TBD)
					val = 0x0100;
				else if (rssi_type == N_RSSI_IQ)
					val = 0x0200;
				else
					val = 0x0300;

				reg = (i == 0) ?
					B43_NPHY_AFECTL_C1 :
					B43_NPHY_AFECTL_C2;

				b43_phy_maskset(dev, reg, 0xFCFF, val);
				b43_phy_maskset(dev, reg, 0xF3FF, val << 2);

				if (rssi_type != N_RSSI_IQ &&
				    rssi_type != N_RSSI_TBD) {
					enum nl80211_band band =
						b43_current_band(dev->wl);

					if (dev->phy.rev < 7) {
						if (b43_nphy_ipa(dev))
							val = (band == NL80211_BAND_5GHZ) ? 0xC : 0xE;
						else
							val = 0x11;
						reg = (i == 0) ? B2056_TX0 : B2056_TX1;
						reg |= B2056_TX_TX_SSI_MUX;
						b43_radio_write(dev, reg, val);
					}

					reg = (i == 0) ?
						B43_NPHY_AFECTL_OVER1 :
						B43_NPHY_AFECTL_OVER;
					b43_phy_set(dev, reg, 0x0200);
				}
			}
		}
	}
}