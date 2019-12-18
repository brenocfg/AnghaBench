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
struct wiphy {TYPE_2__** bands; } ;
struct wil6210_priv {int /*<<< orphan*/  fw_capabilities; } ;
struct TYPE_3__ {int /*<<< orphan*/  bw_config; int /*<<< orphan*/  channels; } ;
struct TYPE_4__ {TYPE_1__ edmg_cap; int /*<<< orphan*/  n_channels; } ;

/* Variables and functions */
 size_t NL80211_BAND_60GHZ ; 
 int /*<<< orphan*/  WIL_EDMG_BW_CONFIGURATION ; 
 int /*<<< orphan*/  WIL_EDMG_CHANNELS ; 
 int /*<<< orphan*/  WMI_FW_CAPABILITY_CHANNEL_BONDING ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_num_supported_channels (struct wil6210_priv*) ; 
 struct wiphy* wil_to_wiphy (struct wil6210_priv*) ; 

void update_supported_bands(struct wil6210_priv *wil)
{
	struct wiphy *wiphy = wil_to_wiphy(wil);

	wil_dbg_misc(wil, "update supported bands");

	wiphy->bands[NL80211_BAND_60GHZ]->n_channels =
						wil_num_supported_channels(wil);

	if (test_bit(WMI_FW_CAPABILITY_CHANNEL_BONDING, wil->fw_capabilities)) {
		wiphy->bands[NL80211_BAND_60GHZ]->edmg_cap.channels =
							WIL_EDMG_CHANNELS;
		wiphy->bands[NL80211_BAND_60GHZ]->edmg_cap.bw_config =
						      WIL_EDMG_BW_CONFIGURATION;
	}
}