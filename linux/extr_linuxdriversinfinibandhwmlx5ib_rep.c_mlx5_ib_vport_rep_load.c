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
struct mlx5_ib_dev {int /*<<< orphan*/  num_ports; struct mlx5_core_dev* mdev; struct mlx5_eswitch_rep* rep; } ;
struct mlx5_eswitch_rep {TYPE_1__* rep_if; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_2__ {struct mlx5_ib_dev* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 size_t REP_IB ; 
 int /*<<< orphan*/  __mlx5_ib_add (struct mlx5_ib_dev*,int /*<<< orphan*/ *) ; 
 scalar_t__ ib_alloc_device (int) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_ports ; 
 int /*<<< orphan*/  num_vhca_ports ; 
 int /*<<< orphan*/  rep_profile ; 

__attribute__((used)) static int
mlx5_ib_vport_rep_load(struct mlx5_core_dev *dev, struct mlx5_eswitch_rep *rep)
{
	struct mlx5_ib_dev *ibdev;

	ibdev = (struct mlx5_ib_dev *)ib_alloc_device(sizeof(*ibdev));
	if (!ibdev)
		return -ENOMEM;

	ibdev->rep = rep;
	ibdev->mdev = dev;
	ibdev->num_ports = max(MLX5_CAP_GEN(dev, num_ports),
			       MLX5_CAP_GEN(dev, num_vhca_ports));
	if (!__mlx5_ib_add(ibdev, &rep_profile))
		return -EINVAL;

	rep->rep_if[REP_IB].priv = ibdev;

	return 0;
}