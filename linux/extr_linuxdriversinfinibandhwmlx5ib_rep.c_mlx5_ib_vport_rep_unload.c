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
struct mlx5_ib_dev {int /*<<< orphan*/  profile; } ;
struct mlx5_eswitch_rep {TYPE_1__* rep_if; } ;
struct TYPE_2__ {int /*<<< orphan*/ * priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_IB_STAGE_MAX ; 
 size_t REP_IB ; 
 int /*<<< orphan*/  __mlx5_ib_remove (struct mlx5_ib_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5_ib_dev* mlx5_ib_rep_to_dev (struct mlx5_eswitch_rep*) ; 

__attribute__((used)) static void
mlx5_ib_vport_rep_unload(struct mlx5_eswitch_rep *rep)
{
	struct mlx5_ib_dev *dev;

	if (!rep->rep_if[REP_IB].priv)
		return;

	dev = mlx5_ib_rep_to_dev(rep);
	__mlx5_ib_remove(dev, dev->profile, MLX5_IB_STAGE_MAX);
	rep->rep_if[REP_IB].priv = NULL;
}