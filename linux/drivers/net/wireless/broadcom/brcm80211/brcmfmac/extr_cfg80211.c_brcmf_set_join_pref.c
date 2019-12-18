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
struct TYPE_3__ {int band; scalar_t__ delta; } ;
struct TYPE_4__ {int band_pref; TYPE_1__ adjust; } ;
struct cfg80211_bss_selection {int behaviour; TYPE_2__ param; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_join_pref_params {int len; void* band; scalar_t__ rssi_gain; int /*<<< orphan*/  type; } ;
struct brcmf_if {struct brcmf_pub* drvr; } ;
typedef  int /*<<< orphan*/  join_pref_params ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_C_SET_ASSOC_PREFER ; 
 int /*<<< orphan*/  BRCMF_JOIN_PREF_BAND ; 
 int /*<<< orphan*/  BRCMF_JOIN_PREF_RSSI ; 
 int /*<<< orphan*/  BRCMF_JOIN_PREF_RSSI_DELTA ; 
#define  NL80211_BSS_SELECT_ATTR_BAND_PREF 131 
#define  NL80211_BSS_SELECT_ATTR_RSSI 130 
#define  NL80211_BSS_SELECT_ATTR_RSSI_ADJUST 129 
 int /*<<< orphan*/  WLC_BAND_AUTO ; 
#define  __NL80211_BSS_SELECT_ATTR_INVALID 128 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,int) ; 
 int /*<<< orphan*/  brcmf_c_set_joinpref_default (struct brcmf_if*) ; 
 int /*<<< orphan*/  brcmf_fil_cmd_int_set (struct brcmf_if*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int brcmf_fil_iovar_data_set (struct brcmf_if*,char*,struct brcmf_join_pref_params*,int) ; 
 void* nl80211_band_to_fwil (int) ; 

__attribute__((used)) static void brcmf_set_join_pref(struct brcmf_if *ifp,
				struct cfg80211_bss_selection *bss_select)
{
	struct brcmf_pub *drvr = ifp->drvr;
	struct brcmf_join_pref_params join_pref_params[2];
	enum nl80211_band band;
	int err, i = 0;

	join_pref_params[i].len = 2;
	join_pref_params[i].rssi_gain = 0;

	if (bss_select->behaviour != NL80211_BSS_SELECT_ATTR_BAND_PREF)
		brcmf_fil_cmd_int_set(ifp, BRCMF_C_SET_ASSOC_PREFER, WLC_BAND_AUTO);

	switch (bss_select->behaviour) {
	case __NL80211_BSS_SELECT_ATTR_INVALID:
		brcmf_c_set_joinpref_default(ifp);
		return;
	case NL80211_BSS_SELECT_ATTR_BAND_PREF:
		join_pref_params[i].type = BRCMF_JOIN_PREF_BAND;
		band = bss_select->param.band_pref;
		join_pref_params[i].band = nl80211_band_to_fwil(band);
		i++;
		break;
	case NL80211_BSS_SELECT_ATTR_RSSI_ADJUST:
		join_pref_params[i].type = BRCMF_JOIN_PREF_RSSI_DELTA;
		band = bss_select->param.adjust.band;
		join_pref_params[i].band = nl80211_band_to_fwil(band);
		join_pref_params[i].rssi_gain = bss_select->param.adjust.delta;
		i++;
		break;
	case NL80211_BSS_SELECT_ATTR_RSSI:
	default:
		break;
	}
	join_pref_params[i].type = BRCMF_JOIN_PREF_RSSI;
	join_pref_params[i].len = 2;
	join_pref_params[i].rssi_gain = 0;
	join_pref_params[i].band = 0;
	err = brcmf_fil_iovar_data_set(ifp, "join_pref", join_pref_params,
				       sizeof(join_pref_params));
	if (err)
		bphy_err(drvr, "Set join_pref error (%d)\n", err);
}