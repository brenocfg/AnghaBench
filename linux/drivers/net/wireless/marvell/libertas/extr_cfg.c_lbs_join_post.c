#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct lbs_private {int /*<<< orphan*/  dev; int /*<<< orphan*/  tx_pending_len; int /*<<< orphan*/  connect_status; TYPE_1__* wdev; } ;
struct TYPE_6__ {TYPE_3__* chan; } ;
struct cfg80211_ibss_params {TYPE_2__ chandef; int /*<<< orphan*/  beacon_interval; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;
struct cfg80211_bss {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  hw_value; } ;
struct TYPE_5__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG80211_BSS_FTYPE_UNKNOWN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IEEE80211_MAX_SSID_LEN ; 
 int /*<<< orphan*/  LBS_CONNECTED ; 
 int /*<<< orphan*/  LBS_DEB_CFG80211 ; 
 int /*<<< orphan*/  WLAN_EID_DS_PARAMS ; 
 int /*<<< orphan*/  WLAN_EID_EXT_SUPP_RATES ; 
 int /*<<< orphan*/  WLAN_EID_IBSS_PARAMS ; 
 int /*<<< orphan*/  WLAN_EID_SSID ; 
 int /*<<< orphan*/  WLAN_EID_SUPP_RATES ; 
 int /*<<< orphan*/  cfg80211_ibss_joined (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 struct cfg80211_bss* cfg80211_inform_bss (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_put_bss (int /*<<< orphan*/ ,struct cfg80211_bss*) ; 
 int /*<<< orphan*/  lbs_deb_hex (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lbs_join_post(struct lbs_private *priv,
			  struct cfg80211_ibss_params *params,
			  u8 *bssid, u16 capability)
{
	u8 fake_ie[2 + IEEE80211_MAX_SSID_LEN + /* ssid */
		   2 + 4 +                      /* basic rates */
		   2 + 1 +                      /* DS parameter */
		   2 + 2 +                      /* atim */
		   2 + 8];                      /* extended rates */
	u8 *fake = fake_ie;
	struct cfg80211_bss *bss;

	/*
	 * For cfg80211_inform_bss, we'll need a fake IE, as we can't get
	 * the real IE from the firmware. So we fabricate a fake IE based on
	 * what the firmware actually sends (sniffed with wireshark).
	 */
	/* Fake SSID IE */
	*fake++ = WLAN_EID_SSID;
	*fake++ = params->ssid_len;
	memcpy(fake, params->ssid, params->ssid_len);
	fake += params->ssid_len;
	/* Fake supported basic rates IE */
	*fake++ = WLAN_EID_SUPP_RATES;
	*fake++ = 4;
	*fake++ = 0x82;
	*fake++ = 0x84;
	*fake++ = 0x8b;
	*fake++ = 0x96;
	/* Fake DS channel IE */
	*fake++ = WLAN_EID_DS_PARAMS;
	*fake++ = 1;
	*fake++ = params->chandef.chan->hw_value;
	/* Fake IBSS params IE */
	*fake++ = WLAN_EID_IBSS_PARAMS;
	*fake++ = 2;
	*fake++ = 0; /* ATIM=0 */
	*fake++ = 0;
	/* Fake extended rates IE, TODO: don't add this for 802.11b only,
	 * but I don't know how this could be checked */
	*fake++ = WLAN_EID_EXT_SUPP_RATES;
	*fake++ = 8;
	*fake++ = 0x0c;
	*fake++ = 0x12;
	*fake++ = 0x18;
	*fake++ = 0x24;
	*fake++ = 0x30;
	*fake++ = 0x48;
	*fake++ = 0x60;
	*fake++ = 0x6c;
	lbs_deb_hex(LBS_DEB_CFG80211, "IE", fake_ie, fake - fake_ie);

	bss = cfg80211_inform_bss(priv->wdev->wiphy,
				  params->chandef.chan,
				  CFG80211_BSS_FTYPE_UNKNOWN,
				  bssid,
				  0,
				  capability,
				  params->beacon_interval,
				  fake_ie, fake - fake_ie,
				  0, GFP_KERNEL);
	cfg80211_put_bss(priv->wdev->wiphy, bss);

	cfg80211_ibss_joined(priv->dev, bssid, params->chandef.chan,
			     GFP_KERNEL);

	/* TODO: consider doing this at MACREG_INT_CODE_LINK_SENSED time */
	priv->connect_status = LBS_CONNECTED;
	netif_carrier_on(priv->dev);
	if (!priv->tx_pending_len)
		netif_wake_queue(priv->dev);
}