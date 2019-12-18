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
typedef  int u16 ;
struct TYPE_2__ {int rev; int channel; } ;
struct b43_wldev {TYPE_1__ phy; int /*<<< orphan*/  wl; } ;
typedef  int s16 ;

/* Variables and functions */
 scalar_t__ NL80211_BAND_5GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 scalar_t__ b43_is_40mhz (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_pa_set_tx_dig_filter (struct b43_wldev*,int const,int const*) ; 
 int const** tbl_tx_filter_coef_rev4 ; 

__attribute__((used)) static void b43_nphy_int_pa_set_tx_dig_filters(struct b43_wldev *dev)
{
	/* B43_NPHY_TXF_20CO_S0A1, B43_NPHY_TXF_40CO_S0A1, unknown */
	static const u16 offset[] = { 0x186, 0x195, 0x2C5 };
	static const s16 dig_filter_phy_rev16[] = {
		-375, 136, -407, 208, -1527,
		956, 93, 186, 93, 230,
		-44, 230, 201, -191, 201,
	};
	int i;

	for (i = 0; i < 3; i++)
		b43_nphy_pa_set_tx_dig_filter(dev, offset[i],
					      tbl_tx_filter_coef_rev4[i]);

	/* Verified with BCM43227 and BCM43228 */
	if (dev->phy.rev == 16)
		b43_nphy_pa_set_tx_dig_filter(dev, 0x186, dig_filter_phy_rev16);

	/* Verified with BCM43131 and BCM43217 */
	if (dev->phy.rev == 17) {
		b43_nphy_pa_set_tx_dig_filter(dev, 0x186, dig_filter_phy_rev16);
		b43_nphy_pa_set_tx_dig_filter(dev, 0x195,
					      tbl_tx_filter_coef_rev4[1]);
	}

	if (b43_is_40mhz(dev)) {
		b43_nphy_pa_set_tx_dig_filter(dev, 0x186,
					      tbl_tx_filter_coef_rev4[3]);
	} else {
		if (b43_current_band(dev->wl) == NL80211_BAND_5GHZ)
			b43_nphy_pa_set_tx_dig_filter(dev, 0x186,
						      tbl_tx_filter_coef_rev4[5]);
		if (dev->phy.channel == 14)
			b43_nphy_pa_set_tx_dig_filter(dev, 0x186,
						      tbl_tx_filter_coef_rev4[6]);
	}
}