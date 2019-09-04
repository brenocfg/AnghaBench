#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* eq; } ;
struct mlx4_priv {TYPE_2__ eq_table; } ;
struct mlx4_dev {int dummy; } ;
struct TYPE_3__ {int irq; } ;

/* Variables and functions */
 size_t MLX4_CQ_TO_EQ_VECTOR (int) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

int mlx4_eq_get_irq(struct mlx4_dev *dev, int cq_vec)
{
	struct mlx4_priv *priv = mlx4_priv(dev);

	return priv->eq_table.eq[MLX4_CQ_TO_EQ_VECTOR(cq_vec)].irq;
}