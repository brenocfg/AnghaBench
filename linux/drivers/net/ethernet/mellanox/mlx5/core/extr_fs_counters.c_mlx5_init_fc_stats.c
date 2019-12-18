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
struct mlx5_fc_stats {int /*<<< orphan*/  bulk_query_out; int /*<<< orphan*/  fc_pool; int /*<<< orphan*/  work; int /*<<< orphan*/  sampling_interval; int /*<<< orphan*/  wq; int /*<<< orphan*/  dellist; int /*<<< orphan*/  addlist; int /*<<< orphan*/  counters; int /*<<< orphan*/  counters_idr; int /*<<< orphan*/  counters_idr_lock; } ;
struct TYPE_2__ {struct mlx5_fc_stats fc_stats; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MLX5_FC_STATS_PERIOD ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int get_max_bulk_query_len (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_llist_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_cmd_fc_get_bulk_query_out_len (int) ; 
 int /*<<< orphan*/  mlx5_fc_pool_init (int /*<<< orphan*/ *,struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_fc_stats_work ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int mlx5_init_fc_stats(struct mlx5_core_dev *dev)
{
	struct mlx5_fc_stats *fc_stats = &dev->priv.fc_stats;
	int max_bulk_len;
	int max_out_len;

	spin_lock_init(&fc_stats->counters_idr_lock);
	idr_init(&fc_stats->counters_idr);
	INIT_LIST_HEAD(&fc_stats->counters);
	init_llist_head(&fc_stats->addlist);
	init_llist_head(&fc_stats->dellist);

	max_bulk_len = get_max_bulk_query_len(dev);
	max_out_len = mlx5_cmd_fc_get_bulk_query_out_len(max_bulk_len);
	fc_stats->bulk_query_out = kzalloc(max_out_len, GFP_KERNEL);
	if (!fc_stats->bulk_query_out)
		return -ENOMEM;

	fc_stats->wq = create_singlethread_workqueue("mlx5_fc");
	if (!fc_stats->wq)
		goto err_wq_create;

	fc_stats->sampling_interval = MLX5_FC_STATS_PERIOD;
	INIT_DELAYED_WORK(&fc_stats->work, mlx5_fc_stats_work);

	mlx5_fc_pool_init(&fc_stats->fc_pool, dev);
	return 0;

err_wq_create:
	kfree(fc_stats->bulk_query_out);
	return -ENOMEM;
}