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
struct zd_mc_hash {int dummy; } ;
struct TYPE_2__ {int interval; int period; int /*<<< orphan*/  last_update; } ;
struct zd_mac {unsigned int short_preamble; int /*<<< orphan*/  lock; TYPE_1__ beacon; int /*<<< orphan*/  type; int /*<<< orphan*/  chip; int /*<<< orphan*/  hw; int /*<<< orphan*/ * vif; int /*<<< orphan*/  channel; struct zd_mc_hash multicast_hash; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*,...) ; 
 struct sk_buff* ieee80211_beacon_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int set_mac_and_bssid (struct zd_mac*) ; 
 int /*<<< orphan*/  set_rts_cts (struct zd_mac*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int zd_chip_set_channel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zd_chip_set_multicast_hash (int /*<<< orphan*/ *,struct zd_mc_hash*) ; 
 int /*<<< orphan*/  zd_mac_config_beacon (int /*<<< orphan*/ ,struct sk_buff*,int) ; 
 int /*<<< orphan*/  zd_mac_dev (struct zd_mac*) ; 
 int /*<<< orphan*/  zd_set_beacon_interval (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

int zd_restore_settings(struct zd_mac *mac)
{
	struct sk_buff *beacon;
	struct zd_mc_hash multicast_hash;
	unsigned int short_preamble;
	int r, beacon_interval, beacon_period;
	u8 channel;

	dev_dbg_f(zd_mac_dev(mac), "\n");

	spin_lock_irq(&mac->lock);
	multicast_hash = mac->multicast_hash;
	short_preamble = mac->short_preamble;
	beacon_interval = mac->beacon.interval;
	beacon_period = mac->beacon.period;
	channel = mac->channel;
	spin_unlock_irq(&mac->lock);

	r = set_mac_and_bssid(mac);
	if (r < 0) {
		dev_dbg_f(zd_mac_dev(mac), "set_mac_and_bssid failed, %d\n", r);
		return r;
	}

	r = zd_chip_set_channel(&mac->chip, channel);
	if (r < 0) {
		dev_dbg_f(zd_mac_dev(mac), "zd_chip_set_channel failed, %d\n",
			  r);
		return r;
	}

	set_rts_cts(mac, short_preamble);

	r = zd_chip_set_multicast_hash(&mac->chip, &multicast_hash);
	if (r < 0) {
		dev_dbg_f(zd_mac_dev(mac),
			  "zd_chip_set_multicast_hash failed, %d\n", r);
		return r;
	}

	if (mac->type == NL80211_IFTYPE_MESH_POINT ||
	    mac->type == NL80211_IFTYPE_ADHOC ||
	    mac->type == NL80211_IFTYPE_AP) {
		if (mac->vif != NULL) {
			beacon = ieee80211_beacon_get(mac->hw, mac->vif);
			if (beacon)
				zd_mac_config_beacon(mac->hw, beacon, false);
		}

		zd_set_beacon_interval(&mac->chip, beacon_interval,
					beacon_period, mac->type);

		spin_lock_irq(&mac->lock);
		mac->beacon.last_update = jiffies;
		spin_unlock_irq(&mac->lock);
	}

	return 0;
}