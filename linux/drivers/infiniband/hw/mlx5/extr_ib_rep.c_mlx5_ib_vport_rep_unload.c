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
struct TYPE_3__ {int /*<<< orphan*/  netdev_lock; int /*<<< orphan*/ * netdev; } ;
struct mlx5_ib_port {int /*<<< orphan*/ * rep; TYPE_1__ roce; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  profile; struct mlx5_ib_port* port; } ;
struct mlx5_eswitch_rep {size_t vport_index; scalar_t__ vport; TYPE_2__* rep_data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_IB_STAGE_MAX ; 
 scalar_t__ MLX5_VPORT_UPLINK ; 
 size_t REP_IB ; 
 int /*<<< orphan*/  __mlx5_ib_remove (struct mlx5_ib_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5_ib_dev* mlx5_ib_rep_to_dev (struct mlx5_eswitch_rep*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlx5_ib_vport_rep_unload(struct mlx5_eswitch_rep *rep)
{
	struct mlx5_ib_dev *dev = mlx5_ib_rep_to_dev(rep);
	struct mlx5_ib_port *port;

	port = &dev->port[rep->vport_index];
	write_lock(&port->roce.netdev_lock);
	port->roce.netdev = NULL;
	write_unlock(&port->roce.netdev_lock);
	rep->rep_data[REP_IB].priv = NULL;
	port->rep = NULL;

	if (rep->vport == MLX5_VPORT_UPLINK)
		__mlx5_ib_remove(dev, dev->profile, MLX5_IB_STAGE_MAX);
}