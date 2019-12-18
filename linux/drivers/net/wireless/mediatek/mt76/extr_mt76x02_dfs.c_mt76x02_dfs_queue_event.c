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
struct mt76x02_dfs_event_rb {size_t t_rb; size_t h_rb; struct mt76x02_dfs_event* data; } ;
struct mt76x02_dfs_event {int engine; int /*<<< orphan*/  fetch_ts; } ;
struct mt76x02_dev {struct mt76x02_dfs_pattern_detector dfs_pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_DFS_EVENT_BUFLEN ; 
 int /*<<< orphan*/  jiffies ; 
 void* mt76_incr (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mt76x02_dfs_queue_event(struct mt76x02_dev *dev,
				    struct mt76x02_dfs_event *event)
{
	struct mt76x02_dfs_pattern_detector *dfs_pd = &dev->dfs_pd;
	struct mt76x02_dfs_event_rb *event_buff;

	/* add radar event to ring buffer */
	event_buff = event->engine == 2 ? &dfs_pd->event_rb[1]
					: &dfs_pd->event_rb[0];
	event_buff->data[event_buff->t_rb] = *event;
	event_buff->data[event_buff->t_rb].fetch_ts = jiffies;

	event_buff->t_rb = mt76_incr(event_buff->t_rb, MT_DFS_EVENT_BUFLEN);
	if (event_buff->t_rb == event_buff->h_rb)
		event_buff->h_rb = mt76_incr(event_buff->h_rb,
					     MT_DFS_EVENT_BUFLEN);
}