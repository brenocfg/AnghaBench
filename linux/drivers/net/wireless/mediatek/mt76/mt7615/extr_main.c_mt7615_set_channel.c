#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mac_work; int /*<<< orphan*/  mutex; int /*<<< orphan*/  state; int /*<<< orphan*/  survey_time; } ;
struct mt7615_dev {TYPE_1__ mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT7615_WATCHDOG_TIME ; 
 int /*<<< orphan*/  MT76_RESET ; 
 int /*<<< orphan*/  MT_MIB_SDR16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_boottime () ; 
 int /*<<< orphan*/  mt7615_dfs_check_channel (struct mt7615_dev*) ; 
 int mt7615_dfs_init_radar_detector (struct mt7615_dev*) ; 
 int /*<<< orphan*/  mt7615_mac_cca_stats_reset (struct mt7615_dev*) ; 
 int mt7615_mcu_set_channel (struct mt7615_dev*) ; 
 int /*<<< orphan*/  mt76_hw (struct mt7615_dev*) ; 
 int /*<<< orphan*/  mt76_rr (struct mt7615_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_set_channel (TYPE_1__*) ; 
 int /*<<< orphan*/  mt76_txq_schedule_all (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt7615_set_channel(struct mt7615_dev *dev)
{
	int ret;

	cancel_delayed_work_sync(&dev->mt76.mac_work);

	mutex_lock(&dev->mt76.mutex);
	set_bit(MT76_RESET, &dev->mt76.state);

	mt7615_dfs_check_channel(dev);

	mt76_set_channel(&dev->mt76);

	ret = mt7615_mcu_set_channel(dev);
	if (ret)
		goto out;

	ret = mt7615_dfs_init_radar_detector(dev);
	mt7615_mac_cca_stats_reset(dev);
	dev->mt76.survey_time = ktime_get_boottime();
	/* TODO: add DBDC support */
	mt76_rr(dev, MT_MIB_SDR16(0));

out:
	clear_bit(MT76_RESET, &dev->mt76.state);
	mutex_unlock(&dev->mt76.mutex);

	mt76_txq_schedule_all(&dev->mt76);
	ieee80211_queue_delayed_work(mt76_hw(dev), &dev->mt76.mac_work,
				     MT7615_WATCHDOG_TIME);
	return ret;
}