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
struct mlx5_fc_stats {int /*<<< orphan*/  wq; } ;
struct TYPE_2__ {struct mlx5_fc_stats fc_stats; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;
struct delayed_work {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,struct delayed_work*,unsigned long) ; 

void mlx5_fc_queue_stats_work(struct mlx5_core_dev *dev,
			      struct delayed_work *dwork,
			      unsigned long delay)
{
	struct mlx5_fc_stats *fc_stats = &dev->priv.fc_stats;

	queue_delayed_work(fc_stats->wq, dwork, delay);
}