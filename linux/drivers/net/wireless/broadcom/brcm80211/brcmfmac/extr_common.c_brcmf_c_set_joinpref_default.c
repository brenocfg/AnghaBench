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
struct brcmf_pub {int dummy; } ;
struct brcmf_join_pref_params {int len; scalar_t__ band; scalar_t__ rssi_gain; int /*<<< orphan*/  type; } ;
struct brcmf_if {struct brcmf_pub* drvr; } ;
typedef  int /*<<< orphan*/  join_pref_params ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_JOIN_PREF_RSSI ; 
 scalar_t__ BRCMF_JOIN_PREF_RSSI_BOOST ; 
 int /*<<< orphan*/  BRCMF_JOIN_PREF_RSSI_DELTA ; 
 scalar_t__ WLC_BAND_5G ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,int) ; 
 int brcmf_fil_iovar_data_set (struct brcmf_if*,char*,struct brcmf_join_pref_params*,int) ; 

void brcmf_c_set_joinpref_default(struct brcmf_if *ifp)
{
	struct brcmf_pub *drvr = ifp->drvr;
	struct brcmf_join_pref_params join_pref_params[2];
	int err;

	/* Setup join_pref to select target by RSSI (boost on 5GHz) */
	join_pref_params[0].type = BRCMF_JOIN_PREF_RSSI_DELTA;
	join_pref_params[0].len = 2;
	join_pref_params[0].rssi_gain = BRCMF_JOIN_PREF_RSSI_BOOST;
	join_pref_params[0].band = WLC_BAND_5G;

	join_pref_params[1].type = BRCMF_JOIN_PREF_RSSI;
	join_pref_params[1].len = 2;
	join_pref_params[1].rssi_gain = 0;
	join_pref_params[1].band = 0;
	err = brcmf_fil_iovar_data_set(ifp, "join_pref", join_pref_params,
				       sizeof(join_pref_params));
	if (err)
		bphy_err(drvr, "Set join_pref error (%d)\n", err);
}