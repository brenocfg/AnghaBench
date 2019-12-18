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
struct TYPE_2__ {int /*<<< orphan*/  dfs_tasklet; } ;
struct mt76x02_dev {int /*<<< orphan*/  mt76; TYPE_1__ dfs_pd; int /*<<< orphan*/  cal_work; } ;
struct cfg80211_chan_def {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_CH_BUSY ; 
 int /*<<< orphan*/  MT_CH_IDLE ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ mt76_is_mmio (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76_rr (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_set_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76_txq_schedule_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76x02_dfs_init_params (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x02_edcca_init (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x02_pre_tbtt_enable (struct mt76x02_dev*,int) ; 
 int /*<<< orphan*/  mt76x0_phy_set_channel (struct mt76x02_dev*,struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mt76x0_set_channel(struct mt76x02_dev *dev, struct cfg80211_chan_def *chandef)
{
	cancel_delayed_work_sync(&dev->cal_work);
	mt76x02_pre_tbtt_enable(dev, false);
	if (mt76_is_mmio(dev))
		tasklet_disable(&dev->dfs_pd.dfs_tasklet);

	mt76_set_channel(&dev->mt76);
	mt76x0_phy_set_channel(dev, chandef);

	/* channel cycle counters read-and-clear */
	mt76_rr(dev, MT_CH_IDLE);
	mt76_rr(dev, MT_CH_BUSY);

	mt76x02_edcca_init(dev);

	if (mt76_is_mmio(dev)) {
		mt76x02_dfs_init_params(dev);
		tasklet_enable(&dev->dfs_pd.dfs_tasklet);
	}
	mt76x02_pre_tbtt_enable(dev, true);

	mt76_txq_schedule_all(&dev->mt76);
}