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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
struct mt7603_dev {TYPE_2__ mt76; int /*<<< orphan*/  rxfilter; } ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  chandef; } ;
struct ieee80211_hw {TYPE_1__ conf; struct mt7603_dev* priv; } ;

/* Variables and functions */
 int IEEE80211_CONF_CHANGE_CHANNEL ; 
 int IEEE80211_CONF_CHANGE_MONITOR ; 
 int IEEE80211_CONF_CHANGE_POWER ; 
 int IEEE80211_CONF_MONITOR ; 
 int /*<<< orphan*/  MT_WF_RFCR ; 
 int /*<<< orphan*/  MT_WF_RFCR_DROP_OTHER_UC ; 
 int /*<<< orphan*/  ieee80211_stop_queues (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_wake_queues (struct ieee80211_hw*) ; 
 int mt7603_set_channel (struct mt7603_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7603_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mt7603_config(struct ieee80211_hw *hw, u32 changed)
{
	struct mt7603_dev *dev = hw->priv;
	int ret = 0;

	if (changed & (IEEE80211_CONF_CHANGE_CHANNEL |
		       IEEE80211_CONF_CHANGE_POWER)) {
		ieee80211_stop_queues(hw);
		ret = mt7603_set_channel(dev, &hw->conf.chandef);
		ieee80211_wake_queues(hw);
	}

	if (changed & IEEE80211_CONF_CHANGE_MONITOR) {
		mutex_lock(&dev->mt76.mutex);

		if (!(hw->conf.flags & IEEE80211_CONF_MONITOR))
			dev->rxfilter |= MT_WF_RFCR_DROP_OTHER_UC;
		else
			dev->rxfilter &= ~MT_WF_RFCR_DROP_OTHER_UC;

		mt76_wr(dev, MT_WF_RFCR, dev->rxfilter);

		mutex_unlock(&dev->mt76.mutex);
	}

	return ret;
}