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
struct mlx4_en_priv {TYPE_1__* mdev; } ;
struct mlx4_en_cq {int /*<<< orphan*/  mcq; } ;
struct TYPE_2__ {int /*<<< orphan*/  uar_lock; int /*<<< orphan*/  uar_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_CQ_DB_REQ_NOT ; 
 int /*<<< orphan*/  mlx4_cq_arm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mlx4_en_arm_cq(struct mlx4_en_priv *priv, struct mlx4_en_cq *cq)
{
	mlx4_cq_arm(&cq->mcq, MLX4_CQ_DB_REQ_NOT, priv->mdev->uar_map,
		    &priv->mdev->uar_lock);
}