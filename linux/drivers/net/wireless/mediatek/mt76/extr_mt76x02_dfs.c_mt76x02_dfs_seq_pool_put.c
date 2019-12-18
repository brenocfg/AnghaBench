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
struct mt76x02_dfs_sequence {int /*<<< orphan*/  head; } ;
struct TYPE_2__ {int /*<<< orphan*/  seq_len; int /*<<< orphan*/  seq_pool_len; } ;
struct mt76x02_dfs_pattern_detector {TYPE_1__ seq_stats; int /*<<< orphan*/  seq_pool; } ;
struct mt76x02_dev {struct mt76x02_dfs_pattern_detector dfs_pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt76x02_dfs_seq_pool_put(struct mt76x02_dev *dev,
				     struct mt76x02_dfs_sequence *seq)
{
	struct mt76x02_dfs_pattern_detector *dfs_pd = &dev->dfs_pd;

	list_add(&seq->head, &dfs_pd->seq_pool);

	dfs_pd->seq_stats.seq_pool_len++;
	dfs_pd->seq_stats.seq_len--;
}