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
struct brcmf_pub {int dummy; } ;
struct brcmf_if {struct brcmf_pub* drvr; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int WLC_BAND_2G ; 
 int WLC_BAND_5G ; 
 int WLC_BW_20MHZ_BIT ; 
 int WLC_BW_40MHZ_BIT ; 
#define  WLC_N_BW_20ALL 130 
#define  WLC_N_BW_20IN2G_40IN5G 129 
#define  WLC_N_BW_40ALL 128 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int brcmf_fil_iovar_int_get (struct brcmf_if*,char*,int*) ; 

__attribute__((used)) static void brcmf_get_bwcap(struct brcmf_if *ifp, u32 bw_cap[])
{
	struct brcmf_pub *drvr = ifp->drvr;
	u32 band, mimo_bwcap;
	int err;

	band = WLC_BAND_2G;
	err = brcmf_fil_iovar_int_get(ifp, "bw_cap", &band);
	if (!err) {
		bw_cap[NL80211_BAND_2GHZ] = band;
		band = WLC_BAND_5G;
		err = brcmf_fil_iovar_int_get(ifp, "bw_cap", &band);
		if (!err) {
			bw_cap[NL80211_BAND_5GHZ] = band;
			return;
		}
		WARN_ON(1);
		return;
	}
	brcmf_dbg(INFO, "fallback to mimo_bw_cap info\n");
	mimo_bwcap = 0;
	err = brcmf_fil_iovar_int_get(ifp, "mimo_bw_cap", &mimo_bwcap);
	if (err)
		/* assume 20MHz if firmware does not give a clue */
		mimo_bwcap = WLC_N_BW_20ALL;

	switch (mimo_bwcap) {
	case WLC_N_BW_40ALL:
		bw_cap[NL80211_BAND_2GHZ] |= WLC_BW_40MHZ_BIT;
		/* fall-thru */
	case WLC_N_BW_20IN2G_40IN5G:
		bw_cap[NL80211_BAND_5GHZ] |= WLC_BW_40MHZ_BIT;
		/* fall-thru */
	case WLC_N_BW_20ALL:
		bw_cap[NL80211_BAND_2GHZ] |= WLC_BW_20MHZ_BIT;
		bw_cap[NL80211_BAND_5GHZ] |= WLC_BW_20MHZ_BIT;
		break;
	default:
		bphy_err(drvr, "invalid mimo_bw_cap value\n");
	}
}