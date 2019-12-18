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
typedef  int /*<<< orphan*/  u64 ;
struct mlx4_slave_state {int /*<<< orphan*/  old_vlan_api; } ;
struct TYPE_3__ {struct mlx4_slave_state* slave_state; } ;
struct TYPE_4__ {TYPE_1__ master; } ;
struct mlx4_priv {TYPE_2__ mfunc; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  RES_OP_RESERVE_AND_MAP 128 
 int /*<<< orphan*/  __mlx4_unregister_vlan (struct mlx4_dev*,int,int /*<<< orphan*/ ) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int mlx4_slave_convert_port (struct mlx4_dev*,int,int) ; 
 int /*<<< orphan*/  vlan_del_from_slave (struct mlx4_dev*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vlan_free_res(struct mlx4_dev *dev, int slave, int op, int cmd,
			    u64 in_param, u64 *out_param, int port)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_slave_state *slave_state = priv->mfunc.master.slave_state;
	int err = 0;

	port = mlx4_slave_convert_port(
			dev, slave, port);

	if (port < 0)
		return -EINVAL;
	switch (op) {
	case RES_OP_RESERVE_AND_MAP:
		if (slave_state[slave].old_vlan_api)
			return 0;
		if (!port)
			return -EINVAL;
		vlan_del_from_slave(dev, slave, in_param, port);
		__mlx4_unregister_vlan(dev, port, in_param);
		break;
	default:
		err = -EINVAL;
		break;
	}

	return err;
}