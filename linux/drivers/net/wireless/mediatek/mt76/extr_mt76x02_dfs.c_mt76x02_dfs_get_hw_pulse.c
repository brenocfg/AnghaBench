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
struct mt76x02_dfs_hw_pulse {int engine; void* burst; void* w2; void* w1; void* period; } ;
struct mt76x02_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFS ; 
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int) ; 
 int MT_DFS_CH_EN ; 
 void* mt76_rr (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mt76x02_dfs_get_hw_pulse(struct mt76x02_dev *dev,
				     struct mt76x02_dfs_hw_pulse *pulse)
{
	u32 data;

	/* select channel */
	data = (MT_DFS_CH_EN << 16) | pulse->engine;
	mt76_wr(dev, MT_BBP(DFS, 0), data);

	/* reported period */
	pulse->period = mt76_rr(dev, MT_BBP(DFS, 19));

	/* reported width */
	pulse->w1 = mt76_rr(dev, MT_BBP(DFS, 20));
	pulse->w2 = mt76_rr(dev, MT_BBP(DFS, 23));

	/* reported burst number */
	pulse->burst = mt76_rr(dev, MT_BBP(DFS, 22));
}