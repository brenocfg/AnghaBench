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
struct TYPE_4__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  rxfilter; } ;
struct mt7615_dev {TYPE_2__ mt76; } ;
struct TYPE_3__ {int flags; } ;
struct ieee80211_hw {TYPE_1__ conf; struct mt7615_dev* priv; } ;

/* Variables and functions */
 int IEEE80211_CONF_CHANGE_CHANNEL ; 
 int IEEE80211_CONF_CHANGE_MONITOR ; 
 int IEEE80211_CONF_CHANGE_POWER ; 
 int IEEE80211_CONF_MONITOR ; 
 int /*<<< orphan*/  MT_WF_RFCR ; 
 int /*<<< orphan*/  MT_WF_RFCR_DROP_OTHER_UC ; 
 int /*<<< orphan*/  ieee80211_stop_queues (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_wake_queues (struct ieee80211_hw*) ; 
 int mt7615_mcu_set_tx_power (struct mt7615_dev*) ; 
 int mt7615_set_channel (struct mt7615_dev*) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7615_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt7615_config(struct ieee80211_hw *hw, u32 changed)
{
	struct mt7615_dev *dev = hw->priv;
	int ret = 0;

	if (changed & IEEE80211_CONF_CHANGE_CHANNEL) {
		ieee80211_stop_queues(hw);
		ret = mt7615_set_channel(dev);
		ieee80211_wake_queues(hw);
	}

	mutex_lock(&dev->mt76.mutex);

	if (changed & IEEE80211_CONF_CHANGE_POWER)
		ret = mt7615_mcu_set_tx_power(dev);

	if (changed & IEEE80211_CONF_CHANGE_MONITOR) {
		if (!(hw->conf.flags & IEEE80211_CONF_MONITOR))
			dev->mt76.rxfilter |= MT_WF_RFCR_DROP_OTHER_UC;
		else
			dev->mt76.rxfilter &= ~MT_WF_RFCR_DROP_OTHER_UC;

		mt76_wr(dev, MT_WF_RFCR, dev->mt76.rxfilter);
	}

	mutex_unlock(&dev->mt76.mutex);

	return ret;
}