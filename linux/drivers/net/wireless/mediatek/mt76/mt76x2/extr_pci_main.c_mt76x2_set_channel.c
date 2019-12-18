#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pre_tbtt_tasklet; int /*<<< orphan*/  mutex; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int /*<<< orphan*/  dfs_tasklet; } ;
struct mt76x02_dev {TYPE_2__ mt76; TYPE_1__ dfs_pd; int /*<<< orphan*/  cal_work; } ;
struct cfg80211_chan_def {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT76_RESET ; 
 int /*<<< orphan*/  MT_CH_BUSY ; 
 int /*<<< orphan*/  MT_CH_IDLE ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76_rr (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_set_channel (TYPE_2__*) ; 
 int /*<<< orphan*/  mt76_txq_schedule_all (TYPE_2__*) ; 
 int /*<<< orphan*/  mt76x02_dfs_init_params (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x2_mac_resume (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x2_mac_stop (struct mt76x02_dev*,int) ; 
 int mt76x2_phy_set_channel (struct mt76x02_dev*,struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mt76x2_set_channel(struct mt76x02_dev *dev, struct cfg80211_chan_def *chandef)
{
	int ret;

	cancel_delayed_work_sync(&dev->cal_work);
	tasklet_disable(&dev->mt76.pre_tbtt_tasklet);
	tasklet_disable(&dev->dfs_pd.dfs_tasklet);

	mutex_lock(&dev->mt76.mutex);
	set_bit(MT76_RESET, &dev->mt76.state);

	mt76_set_channel(&dev->mt76);

	mt76x2_mac_stop(dev, true);
	ret = mt76x2_phy_set_channel(dev, chandef);

	/* channel cycle counters read-and-clear */
	mt76_rr(dev, MT_CH_IDLE);
	mt76_rr(dev, MT_CH_BUSY);

	mt76x02_dfs_init_params(dev);

	mt76x2_mac_resume(dev);

	clear_bit(MT76_RESET, &dev->mt76.state);
	mutex_unlock(&dev->mt76.mutex);

	tasklet_enable(&dev->dfs_pd.dfs_tasklet);
	tasklet_enable(&dev->mt76.pre_tbtt_tasklet);

	mt76_txq_schedule_all(&dev->mt76);

	return ret;
}