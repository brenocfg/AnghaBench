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
typedef  int /*<<< orphan*/  u8 ;
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct lbs_private {size_t wep_tx_key; int /*<<< orphan*/  mac_control; int /*<<< orphan*/ * wep_key; int /*<<< orphan*/ * wep_key_len; int /*<<< orphan*/ * scan_req; int /*<<< orphan*/  scan_q; struct net_device* mesh_dev; } ;
struct cfg80211_scan_request {int dummy; } ;
struct TYPE_2__ {int cipher_group; } ;
struct cfg80211_connect_params {int bssid; size_t key_idx; int auth_type; TYPE_1__ crypto; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  channel; } ;
struct cfg80211_bss {int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ACT_MAC_WEP_ENABLE ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOTSUPP ; 
 int EOPNOTSUPP ; 
 int HZ ; 
 int /*<<< orphan*/  IEEE80211_BSS_TYPE_ESS ; 
 int /*<<< orphan*/  IEEE80211_PRIVACY_ANY ; 
 int /*<<< orphan*/  KEY_INFO_WPA_MCAST ; 
 int /*<<< orphan*/  KEY_INFO_WPA_UNICAST ; 
 int /*<<< orphan*/  KEY_TYPE_ID_WEP ; 
 int /*<<< orphan*/  RADIO_PREAMBLE_SHORT ; 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int /*<<< orphan*/  _internal_start_scan (struct lbs_private*,int,struct cfg80211_scan_request*) ; 
 struct cfg80211_scan_request* _new_connect_scan_req (struct wiphy*,struct cfg80211_connect_params*) ; 
 struct cfg80211_bss* cfg80211_get_bss (struct wiphy*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_put_bss (struct wiphy*,struct cfg80211_bss*) ; 
 int lbs_associate (struct lbs_private*,struct cfg80211_bss*,struct cfg80211_connect_params*) ; 
 int /*<<< orphan*/  lbs_deb_assoc (char*,...) ; 
 int /*<<< orphan*/  lbs_enable_rsn (struct lbs_private*,int) ; 
 int /*<<< orphan*/  lbs_remove_wep_keys (struct lbs_private*) ; 
 int lbs_set_authtype (struct lbs_private*,struct cfg80211_connect_params*) ; 
 int /*<<< orphan*/  lbs_set_key_material (struct lbs_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_set_mac_control (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_set_radio (struct lbs_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lbs_set_wep_keys (struct lbs_private*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wiphy_err (struct wiphy*,char*,int) ; 
 struct lbs_private* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int lbs_cfg_connect(struct wiphy *wiphy, struct net_device *dev,
			   struct cfg80211_connect_params *sme)
{
	struct lbs_private *priv = wiphy_priv(wiphy);
	struct cfg80211_bss *bss = NULL;
	int ret = 0;
	u8 preamble = RADIO_PREAMBLE_SHORT;

	if (dev == priv->mesh_dev)
		return -EOPNOTSUPP;

	if (!sme->bssid) {
		struct cfg80211_scan_request *creq;

		/*
		 * Scan for the requested network after waiting for existing
		 * scans to finish.
		 */
		lbs_deb_assoc("assoc: waiting for existing scans\n");
		wait_event_interruptible_timeout(priv->scan_q,
						 (priv->scan_req == NULL),
						 (15 * HZ));

		creq = _new_connect_scan_req(wiphy, sme);
		if (!creq) {
			ret = -EINVAL;
			goto done;
		}

		lbs_deb_assoc("assoc: scanning for compatible AP\n");
		_internal_start_scan(priv, true, creq);

		lbs_deb_assoc("assoc: waiting for scan to complete\n");
		wait_event_interruptible_timeout(priv->scan_q,
						 (priv->scan_req == NULL),
						 (15 * HZ));
		lbs_deb_assoc("assoc: scanning completed\n");
	}

	/* Find the BSS we want using available scan results */
	bss = cfg80211_get_bss(wiphy, sme->channel, sme->bssid,
		sme->ssid, sme->ssid_len, IEEE80211_BSS_TYPE_ESS,
		IEEE80211_PRIVACY_ANY);
	if (!bss) {
		wiphy_err(wiphy, "assoc: bss %pM not in scan results\n",
			  sme->bssid);
		ret = -ENOENT;
		goto done;
	}
	lbs_deb_assoc("trying %pM\n", bss->bssid);
	lbs_deb_assoc("cipher 0x%x, key index %d, key len %d\n",
		      sme->crypto.cipher_group,
		      sme->key_idx, sme->key_len);

	/* As this is a new connection, clear locally stored WEP keys */
	priv->wep_tx_key = 0;
	memset(priv->wep_key, 0, sizeof(priv->wep_key));
	memset(priv->wep_key_len, 0, sizeof(priv->wep_key_len));

	/* set/remove WEP keys */
	switch (sme->crypto.cipher_group) {
	case WLAN_CIPHER_SUITE_WEP40:
	case WLAN_CIPHER_SUITE_WEP104:
		/* Store provided WEP keys in priv-> */
		priv->wep_tx_key = sme->key_idx;
		priv->wep_key_len[sme->key_idx] = sme->key_len;
		memcpy(priv->wep_key[sme->key_idx], sme->key, sme->key_len);
		/* Set WEP keys and WEP mode */
		lbs_set_wep_keys(priv);
		priv->mac_control |= CMD_ACT_MAC_WEP_ENABLE;
		lbs_set_mac_control(priv);
		/* No RSN mode for WEP */
		lbs_enable_rsn(priv, 0);
		break;
	case 0: /* there's no WLAN_CIPHER_SUITE_NONE definition */
		/*
		 * If we don't have no WEP, no WPA and no WPA2,
		 * we remove all keys like in the WPA/WPA2 setup,
		 * we just don't set RSN.
		 *
		 * Therefore: fall-through
		 */
	case WLAN_CIPHER_SUITE_TKIP:
	case WLAN_CIPHER_SUITE_CCMP:
		/* Remove WEP keys and WEP mode */
		lbs_remove_wep_keys(priv);
		priv->mac_control &= ~CMD_ACT_MAC_WEP_ENABLE;
		lbs_set_mac_control(priv);

		/* clear the WPA/WPA2 keys */
		lbs_set_key_material(priv,
			KEY_TYPE_ID_WEP, /* doesn't matter */
			KEY_INFO_WPA_UNICAST,
			NULL, 0);
		lbs_set_key_material(priv,
			KEY_TYPE_ID_WEP, /* doesn't matter */
			KEY_INFO_WPA_MCAST,
			NULL, 0);
		/* RSN mode for WPA/WPA2 */
		lbs_enable_rsn(priv, sme->crypto.cipher_group != 0);
		break;
	default:
		wiphy_err(wiphy, "unsupported cipher group 0x%x\n",
			  sme->crypto.cipher_group);
		ret = -ENOTSUPP;
		goto done;
	}

	ret = lbs_set_authtype(priv, sme);
	if (ret == -ENOTSUPP) {
		wiphy_err(wiphy, "unsupported authtype 0x%x\n", sme->auth_type);
		goto done;
	}

	lbs_set_radio(priv, preamble, 1);

	/* Do the actual association */
	ret = lbs_associate(priv, bss, sme);

 done:
	if (bss)
		cfg80211_put_bss(wiphy, bss);
	return ret;
}