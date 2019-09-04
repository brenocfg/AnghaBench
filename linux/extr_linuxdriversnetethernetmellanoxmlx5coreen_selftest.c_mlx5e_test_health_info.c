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
struct mlx5e_priv {TYPE_2__* mdev; } ;
struct mlx5_core_health {scalar_t__ sick; } ;
struct TYPE_3__ {struct mlx5_core_health health; } ;
struct TYPE_4__ {TYPE_1__ priv; } ;

/* Variables and functions */

__attribute__((used)) static int mlx5e_test_health_info(struct mlx5e_priv *priv)
{
	struct mlx5_core_health *health = &priv->mdev->priv.health;

	return health->sick ? 1 : 0;
}