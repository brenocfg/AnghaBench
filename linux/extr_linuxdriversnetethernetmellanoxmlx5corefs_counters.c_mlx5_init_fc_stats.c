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
struct mlx5_fc_stats {int /*<<< orphan*/  work; int /*<<< orphan*/  sampling_interval; int /*<<< orphan*/  wq; int /*<<< orphan*/  addlist_lock; int /*<<< orphan*/  addlist; int /*<<< orphan*/  counters; } ;
struct TYPE_2__ {struct mlx5_fc_stats fc_stats; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MLX5_FC_STATS_PERIOD ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  mlx5_fc_stats_work ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int mlx5_init_fc_stats(struct mlx5_core_dev *dev)
{
	struct mlx5_fc_stats *fc_stats = &dev->priv.fc_stats;

	fc_stats->counters = RB_ROOT;
	INIT_LIST_HEAD(&fc_stats->addlist);
	spin_lock_init(&fc_stats->addlist_lock);

	fc_stats->wq = create_singlethread_workqueue("mlx5_fc");
	if (!fc_stats->wq)
		return -ENOMEM;

	fc_stats->sampling_interval = MLX5_FC_STATS_PERIOD;
	INIT_DELAYED_WORK(&fc_stats->work, mlx5_fc_stats_work);

	return 0;
}