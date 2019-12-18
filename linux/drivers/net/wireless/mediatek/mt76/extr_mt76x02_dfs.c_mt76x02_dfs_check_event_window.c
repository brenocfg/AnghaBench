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
struct mt76x02_dfs_pattern_detector {struct mt76x02_dfs_event_rb* event_rb; } ;
struct mt76x02_dfs_event_rb {size_t h_rb; size_t t_rb; struct mt76x02_dfs_event* data; } ;
struct mt76x02_dfs_event {scalar_t__ fetch_ts; } ;
struct mt76x02_dev {struct mt76x02_dfs_pattern_detector dfs_pd; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct mt76x02_dfs_event_rb*) ; 
 int /*<<< orphan*/  MT_DFS_EVENT_BUFLEN ; 
 scalar_t__ MT_DFS_EVENT_WINDOW ; 
 size_t mt76_incr (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ time_is_after_jiffies (scalar_t__) ; 

__attribute__((used)) static void mt76x02_dfs_check_event_window(struct mt76x02_dev *dev)
{
	struct mt76x02_dfs_pattern_detector *dfs_pd = &dev->dfs_pd;
	struct mt76x02_dfs_event_rb *event_buff;
	struct mt76x02_dfs_event *event;
	int i;

	for (i = 0; i < ARRAY_SIZE(dfs_pd->event_rb); i++) {
		event_buff = &dfs_pd->event_rb[i];

		while (event_buff->h_rb != event_buff->t_rb) {
			event = &event_buff->data[event_buff->h_rb];

			/* sorted list */
			if (time_is_after_jiffies(event->fetch_ts +
						  MT_DFS_EVENT_WINDOW))
				break;
			event_buff->h_rb = mt76_incr(event_buff->h_rb,
						     MT_DFS_EVENT_BUFLEN);
		}
	}
}