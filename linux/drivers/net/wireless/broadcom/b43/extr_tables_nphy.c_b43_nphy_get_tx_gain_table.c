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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_9__ {int extpa_gain; } ;
struct TYPE_8__ {int extpa_gain; } ;
struct TYPE_10__ {TYPE_4__ ghz2; TYPE_3__ ghz5; } ;
struct ssb_sprom {TYPE_5__ fem; } ;
struct b43_phy {int rev; TYPE_2__* n; } ;
struct b43_wldev {int /*<<< orphan*/  wl; struct b43_phy phy; TYPE_1__* dev; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_7__ {scalar_t__ ipa5g_on; scalar_t__ ipa2g_on; } ;
struct TYPE_6__ {struct ssb_sprom* bus_sprom; } ;

/* Variables and functions */
 int NL80211_BAND_2GHZ ; 
 int NL80211_BAND_5GHZ ; 
 int b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* b43_nphy_get_ipa_gain_table (struct b43_wldev*) ; 
 int /*<<< orphan*/  const* b43_ntab_tx_gain_epa_rev3_2g ; 
 int /*<<< orphan*/  const* b43_ntab_tx_gain_epa_rev3_5g ; 
 int /*<<< orphan*/  const* b43_ntab_tx_gain_epa_rev3_hi_pwr_2g ; 
 int /*<<< orphan*/  const* b43_ntab_tx_gain_epa_rev4_5g ; 
 int /*<<< orphan*/  const* b43_ntab_tx_gain_epa_rev4_hi_pwr_5g ; 
 int /*<<< orphan*/  const* b43_ntab_tx_gain_epa_rev5_5g ; 
 int /*<<< orphan*/  const* b43_ntab_tx_gain_rev0_1_2 ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*) ; 

const u32 *b43_nphy_get_tx_gain_table(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	enum nl80211_band band = b43_current_band(dev->wl);
	struct ssb_sprom *sprom = dev->dev->bus_sprom;

	if (dev->phy.rev < 3)
		return b43_ntab_tx_gain_rev0_1_2;

	/* rev 3+ */
	if ((dev->phy.n->ipa2g_on && band == NL80211_BAND_2GHZ) ||
	    (dev->phy.n->ipa5g_on && band == NL80211_BAND_5GHZ)) {
		return b43_nphy_get_ipa_gain_table(dev);
	} else if (b43_current_band(dev->wl) == NL80211_BAND_5GHZ) {
		switch (phy->rev) {
		case 6:
		case 5:
			return b43_ntab_tx_gain_epa_rev5_5g;
		case 4:
			return sprom->fem.ghz5.extpa_gain == 3 ?
				b43_ntab_tx_gain_epa_rev4_5g :
				b43_ntab_tx_gain_epa_rev4_hi_pwr_5g;
		case 3:
			return b43_ntab_tx_gain_epa_rev3_5g;
		default:
			b43err(dev->wl,
			       "No 5GHz EPA gain table available for this device\n");
			return NULL;
		}
	} else {
		switch (phy->rev) {
		case 6:
		case 5:
			if (sprom->fem.ghz2.extpa_gain == 3)
				return b43_ntab_tx_gain_epa_rev3_hi_pwr_2g;
			/* fall through */
		case 4:
		case 3:
			return b43_ntab_tx_gain_epa_rev3_2g;
		default:
			b43err(dev->wl,
			       "No 2GHz EPA gain table available for this device\n");
			return NULL;
		}
	}
}