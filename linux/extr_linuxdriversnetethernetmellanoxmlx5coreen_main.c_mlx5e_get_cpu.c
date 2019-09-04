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
struct mlx5e_priv {TYPE_3__* mdev; } ;
struct TYPE_5__ {TYPE_1__* irq_info; } ;
struct TYPE_6__ {TYPE_2__ priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int MLX5_EQ_VEC_COMP_BASE ; 
 int cpumask_first (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5e_get_cpu(struct mlx5e_priv *priv, int ix)
{
	return cpumask_first(priv->mdev->priv.irq_info[ix + MLX5_EQ_VEC_COMP_BASE].mask);
}