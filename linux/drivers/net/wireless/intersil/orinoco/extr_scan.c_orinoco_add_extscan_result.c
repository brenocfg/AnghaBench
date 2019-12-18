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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct wiphy {int dummy; } ;
struct orinoco_private {int dummy; } ;
struct ieee80211_channel {int dummy; } ;
struct cfg80211_bss {int dummy; } ;
struct agere_ext_scan_info {int* data; int /*<<< orphan*/  bssid; int /*<<< orphan*/  level; int /*<<< orphan*/  beacon_interval; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  timestamp; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CFG80211_BSS_FTYPE_UNKNOWN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  SIGNAL_TO_MBM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WLAN_EID_DS_PARAMS ; 
 int* cfg80211_find_ie (int /*<<< orphan*/ ,int*,size_t) ; 
 struct cfg80211_bss* cfg80211_inform_bss (struct wiphy*,struct ieee80211_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_put_bss (struct wiphy*,struct cfg80211_bss*) ; 
 int ieee80211_channel_to_frequency (int,int /*<<< orphan*/ ) ; 
 struct ieee80211_channel* ieee80211_get_channel (struct wiphy*,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct wiphy* priv_to_wiphy (struct orinoco_private*) ; 

void orinoco_add_extscan_result(struct orinoco_private *priv,
				struct agere_ext_scan_info *bss,
				size_t len)
{
	struct wiphy *wiphy = priv_to_wiphy(priv);
	struct ieee80211_channel *channel;
	struct cfg80211_bss *cbss;
	const u8 *ie;
	u64 timestamp;
	s32 signal;
	u16 capability;
	u16 beacon_interval;
	size_t ie_len;
	int chan, freq;

	ie_len = len - sizeof(*bss);
	ie = cfg80211_find_ie(WLAN_EID_DS_PARAMS, bss->data, ie_len);
	chan = ie ? ie[2] : 0;
	freq = ieee80211_channel_to_frequency(chan, NL80211_BAND_2GHZ);
	channel = ieee80211_get_channel(wiphy, freq);

	timestamp = le64_to_cpu(bss->timestamp);
	capability = le16_to_cpu(bss->capabilities);
	beacon_interval = le16_to_cpu(bss->beacon_interval);
	ie = bss->data;
	signal = SIGNAL_TO_MBM(bss->level);

	cbss = cfg80211_inform_bss(wiphy, channel, CFG80211_BSS_FTYPE_UNKNOWN,
				   bss->bssid, timestamp, capability,
				   beacon_interval, ie, ie_len, signal,
				   GFP_KERNEL);
	cfg80211_put_bss(wiphy, cbss);
}