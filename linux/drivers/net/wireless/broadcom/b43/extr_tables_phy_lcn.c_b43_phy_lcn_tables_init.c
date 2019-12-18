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
struct ssb_sprom {int boardflags_lo; int boardflags_hi; } ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_1__* dev; } ;
struct TYPE_2__ {struct ssb_sprom* bus_sprom; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int B43_BFH_FEM_BT ; 
 int B43_BFL_FEM ; 
 int /*<<< orphan*/  B43_LCNTAB16 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_lcntab_sw_ctl_4313_epa_rev0 ; 
 int /*<<< orphan*/  b43_lcntab_tx_gain_tbl_2ghz_ext_pa_rev0 ; 
 int /*<<< orphan*/  b43_lcntab_write_bulk (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_lcn_clean_papd_comp_table (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_lcn_load_rfpower (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_lcn_load_tx_gain_tab (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_lcn_rewrite_rfpower_table (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_lcn_upload_static_tables (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*) ; 

void b43_phy_lcn_tables_init(struct b43_wldev *dev)
{
	struct ssb_sprom *sprom = dev->dev->bus_sprom;

	b43_phy_lcn_upload_static_tables(dev);

	if (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) {
		if (sprom->boardflags_lo & B43_BFL_FEM)
			b43_phy_lcn_load_tx_gain_tab(dev,
				b43_lcntab_tx_gain_tbl_2ghz_ext_pa_rev0);
		else
			b43err(dev->wl,
			       "TX gain table unknown for this card\n");
	}

	if (sprom->boardflags_lo & B43_BFL_FEM &&
	    !(sprom->boardflags_hi & B43_BFH_FEM_BT))
		b43_lcntab_write_bulk(dev, B43_LCNTAB16(0xf, 0),
			ARRAY_SIZE(b43_lcntab_sw_ctl_4313_epa_rev0),
			b43_lcntab_sw_ctl_4313_epa_rev0);
	else
		b43err(dev->wl, "SW ctl table is unknown for this card\n");

	b43_phy_lcn_load_rfpower(dev);
	b43_phy_lcn_rewrite_rfpower_table(dev);
	b43_phy_lcn_clean_papd_comp_table(dev);
}