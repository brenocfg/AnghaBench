#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlx5_rl_table {int max_size; TYPE_3__* rl_entry; } ;
struct mlx5_rate_limit {int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {struct mlx5_rl_table rl_table; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;
struct TYPE_5__ {scalar_t__ rate; } ;
struct TYPE_6__ {int /*<<< orphan*/  index; TYPE_2__ rl; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  mlx5_set_pp_rate_limit_cmd (struct mlx5_core_dev*,int /*<<< orphan*/ ,struct mlx5_rate_limit*) ; 

void mlx5_cleanup_rl_table(struct mlx5_core_dev *dev)
{
	struct mlx5_rl_table *table = &dev->priv.rl_table;
	struct mlx5_rate_limit rl = {0};
	int i;

	/* Clear all configured rates */
	for (i = 0; i < table->max_size; i++)
		if (table->rl_entry[i].rl.rate)
			mlx5_set_pp_rate_limit_cmd(dev, table->rl_entry[i].index,
						   &rl);

	kfree(dev->priv.rl_table.rl_entry);
}