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
struct TYPE_2__ {int /*<<< orphan*/  work; scalar_t__ enabled; } ;
struct mt7601u_dev {TYPE_1__ freq_cal; int /*<<< orphan*/  hw; int /*<<< orphan*/  cal_work; int /*<<< orphan*/  state; int /*<<< orphan*/  hw_atomic_mutex; } ;
struct cfg80211_chan_def {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT7601U_STATE_SCANNING ; 
 int /*<<< orphan*/  MT_CALIBRATE_INTERVAL ; 
 int /*<<< orphan*/  MT_FREQ_CAL_INIT_DELAY ; 
 int __mt7601u_phy_set_channel (struct mt7601u_dev*,struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mt7601u_phy_set_channel(struct mt7601u_dev *dev,
			    struct cfg80211_chan_def *chandef)
{
	int ret;

	cancel_delayed_work_sync(&dev->cal_work);
	cancel_delayed_work_sync(&dev->freq_cal.work);

	mutex_lock(&dev->hw_atomic_mutex);
	ret = __mt7601u_phy_set_channel(dev, chandef);
	mutex_unlock(&dev->hw_atomic_mutex);
	if (ret)
		return ret;

	if (test_bit(MT7601U_STATE_SCANNING, &dev->state))
		return 0;

	ieee80211_queue_delayed_work(dev->hw, &dev->cal_work,
				     MT_CALIBRATE_INTERVAL);
	if (dev->freq_cal.enabled)
		ieee80211_queue_delayed_work(dev->hw, &dev->freq_cal.work,
					     MT_FREQ_CAL_INIT_DELAY);
	return 0;
}