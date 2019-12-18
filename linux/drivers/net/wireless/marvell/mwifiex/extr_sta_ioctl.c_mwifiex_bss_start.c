#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_6__ {int /*<<< orphan*/  ssid; } ;
struct TYPE_7__ {TYPE_2__ bss_descriptor; } ;
struct TYPE_5__ {int /*<<< orphan*/  authentication_mode; scalar_t__ wep_enabled; scalar_t__ is_authtype_auto; } ;
struct mwifiex_private {int scan_block; scalar_t__ bss_mode; int adhoc_is_link_sensed; int /*<<< orphan*/ * attempted_bss_desc; struct mwifiex_adapter* adapter; int /*<<< orphan*/  netdev; TYPE_3__ curr_bss_params; TYPE_1__ sec_info; scalar_t__ assoc_rsp_size; } ;
struct TYPE_8__ {scalar_t__ ssid_len; } ;
struct mwifiex_bssdescriptor {struct mwifiex_bssdescriptor* beacon_buf; TYPE_4__ ssid; scalar_t__ channel; int /*<<< orphan*/  bss_band; } ;
struct mwifiex_adapter {int region_code; int fw_bands; int config_bands; int /*<<< orphan*/  wiphy; } ;
struct cfg80211_ssid {scalar_t__ ssid; } ;
struct cfg80211_bss {int dummy; } ;

