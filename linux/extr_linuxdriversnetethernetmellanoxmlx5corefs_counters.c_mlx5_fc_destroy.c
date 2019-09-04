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
struct mlx5_fc_stats {int /*<<< orphan*/  work; int /*<<< orphan*/  wq; } ;
struct mlx5_fc {int deleted; int /*<<< orphan*/  id; scalar_t__ aging; } ;
struct TYPE_2__ {struct mlx5_fc_stats fc_stats; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlx5_fc*) ; 
 int /*<<< orphan*/  mlx5_cmd_fc_free (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void mlx5_fc_destroy(struct mlx5_core_dev *dev, struct mlx5_fc *counter)
{
	struct mlx5_fc_stats *fc_stats = &dev->priv.fc_stats;

	if (!counter)
		return;

	if (counter->aging) {
		counter->deleted = true;
		mod_delayed_work(fc_stats->wq, &fc_stats->work, 0);
		return;
	}

	mlx5_cmd_fc_free(dev, counter->id);
	kfree(counter);
}