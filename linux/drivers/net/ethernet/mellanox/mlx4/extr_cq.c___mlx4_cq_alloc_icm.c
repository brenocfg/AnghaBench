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
struct mlx4_cq_table {int /*<<< orphan*/  bitmap; int /*<<< orphan*/  table; int /*<<< orphan*/  cmpt_table; } ;
struct mlx4_priv {struct mlx4_cq_table cq_table; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MLX4_NO_RR ; 
 int mlx4_bitmap_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_bitmap_free (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int mlx4_table_get (struct mlx4_dev*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlx4_table_put (struct mlx4_dev*,int /*<<< orphan*/ *,int) ; 

int __mlx4_cq_alloc_icm(struct mlx4_dev *dev, int *cqn)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_cq_table *cq_table = &priv->cq_table;
	int err;

	*cqn = mlx4_bitmap_alloc(&cq_table->bitmap);
	if (*cqn == -1)
		return -ENOMEM;

	err = mlx4_table_get(dev, &cq_table->table, *cqn);
	if (err)
		goto err_out;

	err = mlx4_table_get(dev, &cq_table->cmpt_table, *cqn);
	if (err)
		goto err_put;
	return 0;

err_put:
	mlx4_table_put(dev, &cq_table->table, *cqn);

err_out:
	mlx4_bitmap_free(&cq_table->bitmap, *cqn, MLX4_NO_RR);
	return err;
}