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
typedef  int u32 ;
struct mt7603_vif {int /*<<< orphan*/  idx; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  pre_tbtt_tasklet; } ;
struct mt7603_dev {int slottime; TYPE_1__ mt76; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct mt7603_dev* priv; } ;
struct ieee80211_bss_conf {int beacon_int; int /*<<< orphan*/  enable_beacon; scalar_t__ use_short_slot; scalar_t__ bssid; scalar_t__ ibss_joined; scalar_t__ assoc; } ;

/* Variables and functions */
 int BSS_CHANGED_ASSOC ; 
 int BSS_CHANGED_BEACON_ENABLED ; 
 int BSS_CHANGED_BEACON_INT ; 
 int BSS_CHANGED_BSSID ; 
 int BSS_CHANGED_ERP_SLOT ; 
 int /*<<< orphan*/  MT_BSSID0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_BSSID1 (int /*<<< orphan*/ ) ; 
 int MT_BSSID1_VALID ; 
 int get_unaligned_le16 (scalar_t__) ; 
 int get_unaligned_le32 (scalar_t__) ; 
 int /*<<< orphan*/  mt7603_beacon_set_timer (struct mt7603_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt7603_mac_set_timing (struct mt7603_dev*) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7603_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mt7603_bss_info_changed(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
			struct ieee80211_bss_conf *info, u32 changed)
{
	struct mt7603_dev *dev = hw->priv;
	struct mt7603_vif *mvif = (struct mt7603_vif *)vif->drv_priv;

	mutex_lock(&dev->mt76.mutex);

	if (changed & (BSS_CHANGED_ASSOC | BSS_CHANGED_BSSID)) {
		if (info->assoc || info->ibss_joined) {
			mt76_wr(dev, MT_BSSID0(mvif->idx),
				get_unaligned_le32(info->bssid));
			mt76_wr(dev, MT_BSSID1(mvif->idx),
				(get_unaligned_le16(info->bssid + 4) |
				 MT_BSSID1_VALID));
		} else {
			mt76_wr(dev, MT_BSSID0(mvif->idx), 0);
			mt76_wr(dev, MT_BSSID1(mvif->idx), 0);
		}
	}

	if (changed & BSS_CHANGED_ERP_SLOT) {
		int slottime = info->use_short_slot ? 9 : 20;

		if (slottime != dev->slottime) {
			dev->slottime = slottime;
			mt7603_mac_set_timing(dev);
		}
	}

	if (changed & (BSS_CHANGED_BEACON_ENABLED | BSS_CHANGED_BEACON_INT)) {
		int beacon_int = !!info->enable_beacon * info->beacon_int;

		tasklet_disable(&dev->mt76.pre_tbtt_tasklet);
		mt7603_beacon_set_timer(dev, mvif->idx, beacon_int);
		tasklet_enable(&dev->mt76.pre_tbtt_tasklet);
	}

	mutex_unlock(&dev->mt76.mutex);
}