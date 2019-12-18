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
struct mlx5_ib_profile {int dummy; } ;
struct mlx5_ib_dev {int is_rep; int num_ports; struct mlx5_core_dev* mdev; TYPE_4__* port; int /*<<< orphan*/  ib_dev; } ;
struct mlx5_eswitch_rep {scalar_t__ vport; int vport_index; TYPE_3__* rep_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  eswitch; } ;
struct mlx5_core_dev {TYPE_2__ priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  netdev; } ;
struct TYPE_8__ {TYPE_1__ roce; struct mlx5_eswitch_rep* rep; } ;
struct TYPE_7__ {struct mlx5_ib_dev* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MLX5_VPORT_UPLINK ; 
 size_t REP_IB ; 
 int /*<<< orphan*/  __mlx5_ib_add (struct mlx5_ib_dev*,struct mlx5_ib_profile const*) ; 
 struct mlx5_ib_dev* ib_alloc_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dealloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_dev ; 
 TYPE_4__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int mlx5_eswitch_get_total_vports (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_ib_dev ; 
 int /*<<< orphan*/  mlx5_ib_get_rep_netdev (int /*<<< orphan*/ ,scalar_t__) ; 
 int mlx5_ib_set_vport_rep (struct mlx5_core_dev*,struct mlx5_eswitch_rep*) ; 
 struct mlx5_ib_profile uplink_rep_profile ; 

__attribute__((used)) static int
mlx5_ib_vport_rep_load(struct mlx5_core_dev *dev, struct mlx5_eswitch_rep *rep)
{
	int num_ports = mlx5_eswitch_get_total_vports(dev);
	const struct mlx5_ib_profile *profile;
	struct mlx5_ib_dev *ibdev;
	int vport_index;

	if (rep->vport == MLX5_VPORT_UPLINK)
		profile = &uplink_rep_profile;
	else
		return mlx5_ib_set_vport_rep(dev, rep);

	ibdev = ib_alloc_device(mlx5_ib_dev, ib_dev);
	if (!ibdev)
		return -ENOMEM;

	ibdev->port = kcalloc(num_ports, sizeof(*ibdev->port),
			      GFP_KERNEL);
	if (!ibdev->port) {
		ib_dealloc_device(&ibdev->ib_dev);
		return -ENOMEM;
	}

	ibdev->is_rep = true;
	vport_index = rep->vport_index;
	ibdev->port[vport_index].rep = rep;
	ibdev->port[vport_index].roce.netdev =
		mlx5_ib_get_rep_netdev(dev->priv.eswitch, rep->vport);
	ibdev->mdev = dev;
	ibdev->num_ports = num_ports;

	if (!__mlx5_ib_add(ibdev, profile))
		return -EINVAL;

	rep->rep_data[REP_IB].priv = ibdev;

	return 0;
}