/* Variables and functions */
 int BAND_A ; 
 int BAND_AAC ; 
 int BAND_AN ; 
 int BAND_B ; 
 int BAND_G ; 
 int BAND_GN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HostCmd_SCAN_RADIO_TYPE_BG ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  NL80211_AUTHTYPE_SHARED_KEY ; 
 scalar_t__ NL80211_IFTYPE_P2P_CLIENT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int WLAN_STATUS_NOT_SUPPORTED_AUTH_ALG ; 
 int /*<<< orphan*/  cfg80211_put_bss (int /*<<< orphan*/ ,struct cfg80211_bss*) ; 
 int /*<<< orphan*/  kfree (struct mwifiex_bssdescriptor*) ; 
 struct mwifiex_bssdescriptor* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mwifiex_11h_get_csa_closed_channel (struct mwifiex_private*) ; 
 int mwifiex_adhoc_join (struct mwifiex_private*,struct mwifiex_bssdescriptor*) ; 
 int mwifiex_adhoc_start (struct mwifiex_private*,struct cfg80211_ssid*) ; 
 int mwifiex_associate (struct mwifiex_private*,struct mwifiex_bssdescriptor*) ; 
 scalar_t__ mwifiex_band_to_radio_type (int /*<<< orphan*/ ) ; 
 int mwifiex_check_network_compatibility (struct mwifiex_private*,struct mwifiex_bssdescriptor*) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,...) ; 
 int mwifiex_fill_new_bss_desc (struct mwifiex_private*,struct cfg80211_bss*,struct mwifiex_bssdescriptor*) ; 
 int /*<<< orphan*/  mwifiex_process_country_ie (struct mwifiex_private*,struct cfg80211_bss*) ; 
 int /*<<< orphan*/  mwifiex_ssid_cmp (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  mwifiex_stop_net_dev_queue (int /*<<< orphan*/ ,struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 

int mwifiex_bss_start(struct mwifiex_private *priv, struct cfg80211_bss *bss,
		      struct cfg80211_ssid *req_ssid)
{
	int ret;
	struct mwifiex_adapter *adapter = priv->adapter;
	struct mwifiex_bssdescriptor *bss_desc = NULL;

	priv->scan_block = false;

	if (bss) {
		if (adapter->region_code == 0x00)
			mwifiex_process_country_ie(priv, bss);

		/* Allocate and fill new bss descriptor */
		bss_desc = kzalloc(sizeof(struct mwifiex_bssdescriptor),
				   GFP_KERNEL);
		if (!bss_desc)
			return -ENOMEM;

		ret = mwifiex_fill_new_bss_desc(priv, bss, bss_desc);
		if (ret)
			goto done;
	}

	if (priv->bss_mode == NL80211_IFTYPE_STATION ||
	    priv->bss_mode == NL80211_IFTYPE_P2P_CLIENT) {
		u8 config_bands;

		if (!bss_desc)
			return -1;

		if (mwifiex_band_to_radio_type(bss_desc->bss_band) ==
						HostCmd_SCAN_RADIO_TYPE_BG) {
			config_bands = BAND_B | BAND_G | BAND_GN;
		} else {
			config_bands = BAND_A | BAND_AN;
			if (adapter->fw_bands & BAND_AAC)
				config_bands |= BAND_AAC;
		}

		if (!((config_bands | adapter->fw_bands) & ~adapter->fw_bands))
			adapter->config_bands = config_bands;

		ret = mwifiex_check_network_compatibility(priv, bss_desc);
		if (ret)
			goto done;

		if (mwifiex_11h_get_csa_closed_channel(priv) ==
							(u8)bss_desc->channel) {
			mwifiex_dbg(adapter, ERROR,
				    "Attempt to reconnect on csa closed chan(%d)\n",
				    bss_desc->channel);
			ret = -1;
			goto done;
		}

		mwifiex_dbg(adapter, INFO,
			    "info: SSID found in scan list ...\t"
			    "associating...\n");

		mwifiex_stop_net_dev_queue(priv->netdev, adapter);
		if (netif_carrier_ok(priv->netdev))
			netif_carrier_off(priv->netdev);

		/* Clear any past association response stored for
		 * application retrieval */
		priv->assoc_rsp_size = 0;
		ret = mwifiex_associate(priv, bss_desc);

		/* If auth type is auto and association fails using open mode,
		 * try to connect using shared mode */
		if (ret == WLAN_STATUS_NOT_SUPPORTED_AUTH_ALG &&
		    priv->sec_info.is_authtype_auto &&
		    priv->sec_info.wep_enabled) {
			priv->sec_info.authentication_mode =
						NL80211_AUTHTYPE_SHARED_KEY;
			ret = mwifiex_associate(priv, bss_desc);
		}

		if (bss)
			cfg80211_put_bss(priv->adapter->wiphy, bss);
	} else {
		/* Adhoc mode */
		/* If the requested SSID matches current SSID, return */
		if (bss_desc && bss_desc->ssid.ssid_len &&
		    (!mwifiex_ssid_cmp(&priv->curr_bss_params.bss_descriptor.
				       ssid, &bss_desc->ssid))) {
			ret = 0;
			goto done;
		}

		priv->adhoc_is_link_sensed = false;

		ret = mwifiex_check_network_compatibility(priv, bss_desc);

		mwifiex_stop_net_dev_queue(priv->netdev, adapter);
		if (netif_carrier_ok(priv->netdev))
			netif_carrier_off(priv->netdev);

		if (!ret) {
			mwifiex_dbg(adapter, INFO,
				    "info: network found in scan\t"
				    " list. Joining...\n");
			ret = mwifiex_adhoc_join(priv, bss_desc);
			if (bss)
				cfg80211_put_bss(priv->adapter->wiphy, bss);
		} else {
			mwifiex_dbg(adapter, INFO,
				    "info: Network not found in\t"
				    "the list, creating adhoc with ssid = %s\n",
				    req_ssid->ssid);
			ret = mwifiex_adhoc_start(priv, req_ssid);
		}
	}

done:
	/* beacon_ie buffer was allocated in function
	 * mwifiex_fill_new_bss_desc(). Free it now.
	 */
	if (bss_desc)
		kfree(bss_desc->beacon_buf);
	kfree(bss_desc);

	if (ret < 0)
		priv->attempted_bss_desc = NULL;

	return ret;
}