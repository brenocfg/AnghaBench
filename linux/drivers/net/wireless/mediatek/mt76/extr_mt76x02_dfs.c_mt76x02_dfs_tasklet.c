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
struct mt76x02_dfs_pattern_detector {TYPE_1__* stats; scalar_t__ last_sw_check; } ;
struct mt76x02_dfs_hw_pulse {int engine; } ;
struct TYPE_4__ {int /*<<< orphan*/  hw; int /*<<< orphan*/  state; } ;
struct mt76x02_dev {TYPE_2__ mt76; struct mt76x02_dfs_pattern_detector dfs_pd; } ;
struct TYPE_3__ {int /*<<< orphan*/  hw_pattern; int /*<<< orphan*/  hw_pulse_discarded; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFS ; 
 int /*<<< orphan*/  MT76_SCANNING ; 
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int) ; 
 int MT_DFS_NUM_ENGINES ; 
 scalar_t__ MT_DFS_SW_TIMEOUT ; 
 int /*<<< orphan*/  MT_INT_GPTIMER ; 
 int /*<<< orphan*/  ieee80211_radar_detected (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int mt76_rr (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x02_dfs_add_events (struct mt76x02_dev*) ; 
 int mt76x02_dfs_check_detection (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x02_dfs_check_event_window (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x02_dfs_check_hw_pulse (struct mt76x02_dev*,struct mt76x02_dfs_hw_pulse*) ; 
 int /*<<< orphan*/  mt76x02_dfs_detector_reset (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x02_dfs_get_hw_pulse (struct mt76x02_dev*,struct mt76x02_dfs_hw_pulse*) ; 
 int /*<<< orphan*/  mt76x02_irq_enable (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_is_before_jiffies (scalar_t__) ; 

__attribute__((used)) static void mt76x02_dfs_tasklet(unsigned long arg)
{
	struct mt76x02_dev *dev = (struct mt76x02_dev *)arg;
	struct mt76x02_dfs_pattern_detector *dfs_pd = &dev->dfs_pd;
	u32 engine_mask;
	int i;

	if (test_bit(MT76_SCANNING, &dev->mt76.state))
		goto out;

	if (time_is_before_jiffies(dfs_pd->last_sw_check +
				   MT_DFS_SW_TIMEOUT)) {
		bool radar_detected;

		dfs_pd->last_sw_check = jiffies;

		mt76x02_dfs_add_events(dev);
		radar_detected = mt76x02_dfs_check_detection(dev);
		if (radar_detected) {
			/* sw detector rx radar pattern */
			ieee80211_radar_detected(dev->mt76.hw);
			mt76x02_dfs_detector_reset(dev);

			return;
		}
		mt76x02_dfs_check_event_window(dev);
	}

	engine_mask = mt76_rr(dev, MT_BBP(DFS, 1));
	if (!(engine_mask & 0xf))
		goto out;

	for (i = 0; i < MT_DFS_NUM_ENGINES; i++) {
		struct mt76x02_dfs_hw_pulse pulse;

		if (!(engine_mask & (1 << i)))
			continue;

		pulse.engine = i;
		mt76x02_dfs_get_hw_pulse(dev, &pulse);

		if (!mt76x02_dfs_check_hw_pulse(dev, &pulse)) {
			dfs_pd->stats[i].hw_pulse_discarded++;
			continue;
		}

		/* hw detector rx radar pattern */
		dfs_pd->stats[i].hw_pattern++;
		ieee80211_radar_detected(dev->mt76.hw);
		mt76x02_dfs_detector_reset(dev);

		return;
	}

	/* reset hw detector */
	mt76_wr(dev, MT_BBP(DFS, 1), 0xf);

out:
	mt76x02_irq_enable(dev, MT_INT_GPTIMER);
}