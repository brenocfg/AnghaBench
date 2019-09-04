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
struct mlx5_eq_table {int /*<<< orphan*/  cmd_eq; int /*<<< orphan*/  async_eq; int /*<<< orphan*/  pages_eq; } ;
struct TYPE_2__ {struct mlx5_eq_table eq_table; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_cmd_use_polling (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,int) ; 
 int mlx5_destroy_unmap_eq (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 

void mlx5_stop_eqs(struct mlx5_core_dev *dev)
{
	struct mlx5_eq_table *table = &dev->priv.eq_table;
	int err;

#ifdef CONFIG_INFINIBAND_ON_DEMAND_PAGING
	if (MLX5_CAP_GEN(dev, pg)) {
		err = mlx5_destroy_unmap_eq(dev, &table->pfault_eq);
		if (err)
			mlx5_core_err(dev, "failed to destroy page fault eq, err(%d)\n",
				      err);
	}
#endif

	err = mlx5_destroy_unmap_eq(dev, &table->pages_eq);
	if (err)
		mlx5_core_err(dev, "failed to destroy pages eq, err(%d)\n",
			      err);

	err = mlx5_destroy_unmap_eq(dev, &table->async_eq);
	if (err)
		mlx5_core_err(dev, "failed to destroy async eq, err(%d)\n",
			      err);
	mlx5_cmd_use_polling(dev);

	err = mlx5_destroy_unmap_eq(dev, &table->cmd_eq);
	if (err)
		mlx5_core_err(dev, "failed to destroy command eq, err(%d)\n",
			      err);
}