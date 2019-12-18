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
typedef  int /*<<< orphan*/  u32 ;
struct mt76x02_dfs_event {int /*<<< orphan*/  width; int /*<<< orphan*/  ts; int /*<<< orphan*/  engine; } ;
struct mt76x02_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFS ; 
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_DFS_CHECK_EVENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_DFS_EVENT_ENGINE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_DFS_EVENT_TIMESTAMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_DFS_EVENT_WIDTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_rr (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mt76x02_dfs_fetch_event(struct mt76x02_dev *dev,
				    struct mt76x02_dfs_event *event)
{
	u32 data;

	/* 1st: DFS_R37[31]: 0 (engine 0) - 1 (engine 2)
	 * 2nd: DFS_R37[21:0]: pulse time
	 * 3rd: DFS_R37[11:0]: pulse width
	 * 3rd: DFS_R37[25:16]: phase
	 * 4th: DFS_R37[12:0]: current pwr
	 * 4th: DFS_R37[21:16]: pwr stable counter
	 *
	 * 1st: DFS_R37[31:0] set to 0xffffffff means no event detected
	 */
	data = mt76_rr(dev, MT_BBP(DFS, 37));
	if (!MT_DFS_CHECK_EVENT(data))
		return false;

	event->engine = MT_DFS_EVENT_ENGINE(data);
	data = mt76_rr(dev, MT_BBP(DFS, 37));
	event->ts = MT_DFS_EVENT_TIMESTAMP(data);
	data = mt76_rr(dev, MT_BBP(DFS, 37));
	event->width = MT_DFS_EVENT_WIDTH(data);

	return true;
}