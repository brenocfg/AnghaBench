#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct mt76x02_dfs_pattern_detector {int chirp_pulse_ts; int chirp_pulse_cnt; } ;
struct mt76x02_dev {struct mt76x02_dfs_pattern_detector dfs_pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_PBF_LIFE_TIMER ; 
 int mt76_rr (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mt76x02_dfs_check_chirp(struct mt76x02_dev *dev)
{
	bool ret = false;
	u32 current_ts, delta_ts;
	struct mt76x02_dfs_pattern_detector *dfs_pd = &dev->dfs_pd;

	current_ts = mt76_rr(dev, MT_PBF_LIFE_TIMER);
	delta_ts = current_ts - dfs_pd->chirp_pulse_ts;
	dfs_pd->chirp_pulse_ts = current_ts;

	/* 12 sec */
	if (delta_ts <= (12 * (1 << 20))) {
		if (++dfs_pd->chirp_pulse_cnt > 8)
			ret = true;
	} else {
		dfs_pd->chirp_pulse_cnt = 1;
	}

	return ret;
}