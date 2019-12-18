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
struct mt76x02_dfs_pattern_detector {scalar_t__ last_event_ts; } ;
struct mt76x02_dfs_event {scalar_t__ ts; } ;
struct mt76x02_dev {struct mt76x02_dfs_pattern_detector dfs_pd; } ;

/* Variables and functions */
 int MT_DFS_EVENT_LOOP ; 
 int mt76x02_dfs_add_event_to_sequence (struct mt76x02_dev*,struct mt76x02_dfs_event*) ; 
 int /*<<< orphan*/  mt76x02_dfs_check_event (struct mt76x02_dev*,struct mt76x02_dfs_event*) ; 
 int /*<<< orphan*/  mt76x02_dfs_create_sequence (struct mt76x02_dev*,struct mt76x02_dfs_event*,int) ; 
 int /*<<< orphan*/  mt76x02_dfs_detector_reset (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x02_dfs_fetch_event (struct mt76x02_dev*,struct mt76x02_dfs_event*) ; 
 int /*<<< orphan*/  mt76x02_dfs_queue_event (struct mt76x02_dev*,struct mt76x02_dfs_event*) ; 
 int /*<<< orphan*/  mt76x02_dfs_set_capture_mode_ctrl (struct mt76x02_dev*,int) ; 

__attribute__((used)) static void mt76x02_dfs_add_events(struct mt76x02_dev *dev)
{
	struct mt76x02_dfs_pattern_detector *dfs_pd = &dev->dfs_pd;
	struct mt76x02_dfs_event event;
	int i, seq_len;

	/* disable debug mode */
	mt76x02_dfs_set_capture_mode_ctrl(dev, false);
	for (i = 0; i < MT_DFS_EVENT_LOOP; i++) {
		if (!mt76x02_dfs_fetch_event(dev, &event))
			break;

		if (dfs_pd->last_event_ts > event.ts)
			mt76x02_dfs_detector_reset(dev);
		dfs_pd->last_event_ts = event.ts;

		if (!mt76x02_dfs_check_event(dev, &event))
			continue;

		seq_len = mt76x02_dfs_add_event_to_sequence(dev, &event);
		mt76x02_dfs_create_sequence(dev, &event, seq_len);

		mt76x02_dfs_queue_event(dev, &event);
	}
	mt76x02_dfs_set_capture_mode_ctrl(dev, true);
}