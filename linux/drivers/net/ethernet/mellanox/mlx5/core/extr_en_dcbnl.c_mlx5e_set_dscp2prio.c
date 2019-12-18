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
typedef  size_t u8 ;
struct TYPE_2__ {size_t* dscp2prio; } ;
struct mlx5e_priv {TYPE_1__ dcbx_dp; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int mlx5_set_dscp2prio (int /*<<< orphan*/ ,size_t,size_t) ; 

__attribute__((used)) static int mlx5e_set_dscp2prio(struct mlx5e_priv *priv, u8 dscp, u8 prio)
{
	int err;

	err = mlx5_set_dscp2prio(priv->mdev, dscp, prio);
	if (err)
		return err;

	priv->dcbx_dp.dscp2prio[dscp] = prio;
	return err;
}