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
struct mlx4_mr_table {int /*<<< orphan*/  mpt_bitmap; int /*<<< orphan*/  mtt_buddy; } ;
struct mlx4_priv {scalar_t__ reserved_mtts; struct mlx4_mr_table mr_table; } ;
struct TYPE_2__ {scalar_t__ reserved_mtts; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  fls (scalar_t__) ; 
 int /*<<< orphan*/  mlx4_bitmap_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_buddy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_free_mtt_range (struct mlx4_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_is_slave (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

void mlx4_cleanup_mr_table(struct mlx4_dev *dev)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_mr_table *mr_table = &priv->mr_table;

	if (mlx4_is_slave(dev))
		return;
	if (priv->reserved_mtts >= 0)
		mlx4_free_mtt_range(dev, priv->reserved_mtts,
				    fls(dev->caps.reserved_mtts - 1));
	mlx4_buddy_cleanup(&mr_table->mtt_buddy);
	mlx4_bitmap_cleanup(&mr_table->mpt_bitmap);
}