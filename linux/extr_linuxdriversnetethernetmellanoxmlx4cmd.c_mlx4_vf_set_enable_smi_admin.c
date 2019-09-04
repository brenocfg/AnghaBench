#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* vf_admin; } ;
struct TYPE_11__ {TYPE_4__ master; } ;
struct TYPE_7__ {int /*<<< orphan*/  num_ports; } ;
struct TYPE_12__ {TYPE_1__ caps; } ;
struct mlx4_priv {TYPE_5__ mfunc; TYPE_6__ dev; } ;
struct TYPE_8__ {int num_ports; } ;
struct mlx4_dev {int num_slaves; TYPE_2__ caps; } ;
struct mlx4_active_ports {int /*<<< orphan*/  ports; } ;
struct TYPE_9__ {int* enable_smi; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROTONOSUPPORT ; 
 int MLX4_MAX_PORTS ; 
 int bitmap_weight (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int find_first_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx4_active_ports mlx4_get_active_ports (TYPE_6__*,int) ; 
 int /*<<< orphan*/  mlx4_info (struct mlx4_dev*,char*) ; 
 int mlx4_master_func_num (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

int mlx4_vf_set_enable_smi_admin(struct mlx4_dev *dev, int slave, int port,
				 int enabled)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_active_ports actv_ports = mlx4_get_active_ports(
			&priv->dev, slave);
	int min_port = find_first_bit(actv_ports.ports,
				      priv->dev.caps.num_ports) + 1;
	int max_port = min_port - 1 +
		bitmap_weight(actv_ports.ports, priv->dev.caps.num_ports);

	if (slave == mlx4_master_func_num(dev))
		return 0;

	if (slave < 1 || slave >= dev->num_slaves ||
	    port < 1 || port > MLX4_MAX_PORTS ||
	    enabled < 0 || enabled > 1)
		return -EINVAL;

	if (min_port == max_port && dev->caps.num_ports > 1) {
		mlx4_info(dev, "SMI access disallowed for single ported VFs\n");
		return -EPROTONOSUPPORT;
	}

	priv->mfunc.master.vf_admin[slave].enable_smi[port] = enabled;
	return 0;
}