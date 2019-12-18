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
typedef  int u8 ;
struct net_device {int dummy; } ;
struct mlx5_roce {int /*<<< orphan*/  netdev_lock; } ;
struct mlx5_ib_port {struct mlx5_roce roce; TYPE_3__* rep; } ;
struct mlx5_ib_dev {int num_ports; struct mlx5_ib_port* port; TYPE_2__* mdev; } ;
struct mlx5_eswitch {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  vport; } ;
struct TYPE_4__ {struct mlx5_eswitch* eswitch; } ;
struct TYPE_5__ {TYPE_1__ priv; } ;

/* Variables and functions */
 struct net_device* mlx5_ib_get_rep_netdev (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlx5_roce *mlx5_get_rep_roce(struct mlx5_ib_dev *dev,
					   struct net_device *ndev,
					   u8 *port_num)
{
	struct mlx5_eswitch *esw = dev->mdev->priv.eswitch;
	struct net_device *rep_ndev;
	struct mlx5_ib_port *port;
	int i;

	for (i = 0; i < dev->num_ports; i++) {
		port  = &dev->port[i];
		if (!port->rep)
			continue;

		read_lock(&port->roce.netdev_lock);
		rep_ndev = mlx5_ib_get_rep_netdev(esw,
						  port->rep->vport);
		if (rep_ndev == ndev) {
			read_unlock(&port->roce.netdev_lock);
			*port_num = i + 1;
			return &port->roce;
		}
		read_unlock(&port->roce.netdev_lock);
	}

	return NULL;
}