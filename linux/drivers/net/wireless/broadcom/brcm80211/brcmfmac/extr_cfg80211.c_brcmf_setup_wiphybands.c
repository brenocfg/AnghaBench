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
typedef  int u32 ;
struct wiphy {struct ieee80211_supported_band** bands; } ;
struct ieee80211_supported_band {int dummy; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_if {int dummy; } ;
struct brcmf_cfg80211_info {struct brcmf_pub* pub; } ;
typedef  size_t s32 ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct ieee80211_supported_band**) ; 
 int /*<<< orphan*/  INFO ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 int WLC_BW_20MHZ_BIT ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,int) ; 
 int brcmf_construct_chaninfo (struct brcmf_cfg80211_info*,int*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int brcmf_fil_iovar_int_get (struct brcmf_if*,char*,int*) ; 
 int /*<<< orphan*/  brcmf_get_bwcap (struct brcmf_if*,int*) ; 
 struct brcmf_if* brcmf_get_ifp (struct brcmf_pub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_update_ht_cap (struct ieee80211_supported_band*,int*,int) ; 
 int /*<<< orphan*/  brcmf_update_vht_cap (struct ieee80211_supported_band*,int*,int,int,int,int) ; 
 struct wiphy* cfg_to_wiphy (struct brcmf_cfg80211_info*) ; 

__attribute__((used)) static int brcmf_setup_wiphybands(struct brcmf_cfg80211_info *cfg)
{
	struct brcmf_pub *drvr = cfg->pub;
	struct brcmf_if *ifp = brcmf_get_ifp(drvr, 0);
	struct wiphy *wiphy = cfg_to_wiphy(cfg);
	u32 nmode = 0;
	u32 vhtmode = 0;
	u32 bw_cap[2] = { WLC_BW_20MHZ_BIT, WLC_BW_20MHZ_BIT };
	u32 rxchain;
	u32 nchain;
	int err;
	s32 i;
	struct ieee80211_supported_band *band;
	u32 txstreams = 0;
	u32 txbf_bfe_cap = 0;
	u32 txbf_bfr_cap = 0;

	(void)brcmf_fil_iovar_int_get(ifp, "vhtmode", &vhtmode);
	err = brcmf_fil_iovar_int_get(ifp, "nmode", &nmode);
	if (err) {
		bphy_err(drvr, "nmode error (%d)\n", err);
	} else {
		brcmf_get_bwcap(ifp, bw_cap);
	}
	brcmf_dbg(INFO, "nmode=%d, vhtmode=%d, bw_cap=(%d, %d)\n",
		  nmode, vhtmode, bw_cap[NL80211_BAND_2GHZ],
		  bw_cap[NL80211_BAND_5GHZ]);

	err = brcmf_fil_iovar_int_get(ifp, "rxchain", &rxchain);
	if (err) {
		bphy_err(drvr, "rxchain error (%d)\n", err);
		nchain = 1;
	} else {
		for (nchain = 0; rxchain; nchain++)
			rxchain = rxchain & (rxchain - 1);
	}
	brcmf_dbg(INFO, "nchain=%d\n", nchain);

	err = brcmf_construct_chaninfo(cfg, bw_cap);
	if (err) {
		bphy_err(drvr, "brcmf_construct_chaninfo failed (%d)\n", err);
		return err;
	}

	if (vhtmode) {
		(void)brcmf_fil_iovar_int_get(ifp, "txstreams", &txstreams);
		(void)brcmf_fil_iovar_int_get(ifp, "txbf_bfe_cap",
					      &txbf_bfe_cap);
		(void)brcmf_fil_iovar_int_get(ifp, "txbf_bfr_cap",
					      &txbf_bfr_cap);
	}

	for (i = 0; i < ARRAY_SIZE(wiphy->bands); i++) {
		band = wiphy->bands[i];
		if (band == NULL)
			continue;

		if (nmode)
			brcmf_update_ht_cap(band, bw_cap, nchain);
		if (vhtmode)
			brcmf_update_vht_cap(band, bw_cap, nchain, txstreams,
					     txbf_bfe_cap, txbf_bfr_cap);
	}

	return 0;
}