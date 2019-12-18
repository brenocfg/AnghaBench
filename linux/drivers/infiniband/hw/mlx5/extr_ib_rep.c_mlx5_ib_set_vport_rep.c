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
struct mlx5_ib_dev {TYPE_4__* port; } ;
struct mlx5_eswitch_rep {int vport_index; int /*<<< orphan*/  vport; TYPE_1__* rep_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  eswitch; } ;
struct mlx5_core_dev {TYPE_2__ priv; } ;
struct TYPE_7__ {int /*<<< orphan*/  netdev_lock; int /*<<< orphan*/  netdev; } ;
struct TYPE_8__ {TYPE_3__ roce; struct mlx5_eswitch_rep* rep; } ;
struct TYPE_5__ {struct mlx5_ib_dev* priv; } ;

/* Variables and functions */
 size_t REP_IB ; 
 int /*<<< orphan*/  mlx5_ib_get_rep_netdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5_ib_dev* mlx5_ib_get_uplink_ibdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mlx5_ib_set_vport_rep(struct mlx5_core_dev *dev, struct mlx5_eswitch_rep *rep)
{
	struct mlx5_ib_dev *ibdev;
	int vport_index;

	ibdev = mlx5_ib_get_uplink_ibdev(dev->priv.eswitch);
	vport_index = rep->vport_index;

	ibdev->port[vport_index].rep = rep;
	rep->rep_data[REP_IB].priv = ibdev;
	write_lock(&ibdev->port[vport_index].roce.netdev_lock);
	ibdev->port[vport_index].roce.netdev =
		mlx5_ib_get_rep_netdev(dev->priv.eswitch, rep->vport);
	write_unlock(&ibdev->port[vport_index].roce.netdev_lock);

	return 0;
}