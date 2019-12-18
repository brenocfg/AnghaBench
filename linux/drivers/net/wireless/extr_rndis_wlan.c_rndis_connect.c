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
struct wiphy {int dummy; } ;
struct usbnet {int /*<<< orphan*/  net; } ;
struct rndis_wlan_private {int /*<<< orphan*/  encr_tx_key_index; struct usbnet* usbdev; } ;
struct net_device {int dummy; } ;
struct ndis_80211_ssid {int /*<<< orphan*/  essid; int /*<<< orphan*/  length; } ;
struct ieee80211_channel {int /*<<< orphan*/  center_freq; } ;
struct TYPE_2__ {int n_ciphers_pairwise; int n_akm_suites; int /*<<< orphan*/  wpa_versions; int /*<<< orphan*/ * akm_suites; int /*<<< orphan*/ * ciphers_pairwise; int /*<<< orphan*/  cipher_group; } ;
struct cfg80211_connect_params {int ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  bssid; int /*<<< orphan*/  key_idx; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  auth_type; TYPE_1__ crypto; int /*<<< orphan*/  privacy; struct ieee80211_channel* channel; } ;
typedef  int /*<<< orphan*/  ssid ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  NDIS_80211_INFRA_INFRA ; 
 int NDIS_802_11_LENGTH_SSID ; 
 int RNDIS_WLAN_ALG_NONE ; 
 int RNDIS_WLAN_ALG_WEP ; 
 int RNDIS_WLAN_KEY_MGMT_NONE ; 
 int add_wep_key (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bssid (struct usbnet*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  disassociate (struct usbnet*,int) ; 
 int ieee80211_frequency_to_channel (int /*<<< orphan*/ ) ; 
 scalar_t__ is_associated (struct usbnet*) ; 
 int /*<<< orphan*/  is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ndis_80211_ssid*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int rndis_akm_suite_to_key_mgmt (int /*<<< orphan*/ ) ; 
 int rndis_cipher_to_alg (int /*<<< orphan*/ ) ; 
 int set_auth_mode (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int set_bssid (struct usbnet*,int /*<<< orphan*/ ) ; 
 int set_channel (struct usbnet*,int) ; 
 int set_encr_mode (struct usbnet*,int,int) ; 
 int set_essid (struct usbnet*,struct ndis_80211_ssid*) ; 
 int set_infra_mode (struct usbnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_priv_filter (struct usbnet*) ; 
 int /*<<< orphan*/  usbnet_pause_rx (struct usbnet*) ; 
 int /*<<< orphan*/  usbnet_purge_paused_rxq (struct usbnet*) ; 
 struct rndis_wlan_private* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int rndis_connect(struct wiphy *wiphy, struct net_device *dev,
					struct cfg80211_connect_params *sme)
{
	struct rndis_wlan_private *priv = wiphy_priv(wiphy);
	struct usbnet *usbdev = priv->usbdev;
	struct ieee80211_channel *channel = sme->channel;
	struct ndis_80211_ssid ssid;
	int pairwise = RNDIS_WLAN_ALG_NONE;
	int groupwise = RNDIS_WLAN_ALG_NONE;
	int keymgmt = RNDIS_WLAN_KEY_MGMT_NONE;
	int length, i, ret, chan = -1;

	if (channel)
		chan = ieee80211_frequency_to_channel(channel->center_freq);

	groupwise = rndis_cipher_to_alg(sme->crypto.cipher_group);
	for (i = 0; i < sme->crypto.n_ciphers_pairwise; i++)
		pairwise |=
			rndis_cipher_to_alg(sme->crypto.ciphers_pairwise[i]);

	if (sme->crypto.n_ciphers_pairwise > 0 &&
			pairwise == RNDIS_WLAN_ALG_NONE) {
		netdev_err(usbdev->net, "Unsupported pairwise cipher\n");
		return -ENOTSUPP;
	}

	for (i = 0; i < sme->crypto.n_akm_suites; i++)
		keymgmt |=
			rndis_akm_suite_to_key_mgmt(sme->crypto.akm_suites[i]);

	if (sme->crypto.n_akm_suites > 0 &&
			keymgmt == RNDIS_WLAN_KEY_MGMT_NONE) {
		netdev_err(usbdev->net, "Invalid keymgmt\n");
		return -ENOTSUPP;
	}

	netdev_dbg(usbdev->net, "cfg80211.connect('%.32s':[%pM]:%d:[%d,0x%x:0x%x]:[0x%x:0x%x]:0x%x)\n",
		   sme->ssid, sme->bssid, chan,
		   sme->privacy, sme->crypto.wpa_versions, sme->auth_type,
		   groupwise, pairwise, keymgmt);

	if (is_associated(usbdev))
		disassociate(usbdev, false);

	ret = set_infra_mode(usbdev, NDIS_80211_INFRA_INFRA);
	if (ret < 0) {
		netdev_dbg(usbdev->net, "connect: set_infra_mode failed, %d\n",
			   ret);
		goto err_turn_radio_on;
	}

	ret = set_auth_mode(usbdev, sme->crypto.wpa_versions, sme->auth_type,
								keymgmt);
	if (ret < 0) {
		netdev_dbg(usbdev->net, "connect: set_auth_mode failed, %d\n",
			   ret);
		goto err_turn_radio_on;
	}

	set_priv_filter(usbdev);

	ret = set_encr_mode(usbdev, pairwise, groupwise);
	if (ret < 0) {
		netdev_dbg(usbdev->net, "connect: set_encr_mode failed, %d\n",
			   ret);
		goto err_turn_radio_on;
	}

	if (channel) {
		ret = set_channel(usbdev, chan);
		if (ret < 0) {
			netdev_dbg(usbdev->net, "connect: set_channel failed, %d\n",
				   ret);
			goto err_turn_radio_on;
		}
	}

	if (sme->key && ((groupwise | pairwise) & RNDIS_WLAN_ALG_WEP)) {
		priv->encr_tx_key_index = sme->key_idx;
		ret = add_wep_key(usbdev, sme->key, sme->key_len, sme->key_idx);
		if (ret < 0) {
			netdev_dbg(usbdev->net, "connect: add_wep_key failed, %d (%d, %d)\n",
				   ret, sme->key_len, sme->key_idx);
			goto err_turn_radio_on;
		}
	}

	if (sme->bssid && !is_zero_ether_addr(sme->bssid) &&
				!is_broadcast_ether_addr(sme->bssid)) {
		ret = set_bssid(usbdev, sme->bssid);
		if (ret < 0) {
			netdev_dbg(usbdev->net, "connect: set_bssid failed, %d\n",
				   ret);
			goto err_turn_radio_on;
		}
	} else
		clear_bssid(usbdev);

	length = sme->ssid_len;
	if (length > NDIS_802_11_LENGTH_SSID)
		length = NDIS_802_11_LENGTH_SSID;

	memset(&ssid, 0, sizeof(ssid));
	ssid.length = cpu_to_le32(length);
	memcpy(ssid.essid, sme->ssid, length);

	/* Pause and purge rx queue, so we don't pass packets before
	 * 'media connect'-indication.
	 */
	usbnet_pause_rx(usbdev);
	usbnet_purge_paused_rxq(usbdev);

	ret = set_essid(usbdev, &ssid);
	if (ret < 0)
		netdev_dbg(usbdev->net, "connect: set_essid failed, %d\n", ret);
	return ret;

err_turn_radio_on:
	disassociate(usbdev, true);

	return ret;
}