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
struct mt76x02_dfs_pattern_detector {int /*<<< orphan*/  dfs_tasklet; int /*<<< orphan*/  last_sw_check; int /*<<< orphan*/  seq_pool; int /*<<< orphan*/  sequences; } ;
struct TYPE_2__ {int /*<<< orphan*/  region; } ;
struct mt76x02_dev {TYPE_1__ mt76; struct mt76x02_dfs_pattern_detector dfs_pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NL80211_DFS_UNSET ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mt76x02_dfs_tasklet ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

void mt76x02_dfs_init_detector(struct mt76x02_dev *dev)
{
	struct mt76x02_dfs_pattern_detector *dfs_pd = &dev->dfs_pd;

	INIT_LIST_HEAD(&dfs_pd->sequences);
	INIT_LIST_HEAD(&dfs_pd->seq_pool);
	dev->mt76.region = NL80211_DFS_UNSET;
	dfs_pd->last_sw_check = jiffies;
	tasklet_init(&dfs_pd->dfs_tasklet, mt76x02_dfs_tasklet,
		     (unsigned long)dev);
}