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
struct TYPE_3__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  state; } ;
struct mt76x02_dev {TYPE_1__ mt76; int /*<<< orphan*/  cal_work; } ;
struct cfg80211_chan_def {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT76_RESET ; 
 int /*<<< orphan*/  MT_CH_BUSY ; 
 int /*<<< orphan*/  MT_CH_IDLE ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76_rr (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_set_channel (TYPE_1__*) ; 
 int /*<<< orphan*/  mt76_txq_schedule_all (TYPE_1__*) ; 
 int /*<<< orphan*/  mt76x02_pre_tbtt_enable (struct mt76x02_dev*,int) ; 
 int /*<<< orphan*/  mt76x2_mac_resume (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x2_mac_stop (struct mt76x02_dev*,int) ; 
 int mt76x2u_phy_set_channel (struct mt76x02_dev*,struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mt76x2u_set_channel(struct mt76x02_dev *dev,
		    struct cfg80211_chan_def *chandef)
{
	int err;

	cancel_delayed_work_sync(&dev->cal_work);
	mt76x02_pre_tbtt_enable(dev, false);

	mutex_lock(&dev->mt76.mutex);
	set_bit(MT76_RESET, &dev->mt76.state);

	mt76_set_channel(&dev->mt76);

	mt76x2_mac_stop(dev, false);

	err = mt76x2u_phy_set_channel(dev, chandef);

	/* channel cycle counters read-and-clear */
	mt76_rr(dev, MT_CH_IDLE);
	mt76_rr(dev, MT_CH_BUSY);

	mt76x2_mac_resume(dev);

	clear_bit(MT76_RESET, &dev->mt76.state);
	mutex_unlock(&dev->mt76.mutex);

	mt76x02_pre_tbtt_enable(dev, true);
	mt76_txq_schedule_all(&dev->mt76);

	return err;
}