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
struct TYPE_2__ {int /*<<< orphan*/  mac_work; int /*<<< orphan*/  state; int /*<<< orphan*/  survey_time; } ;
struct mt7615_dev {TYPE_1__ mt76; } ;
struct ieee80211_hw {struct mt7615_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT7615_WATCHDOG_TIME ; 
 int /*<<< orphan*/  MT76_STATE_RUNNING ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_boottime () ; 
 int /*<<< orphan*/  mt76_hw (struct mt7615_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt7615_start(struct ieee80211_hw *hw)
{
	struct mt7615_dev *dev = hw->priv;

	dev->mt76.survey_time = ktime_get_boottime();
	set_bit(MT76_STATE_RUNNING, &dev->mt76.state);
	ieee80211_queue_delayed_work(mt76_hw(dev), &dev->mt76.mac_work,
				     MT7615_WATCHDOG_TIME);

	return 0;
}