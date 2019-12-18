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
struct cfg80211_chan_def {TYPE_1__* chan; } ;
struct TYPE_4__ {scalar_t__ region; struct cfg80211_chan_def chandef; } ;
struct mt76x02_dev {TYPE_2__ mt76; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFS ; 
 int /*<<< orphan*/  IBI ; 
 int IEEE80211_CHAN_RADAR ; 
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_INT_GPTIMER ; 
 int /*<<< orphan*/  MT_INT_TIMER_EN ; 
 int /*<<< orphan*/  MT_INT_TIMER_EN_GP_TIMER_EN ; 
 scalar_t__ NL80211_DFS_UNSET ; 
 int mt76_chip (TYPE_2__*) ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x02_dfs_init_sw_detector (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x02_dfs_set_bbp_params (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x02_dfs_set_capture_mode_ctrl (struct mt76x02_dev*,int) ; 
 int /*<<< orphan*/  mt76x02_irq_disable (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x02_irq_enable (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 

void mt76x02_dfs_init_params(struct mt76x02_dev *dev)
{
	struct cfg80211_chan_def *chandef = &dev->mt76.chandef;

	if ((chandef->chan->flags & IEEE80211_CHAN_RADAR) &&
	    dev->mt76.region != NL80211_DFS_UNSET) {
		mt76x02_dfs_init_sw_detector(dev);
		mt76x02_dfs_set_bbp_params(dev);
		/* enable debug mode */
		mt76x02_dfs_set_capture_mode_ctrl(dev, true);

		mt76x02_irq_enable(dev, MT_INT_GPTIMER);
		mt76_rmw_field(dev, MT_INT_TIMER_EN,
			       MT_INT_TIMER_EN_GP_TIMER_EN, 1);
	} else {
		/* disable hw detector */
		mt76_wr(dev, MT_BBP(DFS, 0), 0);
		/* clear detector status */
		mt76_wr(dev, MT_BBP(DFS, 1), 0xf);
		if (mt76_chip(&dev->mt76) == 0x7610 ||
		    mt76_chip(&dev->mt76) == 0x7630)
			mt76_wr(dev, MT_BBP(IBI, 11), 0xfde8081);
		else
			mt76_wr(dev, MT_BBP(IBI, 11), 0);

		mt76x02_irq_disable(dev, MT_INT_GPTIMER);
		mt76_rmw_field(dev, MT_INT_TIMER_EN,
			       MT_INT_TIMER_EN_GP_TIMER_EN, 0);
	}
}