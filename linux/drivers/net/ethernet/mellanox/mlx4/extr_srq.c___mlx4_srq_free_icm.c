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
struct mlx4_srq_table {int /*<<< orphan*/  bitmap; int /*<<< orphan*/  table; int /*<<< orphan*/  cmpt_table; } ;
struct mlx4_dev {int dummy; } ;
struct TYPE_2__ {struct mlx4_srq_table srq_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_NO_RR ; 
 int /*<<< orphan*/  mlx4_bitmap_free (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_table_put (struct mlx4_dev*,int /*<<< orphan*/ *,int) ; 

void __mlx4_srq_free_icm(struct mlx4_dev *dev, int srqn)
{
	struct mlx4_srq_table *srq_table = &mlx4_priv(dev)->srq_table;

	mlx4_table_put(dev, &srq_table->cmpt_table, srqn);
	mlx4_table_put(dev, &srq_table->table, srqn);
	mlx4_bitmap_free(&srq_table->bitmap, srqn, MLX4_NO_RR);
}