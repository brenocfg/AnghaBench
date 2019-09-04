#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* eq; } ;
struct mlx4_priv {TYPE_3__ eq_table; } ;
struct TYPE_8__ {int num_comp_vectors; int /*<<< orphan*/  num_ports; } ;
struct mlx4_dev {TYPE_4__ caps; } ;
struct TYPE_5__ {int /*<<< orphan*/  ports; } ;
struct TYPE_6__ {TYPE_1__ actv_ports; } ;

/* Variables and functions */
 int EINVAL ; 
 int MLX4_CQ_TO_EQ_VECTOR (int) ; 
 int bitmap_weight (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

int mlx4_is_eq_shared(struct mlx4_dev *dev, int vector)
{
	struct mlx4_priv *priv = mlx4_priv(dev);

	vector = MLX4_CQ_TO_EQ_VECTOR(vector);
	if (vector <= 0 || (vector >= dev->caps.num_comp_vectors + 1))
		return -EINVAL;

	return !!(bitmap_weight(priv->eq_table.eq[vector].actv_ports.ports,
				dev->caps.num_ports) > 1);
}