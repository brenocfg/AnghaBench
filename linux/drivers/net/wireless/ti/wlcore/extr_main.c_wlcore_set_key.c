#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {size_t hlid; } ;
struct TYPE_4__ {size_t bcast_hlid; } ;
struct wl12xx_vif {scalar_t__ bss_type; size_t encryption_type; TYPE_2__ sta; TYPE_1__ ap; } ;
struct wl1271_station {size_t hlid; } ;
struct wl1271 {TYPE_3__* links; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_key_conf {int cipher; int /*<<< orphan*/  key; int /*<<< orphan*/  keylen; int /*<<< orphan*/  keyidx; int /*<<< orphan*/  flags; int /*<<< orphan*/  hw_key_idx; } ;
typedef  enum set_key_cmd { ____Placeholder_set_key_cmd } set_key_cmd ;
struct TYPE_6__ {int /*<<< orphan*/  total_freed_pkts; } ;

/* Variables and functions */
 scalar_t__ BSS_TYPE_AP_BSS ; 
 scalar_t__ BSS_TYPE_STA_BSS ; 
 int /*<<< orphan*/  DEBUG_CRYPT ; 
 int /*<<< orphan*/  DEBUG_MAC80211 ; 
#define  DISABLE_KEY 134 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IEEE80211_KEY_FLAG_PUT_IV_SPACE ; 
 int /*<<< orphan*/  KEY_ADD_OR_REPLACE ; 
 size_t KEY_AES ; 
 size_t KEY_GEM ; 
 int /*<<< orphan*/  KEY_REMOVE ; 
 size_t KEY_TKIP ; 
 size_t KEY_WEP ; 
#define  SET_KEY 133 
#define  WL1271_CIPHER_SUITE_GEM 132 
 int /*<<< orphan*/  WL1271_TX_SECURITY_HI32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WL1271_TX_SECURITY_LO16 (int /*<<< orphan*/ ) ; 
 size_t WL12XX_INVALID_LINK_ID ; 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int wl1271_cmd_build_arp_rsp (struct wl1271*,struct wl12xx_vif*) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wl1271_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_error (char*,...) ; 
 int wl1271_set_key (struct wl1271*,struct wl12xx_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 
 struct wl12xx_vif* wl12xx_vif_to_data (struct ieee80211_vif*) ; 

int wlcore_set_key(struct wl1271 *wl, enum set_key_cmd cmd,
		   struct ieee80211_vif *vif,
		   struct ieee80211_sta *sta,
		   struct ieee80211_key_conf *key_conf)
{
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);
	int ret;
	u32 tx_seq_32 = 0;
	u16 tx_seq_16 = 0;
	u8 key_type;
	u8 hlid;

	wl1271_debug(DEBUG_MAC80211, "mac80211 set key");

	wl1271_debug(DEBUG_CRYPT, "CMD: 0x%x sta: %p", cmd, sta);
	wl1271_debug(DEBUG_CRYPT, "Key: algo:0x%x, id:%d, len:%d flags 0x%x",
		     key_conf->cipher, key_conf->keyidx,
		     key_conf->keylen, key_conf->flags);
	wl1271_dump(DEBUG_CRYPT, "KEY: ", key_conf->key, key_conf->keylen);

	if (wlvif->bss_type == BSS_TYPE_AP_BSS)
		if (sta) {
			struct wl1271_station *wl_sta = (void *)sta->drv_priv;
			hlid = wl_sta->hlid;
		} else {
			hlid = wlvif->ap.bcast_hlid;
		}
	else
		hlid = wlvif->sta.hlid;

	if (hlid != WL12XX_INVALID_LINK_ID) {
		u64 tx_seq = wl->links[hlid].total_freed_pkts;
		tx_seq_32 = WL1271_TX_SECURITY_HI32(tx_seq);
		tx_seq_16 = WL1271_TX_SECURITY_LO16(tx_seq);
	}

	switch (key_conf->cipher) {
	case WLAN_CIPHER_SUITE_WEP40:
	case WLAN_CIPHER_SUITE_WEP104:
		key_type = KEY_WEP;

		key_conf->hw_key_idx = key_conf->keyidx;
		break;
	case WLAN_CIPHER_SUITE_TKIP:
		key_type = KEY_TKIP;
		key_conf->hw_key_idx = key_conf->keyidx;
		break;
	case WLAN_CIPHER_SUITE_CCMP:
		key_type = KEY_AES;
		key_conf->flags |= IEEE80211_KEY_FLAG_PUT_IV_SPACE;
		break;
	case WL1271_CIPHER_SUITE_GEM:
		key_type = KEY_GEM;
		break;
	default:
		wl1271_error("Unknown key algo 0x%x", key_conf->cipher);

		return -EOPNOTSUPP;
	}

	switch (cmd) {
	case SET_KEY:
		ret = wl1271_set_key(wl, wlvif, KEY_ADD_OR_REPLACE,
				 key_conf->keyidx, key_type,
				 key_conf->keylen, key_conf->key,
				 tx_seq_32, tx_seq_16, sta);
		if (ret < 0) {
			wl1271_error("Could not add or replace key");
			return ret;
		}

		/*
		 * reconfiguring arp response if the unicast (or common)
		 * encryption key type was changed
		 */
		if (wlvif->bss_type == BSS_TYPE_STA_BSS &&
		    (sta || key_type == KEY_WEP) &&
		    wlvif->encryption_type != key_type) {
			wlvif->encryption_type = key_type;
			ret = wl1271_cmd_build_arp_rsp(wl, wlvif);
			if (ret < 0) {
				wl1271_warning("build arp rsp failed: %d", ret);
				return ret;
			}
		}
		break;

	case DISABLE_KEY:
		ret = wl1271_set_key(wl, wlvif, KEY_REMOVE,
				     key_conf->keyidx, key_type,
				     key_conf->keylen, key_conf->key,
				     0, 0, sta);
		if (ret < 0) {
			wl1271_error("Could not remove key");
			return ret;
		}
		break;

	default:
		wl1271_error("Unsupported key cmd 0x%x", cmd);
		return -EOPNOTSUPP;
	}

	return ret;
}